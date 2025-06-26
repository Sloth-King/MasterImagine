#include "ImageBase.h"
#include <stdio.h>
#include "fonctions.h"
#include <iostream>
#include <cmath>
#include <vector>
#include "compression_video.h"
#include <map>

struct Color
{
	int R, G, B;
	Color(int r1, int g1, int b1)
	{
		R = r1;
		G = g1, B = b1;
	}
	bool equals(Color c1, Color c2)
	{
		return c1.R == c2.R && c1.G == c2.G && c1.B == c2.B;
	}
};

void seperateColor(ImageBase &imIn, ImageBase &imOutR, ImageBase &imOutG, ImageBase &imOutB)
{
	for (int y = 0; y < imIn.getHeight(); y++)
	{
		for (int x = 0; x < imIn.getWidth(); x++)
		{
			imOutR[y][x] = imIn[y * 3][x * 3 + 0]; // R
			imOutG[y][x] = imIn[y * 3][x * 3 + 1]; // G
			imOutB[y][x] = imIn[y * 3][x * 3 + 2]; // B
		}
	}
}

void reduceComponent(ImageBase &imInPgm, ImageBase &imReduced)
{
	for (int y = 0; y < imReduced.getHeight(); y++)
	{
		for (int x = 0; x < imReduced.getWidth(); x++)
		{
			int sum = imInPgm[y * 2][x * 2] + imInPgm[y * 2 + 1][x * 2] + imInPgm[y * 2][x * 2 + 1] + imInPgm[y * 2 + 1][x * 2 + 1];
			imReduced[y][x] = sum / 4;
		}
	}
}

void growImage(ImageBase &imInReduced, ImageBase &imOutGrown)
{
	for (int y = 0; y < imInReduced.getHeight(); y++)
	{
		for (int x = 0; x < imInReduced.getWidth(); x++)
		{
			imOutGrown[y * 2][x * 2] = imInReduced[y][x];
			imOutGrown[y * 2 + 1][x * 2] = imInReduced[y][x];
			imOutGrown[y * 2][x * 2 + 1] = imInReduced[y][x];
			imOutGrown[y * 2 + 1][x * 2 + 1] = imInReduced[y][x];
		}
	}
}

void reconstructImage(ImageBase &imInR, ImageBase imInG, ImageBase imInB, ImageBase &imOut)
{
	for (int y = 0; y < imOut.getHeight(); y++)
	{
		for (int x = 0; x < imOut.getWidth(); x++)
		{
			imOut[y * 3][x * 3 + 0] = imInR[y][x]; // R
			imOut[y * 3][x * 3 + 1] = imInG[y][x]; // G
			imOut[y * 3][x * 3 + 2] = imInB[y][x]; // B
		}
	}
}

float EQM(ImageBase &imIn, ImageBase &imOut)
{
	float eqm = 0.0;
	for (int y = 0; y < imIn.getHeight(); y++)
	{
		for (int x = 0; x < imIn.getWidth(); x++)
		{
			for (int c = 0; c < 3; c++)
			{
				float diff = imIn[y * 3 + c][x * 3] - imOut[y * 3 + c][x * 3];
				eqm += diff * diff;
			}
		}
	}
	eqm /= (imIn.getHeight() * imIn.getWidth() * 3);
	return eqm;
}

float EQM_gris(ImageBase &imIn, ImageBase &imOut)
{
	float eqm = 0.0;
	for (int y = 0; y < imIn.getHeight(); y++)
	{
		for (int x = 0; x < imIn.getWidth(); x++)
		{
			float diff = imIn[y][x] - imOut[y][x];
			eqm += diff * diff;
		}
	}
	eqm /= (imIn.getHeight() * imIn.getWidth());
	return eqm;
}

float PSNR(float max, float eqm)
{ // not sure walla
	return 10 * log10((max * max) / eqm);
}

void RGBtoYCrCb(ImageBase &imIn, ImageBase &imOut)
{
	for (int y = 0; y < imIn.getHeight(); y++)
	{
		for (int x = 0; x < imIn.getWidth(); x++)
		{
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

void YCrCbtoRGB(ImageBase &imIn, ImageBase &imOut)
{
	for (int y = 0; y < imIn.getHeight(); y++)
	{
		for (int x = 0; x < imIn.getWidth(); x++)
		{
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

void seperateYCrCb(ImageBase &imIn, ImageBase &imOutY, ImageBase &imOutCr, ImageBase &imOutCb)
{
	for (int y = 0; y < imIn.getHeight(); y++)
	{
		for (int x = 0; x < imIn.getWidth(); x++)
		{
			imOutY[y][x] = imIn[y * 3][x * 3 + 0];	// Y
			imOutCr[y][x] = imIn[y * 3][x * 3 + 1]; // Cr
			imOutCb[y][x] = imIn[y * 3][x * 3 + 2]; // Cb
		}
	}
}

void reduceCrCb(ImageBase &imInCr, ImageBase &imInCb, ImageBase &imReducedCr, ImageBase &imReducedCb)
{
	for (int y = 0; y < imReducedCr.getHeight(); y++)
	{
		for (int x = 0; x < imReducedCr.getWidth(); x++)
		{
			int sumCr = imInCr[y * 2][x * 2] + imInCr[y * 2 + 1][x * 2] + imInCr[y * 2][x * 2 + 1] + imInCr[y * 2 + 1][x * 2 + 1];
			int sumCb = imInCb[y * 2][x * 2] + imInCb[y * 2 + 1][x * 2] + imInCb[y * 2][x * 2 + 1] + imInCb[y * 2 + 1][x * 2 + 1];
			imReducedCr[y][x] = sumCr / 4;
			imReducedCb[y][x] = sumCb / 4;
		}
	}
}

std::vector<std::vector<float>> matrix_mul(std::vector<std::vector<float>> m1 , std::vector<std::vector<float>> m2){
	std::vector<std::vector<float>> result(m1.size() , std::vector<float>(m2.size()));
	for(int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m2[0].size(); j++) {
			float sum = 0;
			for (int k = 0; k < m1[0].size(); k++) {
				sum += m1[i][k] * m2[k][j];
			}
			result[i][j] = sum;
		}
	}
	return result;
}

std::vector<std::vector<float>> matrix_scalaire(std::vector<std::vector<float>> m1 , std::vector<std::vector<float>> m2 ){
	std::vector<std::vector<float>> out = m1;
	for(int i = 0 ; i < m1.size() ; i++){
		for(int j = 0 ; j < m1[0].size() ; j++){
			out[i][j] = m1[i][j] * m2[i][j];
		}
	}
	return out;
}

std::vector<std::vector<float>> matrixMultiplyFloat(std::vector<std::vector<float>> m , float x){
	std::vector<std::vector<float>> out = m;
	for(int i = 0 ; i < m.size() ; i++){
		for(int j = 0 ; j < m[0].size() ; j++){
			out[i][j] = m[i][j] * x;
		}
	}
	return out;	
}

// Add this function before main()

size_t calculateYUVBinarySize(ImageBase& yImage, ImageBase& crImage, ImageBase& cbImage, int numFrames, bool subsample = false) {
	size_t ySize = yImage.getWidth() * yImage.getHeight() * 8; // 8 bits per pixel

	size_t crSize, cbSize;
	if (subsample) {
		// 4:2:0 subsampling - chroma at half resolution in both dimensions
		crSize = (crImage.getWidth() / 2) * (crImage.getHeight() / 2) * 8;
		cbSize = (cbImage.getWidth() / 2) * (cbImage.getHeight() / 2) * 8;
	} else {
		// 4:4:4 - full resolution chroma
		crSize = crImage.getWidth() * crImage.getHeight() * 8;
		cbSize = cbImage.getWidth() * cbImage.getHeight() * 8;
	}

	// Total size for all frames in bits
	return numFrames * (ySize + crSize + cbSize);
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

	// Load the two frames to simulate a video
	// Have them be slightly different
	ImageBase frame1;
	frame1.load("img/in/frog1.ppm");

	ImageBase frame2;
	frame2.load("img/in/frog2.ppm");

	// 1)a) Convert to YCrCb

	ImageBase frame1_ycrcb(frame1.getWidth(), frame1.getHeight(), frame1.getColor());
	ImageBase frame2_ycrcb(frame2.getWidth(), frame2.getHeight(), frame2.getColor());

	RGBtoYCrCb(frame1, frame1_ycrcb);
	RGBtoYCrCb(frame2, frame2_ycrcb);

	frame1_ycrcb.save("img/out/frame1YCrCB.ppm");
	frame2_ycrcb.save("img/out/frame2YCrCB.ppm");

	// seperate to use just Y component.

	ImageBase frame1_y(frame1.getWidth(), frame1.getHeight(), false);
	ImageBase frame1_cr(frame1.getWidth(), frame1.getHeight(), false);
	ImageBase frame1_cb(frame1.getWidth(), frame1.getHeight(), false);

	seperateYCrCb(frame1_ycrcb, frame1_y, frame1_cr, frame1_cb);

	ImageBase frame2_y(frame2.getWidth(), frame2.getHeight(), false);
	ImageBase frame2_cr(frame2.getWidth(), frame2.getHeight(), false);
	ImageBase frame2_cb(frame2.getWidth(), frame2.getHeight(), false);

	seperateYCrCb(frame2_ycrcb, frame2_y, frame2_cr, frame2_cb);

	frame1_y.save("img/out/frame1Y.pgm");
	frame1_cr.save("img/out/frame1Cr.pgm");
	frame1_cb.save("img/out/frame1Cb.pgm");

	// 1)b)c) INTRA_16x16 Vertical and Horizontal

	ImageBase frame1_intra_v(frame1_y.getWidth(), frame1_y.getHeight(), frame1_y.getColor());
	ImageBase frame1_intra_h(frame1_y.getWidth(), frame1_y.getHeight(), frame1_y.getColor());

	std::vector<std::vector<Block>> vert_blocks = intra_16x16_vertical(frame1_y, 16);
	std::vector<std::vector<Block>> hori_blocks = intra_16x16_horizontal(frame1_y, 16);
	std::vector<std::vector<Block>> base_blocks = getBlocksMat(frame1_y, 16);

	reconstructImageFromBlocks(frame1_intra_v, vert_blocks);
	reconstructImageFromBlocks(frame1_intra_h, hori_blocks);

	frame1_intra_v.save("img/out/frame1IntraVertical.pgm");
	frame1_intra_h.save("img/out/frame1IntraHorizontal.pgm");

	// 1)d)e) Carte

	ImageBase frame1_map(frame1_y.getWidth(), frame1_y.getHeight(), frame1_y.getColor());

	blockDistMap(base_blocks, vert_blocks, hori_blocks, frame1_y, frame1_map);
	frame1_map.save("img/out/frame1DistanceMap.pgm");

	// 2)A)

	std::vector<std::vector<float>> DCTint1 = {
		{1.f, 1.f, 1.f, 1.f},
		{2.f, 1.f, -1.f, -2.f},
		{1.f, -1.f, -1.f, 1.f},
		{1.f, -2.f, 2.f, -1.f}
	};

	std::vector<std::vector<float>> DCTint2 = {
		{1.f, 2.f, 1.f, 1.f},
		{1.f, 1.f, -1.f, -2.f},
		{1.f, -1.f, -1.f, 2.f},
		{1.f, -2.f, 1.f, -1.f}
	};

	float a = 1.f/2.f;
	float b = sqrt(2.f/5.f);

	std::vector<std::vector<float>> scalingMatrix = {
		{a*a, a*b/2 , a*a, a*b/2},
		{a*b/2, b*b/4, a*b/2, b*b/4},
		{a*a, a*b/2, a*a, a*b/2},
		{a*b/2, b*b/4, a*b/2, b*b/4}
	};

	//create 4x4 blocks 
	std::vector<std::vector<Block>> small_blocks = getBlocksMat(frame1_y , 4);
	std::vector<std::vector<float>> dct;

	for (int i = 0; i < small_blocks.size(); i++) {
		for (int j = 0; j < small_blocks[i].size(); j++) {
			std::vector<std::vector<float>> x = small_blocks[i][j].data;
			std::vector<std::vector<float>> temp = matrix_mul(DCTint1, matrix_mul(x, DCTint2));
			std::vector<std::vector<float>> result = matrix_scalaire(temp, scalingMatrix);
			dct.insert(dct.end(), result.begin(), result.end());
		}
	}	

	std::map<int , int> histo;
	for (int i = 0 ; i < dct.size() ; i++) {
		for (int j = 0 ; j < dct[0].size() ; j++) {
			int value = (int) dct[i][j];
			histo[value]++;
		}
	}

	//2)b)

	//iterate over a map : https://stackoverflow.com/questions/26281979/how-do-you-loop-through-a-stdmap
	std::ofstream outFile("dct.dat");
	if (outFile.is_open()) {
		for (auto const& [key, count] : histo) {
			outFile << key << " " << count << "\n";
		}
		outFile.close();
	} else {
		std::cerr << "Unable to open file for writing: dct.dat" << std::endl;
	}

	//2)c)

	//split into subblocsk
	std::vector<std::vector<Block>> subBlocks = splitIntoSubBlocks(vert_blocks , 4);
	std::cout << "split done" << std::endl;
	std::vector<std::vector<float>> dct_predicted;

	for (int i = 0; i < subBlocks.size(); i++) {
		for (int j = 0; j < subBlocks[i].size(); j++) {
			std::vector<std::vector<float>> x = subBlocks[i][j].data;
			std::vector<std::vector<float>> temp = matrix_mul(DCTint1, matrix_mul(x, DCTint2));
			std::vector<std::vector<float>> result = matrix_scalaire(temp, scalingMatrix);
			dct_predicted.insert(dct_predicted.end(), result.begin(), result.end());
		}
	}	

	std::cout << "dct done" << std::endl;

	std::map<int , int> histo_predicted;
	for (int i = 0 ; i < dct_predicted.size() ; i++) {
		for (int j = 0 ; j < dct_predicted[0].size() ; j++) {
			int value = (int) dct_predicted[i][j];
			histo_predicted[value]++;
		}
	}
	std::cout << "histo done" << std::endl;

	//iterate over a map : https://stackoverflow.com/questions/26281979/how-do-you-loop-through-a-stdmap
	std::ofstream outFile2("dct2.dat");
	if (outFile2.is_open()) {
		for (auto const& [key, count] : histo_predicted) {
			outFile2 << key << " " << count << "\n";
		}
		outFile2.close();
	} else {
		std::cerr << "Unable to open file for writing: dct2.dat" << std::endl;
	}
	std::cout << "file done" << std::endl;

	//2)d)

	//IDCT now or something

	std::vector<std::vector<float>> IDCTint1 = {
		{1.f, 1.f, 1.f, 1.f/2.f},
		{1.f, 1.f/2.f , -1.f, -1.f},
		{1.f, -1.f/2.f, -1.f, 1.f},
		{1.f, -1.f, 1.f, -1.f/2.f}
	};

	std::vector<std::vector<float>> IDCTint2 = {
		{1.f, 1.f, 1.f, 1.f},
		{1.f, 1.f/2.f , -1.f/2.f, -1.f},
		{1.f, -1.f, -1.f, 1.f},
		{1.f/2.f, -1.f, 1.f, -1.f/2.f}
	};

	//THIS std::vector<std::vector<float>> result = matrix_mul(matrix_mul(matrix_scalaire(x, scalingMatrix), IDCTint1), IDCTint2);

	// Create a vector of blocks for IDCT
    std::vector<std::vector<Block>> idct_blocks = getBlocksMat(frame1_y, 4); // Start with same block structure
    
    // Apply IDCT to each block
    for (int i = 0; i < small_blocks.size(); i++) {
        for (int j = 0; j < small_blocks[i].size(); j++) {
            std::vector<std::vector<float>> x = small_blocks[i][j].data;
            
            // First apply the quantization matrix (inverse of scaling)
            std::vector<std::vector<float>> quantized_x = matrix_scalaire(x, scalingMatrix);
            
            // Apply IDCT formula: IDCT = IDCTint1 * X * IDCTint2
            std::vector<std::vector<float>> result = matrix_mul(matrix_mul(IDCTint1, quantized_x), IDCTint2);
            
            // Store result back into block structure
            idct_blocks[i][j].data = result;
        }
    }

    ImageBase reconstructed(frame1_y.getWidth(), frame1_y.getHeight(), frame1_y.getColor());
    reconstructImageFromBlocks(reconstructed, idct_blocks);
    reconstructed.save("img/out/frame1IDCT.pgm");

	//3)a) 
	//Quantification Qcp

	std::vector<float> qstep;
	qstep.push_back(0.625);
	for(int qp = 1 ; qp < 52 ; qp++){
		float val = qstep[qp-1] * pow(2.,1./6); 
		qstep.push_back(val);
	}

	//create 4x4 blocks 
	std::vector<std::vector<float>> dct3;

	std::vector<std::vector<float>> scalem2 = matrixMultiplyFloat(scalingMatrix , qstep[50]);

	for (int i = 0; i < small_blocks.size(); i++) {
		for (int j = 0; j < small_blocks[i].size(); j++) {
			std::vector<std::vector<float>> x = small_blocks[i][j].data;
			std::vector<std::vector<float>> temp = matrix_mul(DCTint1, matrix_mul(x, DCTint2));
			std::vector<std::vector<float>> result = matrix_scalaire(temp, scalem2);
			dct3.insert(dct3.end(), result.begin(), result.end());
		}
	}	

	std::map<int , int> histo3;
	for (int i = 0 ; i < dct3.size() ; i++) {
		for (int j = 0 ; j < dct3[0].size() ; j++) {
			int value = (int) dct3[i][j];
			histo3[value]++;
		}
	}
	
	std::ofstream outFile3("dct3.dat");
	if (outFile3.is_open()) {
		for (auto const& [key, count] : histo3) {
			outFile3 << key << " " << count << "\n";
		}
		outFile3.close();
	} else {
		std::cerr << "Unable to open file for writing: dct2.dat" << std::endl;
	}
	std::cout << "file done" << std::endl;


	//6)a)
	//size 

	

	std::cout << "Frame 1 : " << calculateYUVBinarySize(frame1_y , frame1_cr , frame1_cb , 2 ) << std::endl;
	std::cout << "Frame 2 : " << calculateYUVBinarySize(frame2_y , frame2_cr , frame2_cb , 2 ) << std::endl;


	///////////////////////////////////////// Exemple de cr�ation d'une image couleur
	ImageBase imC(50, 100, true);

	for (int y = 0; y < imC.getHeight(); ++y)
		for (int x = 0; x < imC.getWidth(); ++x)
		{
			imC[y * 3][x * 3 + 0] = 200; // R
			imC[y * 3][x * 3 + 1] = 0;	 // G
			imC[y * 3][x * 3 + 2] = 0;	 // B
		}

	imC.save("imC.ppm");

	///////////////////////////////////////// Exemple de cr�ation d'une image en niveau de gris
	ImageBase imG(50, 100, false);

	for (int y = 0; y < imG.getHeight(); ++y)
		for (int x = 0; x < imG.getWidth(); ++x)
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
