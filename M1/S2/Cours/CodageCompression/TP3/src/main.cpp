#include "ImageBase.h"
#include <stdio.h>
#include "fonctions.h"
#include <iostream>
#include <cmath>
#include <vector>

struct Color{
	int R , G , B; 
	Color(int r1, int g1 , int b1){
		R = r1 ; G = g1 , B = b1;
	}
	bool equals(Color c1 , Color c2){
		return c1.R == c2.R && c1.G == c2.G && c1.B == c2.B;
	}
};

void seperateColor(ImageBase &imIn, ImageBase &imOutR, ImageBase &imOutG ,ImageBase &imOutB) {
	for (int y = 0; y < imIn.getHeight(); y++) {
		for (int x = 0; x < imIn.getWidth(); x++) {
			imOutR[y][x] = imIn[y*3][x*3+0]; // R
			imOutG[y][x] = imIn[y*3][x*3+1]; // G
			imOutB[y][x] = imIn[y*3][x*3+2]; // B
		}
	}
}

void reduceComponent(ImageBase &imInPgm, ImageBase &imReduced) {
	for (int y = 0; y < imReduced.getHeight(); y++) {
		for (int x = 0; x < imReduced.getWidth(); x++) {
			int sum = imInPgm[y * 2][x * 2] + imInPgm[y * 2 + 1][x * 2] + imInPgm[y * 2][x * 2 + 1] + imInPgm[y * 2 + 1][x * 2 + 1];
			imReduced[y][x] = sum / 4;
		}
	}
}

void growImage(ImageBase &imInReduced , ImageBase &imOutGrown) {
	for (int y = 0; y < imInReduced.getHeight(); y++) {
		for (int x = 0; x < imInReduced.getWidth(); x++) {
			imOutGrown[y * 2][x * 2] = imInReduced[y][x];
			imOutGrown[y * 2 + 1][x * 2] = imInReduced[y][x];
			imOutGrown[y * 2][x * 2 + 1] = imInReduced[y][x];
			imOutGrown[y * 2 + 1][x * 2 + 1] = imInReduced[y][x];
		}
	}
}

void reconstructImage(ImageBase &imInR , ImageBase imInG , ImageBase imInB , ImageBase &imOut){
	for (int y = 0; y < imOut.getHeight(); y++) {
		for (int x = 0; x < imOut.getWidth(); x++) {
			imOut[y*3][x*3+0] = imInR[y][x]; // R
			imOut[y*3][x*3+1] = imInG[y][x]; // G
			imOut[y*3][x*3+2] = imInB[y][x]; // B
		}
	}
}

float EQM(ImageBase &imIn, ImageBase &imOut) {
	float eqm = 0.0;
	for (int y = 0; y < imIn.getHeight(); y++) {
		for (int x = 0; x < imIn.getWidth(); x++) {
			for (int c = 0; c < 3; c++) {
				float diff = imIn[y * 3 + c][x * 3] - imOut[y * 3 + c][x * 3];
				eqm += diff * diff;
			}
		}
	}
	eqm /= (imIn.getHeight() * imIn.getWidth() * 3);
	return eqm;
}

float PSNR(float max , float eqm){ //not sure walla
	return 10*log10((max*max) / eqm);
}

void RGBtoYCrCb(ImageBase &imIn, ImageBase &imOut) {
	for (int y = 0; y < imIn.getHeight(); y++) {
		for (int x = 0; x < imIn.getWidth(); x++) {
			int R = imIn[y * 3][x * 3 + 0];
			int G = imIn[y * 3][x * 3 + 1];
			int B = imIn[y * 3][x * 3 + 2];

			int Y = 0.299 * R + 0.587 * G + 0.114 * B;
			int Cr = 128 + 0.5 * R - 0.418688 * G - 0.081312 * B;
			int Cb = 128 - 0.168736 * R - 0.331264 * G + 0.5 * B;

			imOut[y * 3][x * 3 + 0] = Y;
			imOut[y * 3][x * 3 + 1] = Cr;
			imOut[y * 3][x * 3 + 2] = Cb;
		}
	}
}

void YCrCbtoRGB(ImageBase &imIn, ImageBase &imOut) {
	for (int y = 0; y < imIn.getHeight(); y++) {
		for (int x = 0; x < imIn.getWidth(); x++) {
			int Y = imIn[y * 3][x * 3 + 0];
			int Cr = imIn[y * 3][x * 3 + 1];
			int Cb = imIn[y * 3][x * 3 + 2];

			int R = Y + 1.402 * (Cr - 128);
			int G = Y - 0.344136 * (Cb - 128) - 0.714136 * (Cr - 128);
			int B = Y + 1.772 * (Cb - 128);

			imOut[y * 3][x * 3 + 0] = std::min(std::max(R, 0), 255);
			imOut[y * 3][x * 3 + 1] = std::min(std::max(G, 0), 255);
			imOut[y * 3][x * 3 + 2] = std::min(std::max(B, 0), 255);
		}
	}
}

void seperateYCrCb(ImageBase &imIn, ImageBase &imOutY, ImageBase &imOutCr, ImageBase &imOutCb) {
	for (int y = 0; y < imIn.getHeight(); y++) {
		for (int x = 0; x < imIn.getWidth(); x++) {
			imOutY[y][x] = imIn[y * 3][x * 3 + 0]; // Y
			imOutCr[y][x] = imIn[y * 3][x * 3 + 1]; // Cr
			imOutCb[y][x] = imIn[y * 3][x * 3 + 2]; // Cb
		}
	}
}

void reduceCrCb(ImageBase &imInCr, ImageBase &imInCb, ImageBase &imReducedCr, ImageBase &imReducedCb) {
	for (int y = 0; y < imReducedCr.getHeight(); y++) {
		for (int x = 0; x < imReducedCr.getWidth(); x++) {
			int sumCr = imInCr[y * 2][x * 2] + imInCr[y * 2 + 1][x * 2] + imInCr[y * 2][x * 2 + 1] + imInCr[y * 2 + 1][x * 2 + 1];
			int sumCb = imInCb[y * 2][x * 2] + imInCb[y * 2 + 1][x * 2] + imInCb[y * 2][x * 2 + 1] + imInCb[y * 2 + 1][x * 2 + 1];
			imReducedCr[y][x] = sumCr / 4;
			imReducedCb[y][x] = sumCb / 4;
		}
	}
}

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	// char cNomImgLue[250], cNomImgEcrite1[250], cNomImgEcrite2[250], cNomImgEcrite3[250];
	// int LC;
	// int num;

  
	// if (argc != 5) 
	// {
	// 	printf("Usage: ImageIn.ppm ImOutR.ppm ImOutG.ppm ImOutB.ppm \n"); 
	// 	return 1;
	// }
	// sscanf (argv[1],"%s",cNomImgLue) ;
	// //sscanf (argv[2],"%s",cNomImgEcrite);
	// sscanf (argv[2], "%s" , cNomImgEcrite1);
	// sscanf (argv[3], "%s" , cNomImgEcrite2);
	// sscanf (argv[4], "%s" , cNomImgEcrite3);

	// //sscanf (argv[3],"%d",&S1);
	// //sscanf (argv[4],"%d",&S2);
	
	ImageBase imIn;
	imIn.load("img/in/cuttlefish.pgm");
	std::vector<int> histo;
	histogramme_pgm(imIn , histo);

	std::cout << "Entropie : " << entropy_pgm(imIn) << std::endl;
	ImageBase imOut0(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	carte_diff(imIn, imOut0, 0);
	histogramme_pgm(imOut0);
	std::cout << "Entropie carte 0 : " << entropy_pgm(imOut0) << std::endl;
	imOut0.save("img/out/carte_diff0.pgm");

	ImageBase imOut1(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	carte_diff(imIn, imOut1, 1);
	histogramme_pgm(imOut1);
	std::cout << "Entropie carte 1 : " << entropy_pgm(imOut1) << std::endl;
	imOut1.save("img/out/carte_diff1.pgm");

	ImageBase imOut2(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	carte_diff(imIn, imOut2, 2);
	histogramme_pgm(imOut2);
	std::cout << "Entropie carte 2 : " << entropy_pgm(imOut2) << std::endl;
	imOut2.save("img/out/carte_diff2.pgm");

	ImageBase imOut3(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	carte_diff(imIn, imOut3, 3);
	histogramme_pgm(imOut3);
	std::cout << "Entropie carte 3 : " << entropy_pgm(imOut3) << std::endl;
	imOut3.save("img/out/carte_diff3.pgm");

	ImageBase imOut4(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
	carte_diff(imIn, imOut4, 4);
	histogramme_pgm(imOut4);
	std::cout << "Entropie carte 4 : " << entropy_pgm(imOut4) << std::endl;
	imOut4.save("img/out/carte_diff4.pgm");

	///////////////////////////////////////// Exemple de cr�ation d'une image couleur
	ImageBase imC(50, 100, true);

	for(int y = 0; y < imC.getHeight(); ++y)
		for(int x = 0; x < imC.getWidth(); ++x)
		{
			imC[y*3][x*3+0] = 200; // R
			imC[y*3][x*3+1] = 0; // G
			imC[y*3][x*3+2] = 0; // B
		}
		
	imC.save("imC.ppm");
		



	///////////////////////////////////////// Exemple de cr�ation d'une image en niveau de gris
	ImageBase imG(50, 100, false);

	for(int y = 0; y < imG.getHeight(); ++y)
		for(int x = 0; x < imG.getWidth(); ++x)
			imG[y][x] = 50;

	imG.save("imG.pgm");




	ImageBase imC2, imG2;
	
	///////////////////////////////////////// Exemple lecture image couleur
	imC2.load("imC.ppm");
	///////////////////////////////////////// Exemple lecture image en niveau de gris
	imG2.load("imG.pgm");
	
	

	///////////////////////////////////////// Exemple de r�cup�ration d'un plan de l'image
	ImageBase *R = imC2.getPlan(ImageBase::PLAN_R);
	R->save("R.pgm");
	delete R;
	


	return 0;
}
