#include "ImageBase.h"
#include <stdio.h>
#include "fonctions.h"
#include <iostream>
#include <cmath>
#include <ctime>
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

float distanceCouleur(Color c1 , Color c2){
	return sqrt(pow(c1.R - c2.R , 2) + pow(c1.G - c2.G , 2) + pow(c1.B - c2.B , 2));
}

std::vector<Color> generateRandomColors(int numColors){
	std::vector<Color> colors;
	std::srand(std::time(nullptr));
	for(int i = 0 ; i < numColors ; i++){
		int randR = std::rand() % 256;
		int randG = std::rand() % 256;
		int randB = std::rand() % 256;
		Color randomColor(randR, randG, randB);
		colors.push_back(randomColor);
	}
	return colors;
}

float k_mean(int k, ImageBase& imgIn, ImageBase& imgOut, std::vector<Color> colors) {
    for (int y = 0; y < imgIn.getHeight(); y++) {
        for (int x = 0; x < imgIn.getWidth(); x++) {
            Color pixelColor(imgIn[y * 3][x * 3 + 0], imgIn[y * 3][x * 3 + 1], imgIn[y * 3][x * 3 + 2]);

            int bestIndex = 0;
            float minDistance = distanceCouleur(pixelColor, colors[0]);

            for (int i = 1; i < k; i++) {
                float dist = distanceCouleur(pixelColor, colors[i]);
                if (dist < minDistance) {
                    minDistance = dist;
                    bestIndex = i;
                }
            }

            imgOut[y * 3][x * 3 + 0] = colors[bestIndex].R;
            imgOut[y * 3][x * 3 + 1] = colors[bestIndex].G;
            imgOut[y * 3][x * 3 + 2] = colors[bestIndex].B;
        }
    }
}


void two_mean(int k, ImageBase& imgIn, ImageBase& imgOut, Color c1, Color c2) {
	//foreach pixel, distance between color value of pixel and each value i chose
	for (int y = 0; y < imgIn.getHeight(); y++) {
		for (int x = 0; x < imgIn.getWidth(); x++) {
			Color pixelColor(imgIn[y * 3][x * 3 + 0], imgIn[y * 3][x * 3 + 1], imgIn[y * 3][x * 3 + 2]);
			//if value is closer to v1 pick v2 else v2
			float distV1 = distanceCouleur(pixelColor, c1);
			float distC2 = distanceCouleur(pixelColor, c2);
			if (distV1 < distC2) {
				imgOut[y * 3][x * 3 + 0] = c1.R;
				imgOut[y * 3][x * 3 + 1] = c1.G;
				imgOut[y * 3][x * 3 + 2] = c1.B;
			} else {
				imgOut[y * 3][x * 3 + 0] = c2.R;
				imgOut[y * 3][x * 3 + 1] = c2.G;
				imgOut[y * 3][x * 3 + 2] = c2.B;
			}
		}
	}
}

float getCentroid(std::vector<Color> colors){
	float centroid = 0.0;
	for(Color c : colors){
		centroid+= c.R + c.B + c.G;
	}
	return centroid/(colors.size()*3);
}

float PSNR(float max , float eqm){ //not sure walla
	return 10*log10((max*max) / eqm);
}

float EQM(ImageBase imIn , ImageBase imOut){
	float eqm = 0;
	for (int y = 0; y < imOut.getHeight(); ++y){
        for (int x = 0; x < imOut.getWidth(); ++x){
			eqm += sqrt(pow((imIn[x][y] - imOut[x][y]),2));
		}
	}
	eqm /= (imOut.getHeight() * imOut.getWidth());
	return eqm;
}

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image
	char cNomImgLue[250], cNomImgEcrite[250] , cNomImgEcrite2[250], cNomImgEcrite3[250];
	int LC;
	int num;
	int k;

  
	if (argc != 6) 
	{
		printf("Usage: ImageIn.ppm ImageOut1.ppm k ImageOut2.pgm ImageOut3.ppm\n"); 
		return 1;
	}
	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcrite);
	sscanf (argv[3], "%d" , &k);
	sscanf (argv[4],"%s",cNomImgEcrite2);
	sscanf (argv[5],"%s",cNomImgEcrite3);

	//sscanf (argv[3],"%d",&S1);
	//sscanf (argv[4],"%d",&S2);
	
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(cNomImgLue);

	//ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	ImageBase imUnOct(imIn.getWidth(), imIn.getHeight(), false);

	//seuil2(&imIn , &imOut , S1);
	//profil_pgm(imIn , LC , num);

	//imOut.save(cNomImgEcrite);

	//iterate for k colors
  	std::vector<Color> colors = generateRandomColors(k);
    bool changed = true;
    int max_it = 10;
    int i = 0;
	float threshold = 0.05f;

    while (changed && i < max_it) {
        k_mean(k, imIn, imOut, colors);
        std::vector<Color> new_colors(k, Color(0, 0, 0));
        std::vector<int> count(k, 0);

        for (int y = 0; y < imOut.getHeight(); ++y) {
            for (int x = 0; x < imOut.getWidth(); ++x) {
				Color pixelColor(imIn[y * 3][x * 3 + 0], imIn[y * 3][x * 3 + 1], imIn[y * 3][x * 3 + 2]);
                int bestIndex = 0;
                float minDistance = distanceCouleur(pixelColor, colors[0]);

                for (int j = 1; j < k; j++) {
                    float dist = distanceCouleur(pixelColor, colors[j]);
                    if (dist < minDistance) {
                        minDistance = dist;
                        bestIndex = j;
                    }
                }

                new_colors[bestIndex].R += pixelColor.R;
                new_colors[bestIndex].G += pixelColor.G;
                new_colors[bestIndex].B += pixelColor.B;
                count[bestIndex]++;
            }
        }

        for (int j = 0; j < k; j++) {
            if (count[j] > 0) {
                new_colors[j].R /= count[j];
                new_colors[j].G /= count[j];
                new_colors[j].B /= count[j];
            }
		}


		float old_centroid = getCentroid(colors);
		float new_centroid = getCentroid(new_colors);
		//std::cout << "heeeeeeeeeeeeeelp " << (new_centroid - old_centroid)  << std::endl;
		if(std::abs(new_centroid - old_centroid) <= threshold){
			changed = false;
		}

		colors = new_colors;
        i++;
		std::cout << "Kmean looped "  << i << " times" << std::endl;
    }

	//eqm = EQM(imIn , imOut);
	//float psnr = PSNR(k , eqm);
	//std::cout << "PSNR : " << psnr << std::endl;

	std::cout << "nb iterations : " << i << std::endl;

	//iterate for two colors.

	// //randomly gen 2 colors
	// bool changed = true;
	// int random_value1 = std::rand() % (imIn.getWidth() * imIn.getHeight());
	// int random_value2 = std::rand() % (imIn.getWidth() * imIn.getHeight());
	// int x1 = random_value1 % imIn.getWidth();
	// int y1 = random_value1 / imIn.getWidth();
	// Color c1(imIn[y1 * 3][x1 * 3 + 0], imIn[y1 * 3][x1 * 3 + 1], imIn[y1 * 3][x1 * 3 + 2]);

	// int x2 = random_value2 % imIn.getWidth();
	// int y2 = random_value2 / imIn.getWidth();
	// Color c2(imIn[y2 * 3][x2 * 3 + 0], imIn[y2 * 3][x2 * 3 + 1], imIn[y2 * 3][x2 * 3 + 2]);
	// //ImageBase imOut(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	// int max_it = 25;
	// int i = 0;

	// while (changed && i < max_it) {
	// 	two_mean(k, imIn, imOut, c1, c2);
	// 	Color new_c1(0, 0, 0);
	// 	Color new_c2(0, 0, 0);
	// 	int count_c1 = 0;
	// 	int count_c2 = 0;

	// 	for (int y = 0; y < imOut.getHeight(); ++y) {
	// 		for (int x = 0; x < imOut.getWidth(); ++x) {
	// 			Color pixelColor(imOut[y * 3][x * 3 + 0], imOut[y * 3][x * 3 + 1], imOut[y * 3][x * 3 + 2]);
	// 			if (distanceCouleur(pixelColor, c1) < distanceCouleur(pixelColor, c2)) {
	// 				new_c1.R += pixelColor.R;
	// 				new_c1.G += pixelColor.G;
	// 				new_c1.B += pixelColor.B;
	// 				count_c1++;
	// 			} else {
	// 				new_c2.R += pixelColor.R;
	// 				new_c2.G += pixelColor.G;
	// 				new_c2.B += pixelColor.B;
	// 				count_c2++;
	// 			}
	// 		}
	// 	}
	// 	if (count_c1 > 0) {
	// 		new_c1.R /= count_c1;
	// 		new_c1.G /= count_c1;
	// 		new_c1.B /= count_c1;
	// 	}
	// 	if (count_c2 > 0) {
	// 		new_c2.R /= count_c2;
	// 		new_c2.G /= count_c2;
	// 		new_c2.B /= count_c2;
	// 	}
	// 	if (c1.equals(c1, new_c1) && c2.equals(c2, new_c2)) {
	// 		changed = false;
	// 	} else {
	// 		c1 = new_c1;
	// 		c2 = new_c2;
	// 	}
	// 	i++;
	// }
	std::cout << "Starting loops" << std::endl;
	for (int y = 0; y < imUnOct.getHeight(); y++)
	{
		for (int x = 0; x < imUnOct.getWidth(); x++)
		{
			Color pixelColor(imIn[y * 3][x * 3 + 0], imIn[y * 3][x * 3 + 1], imIn[y * 3][x * 3 + 2]);
			std::cout << "Pixel color chosen" << std::endl;
			int bestIndex = 0;
			std::cout << "Min distance " << std::endl;
			float minDistance = distanceCouleur(pixelColor, colors[0]);

			for (int i = 1; i < k; i++)
			{
				float dist = distanceCouleur(pixelColor, colors[i]);
				if (dist < minDistance)
				{
					minDistance = dist;
					bestIndex = i;
				}
			}
			std::cout << "Best index : " << bestIndex << std::endl;
			imUnOct[y][x] = bestIndex;
		}
	}

	ImageBase imReconstructed(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for (int y = 0; y < imUnOct.getHeight(); y++) {
		for (int x = 0; x < imUnOct.getWidth(); x++) {
			int bestIndex = imUnOct[y][x];
			imReconstructed[y * 3][x * 3 + 0] = colors[bestIndex].R;
			imReconstructed[y * 3][x * 3 + 1] = colors[bestIndex].G;
			imReconstructed[y * 3][x * 3 + 2] = colors[bestIndex].B;
		}
	}

	imReconstructed.save(cNomImgEcrite3);

	float eqm = EQM(imIn,imReconstructed);
	float psnr = PSNR(256 , eqm);
	std::cout<<"PSNR : " << psnr << std::endl;

	std::cout << "ok saving" << std::endl;
	imUnOct.save(cNomImgEcrite2);
	std::cout << "Pgm image saved" << std::endl;
	// imOut.save(cNomImgEcrite);
	// std::cout << "Ppm image saved" << std::endl;

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
