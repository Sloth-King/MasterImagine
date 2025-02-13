#include "ImageBase.h"
#include <stdio.h>
#include "fonctions.h"
#include <iostream>

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image

  
	// if (argc != 4) 
	// {
	// 	printf("Usage: ImageIn.pgm L/C numL/C \n"); 
	// 	return 1;
	// }
	// sscanf (argv[1],"%s",cNomImgLue) ;
	// //sscanf (argv[2],"%s",cNomImgEcrite);
	// sscanf (argv[2], "%d" , &LC);
	// sscanf (argv[3], "%d" , &num);

	//sscanf (argv[3],"%d",&S1);
	//sscanf (argv[4],"%d",&S2);
	

	
	//ImageBase imIn, imOut;
	char cNomImgLue[256] = "img/in/baboon.pgm";
	ImageBase imInPgm;
	imInPgm.load(cNomImgLue);
	char cNomImgLue2[256] = "img/in/sloth.ppm";
	ImageBase imInPpm;
	imInPpm.load(cNomImgLue2);

	ImageBase imOut1_1(imInPgm.getHeight() , imInPgm.getWidth() , imInPgm.getColor());
	ImageBase imOut1_2(imInPgm.getHeight() , imInPgm.getWidth() , imInPgm.getColor());
	ImageBase imOut1_3(imInPgm.getHeight() , imInPgm.getWidth() , imInPgm.getColor());
	ImageBase imOut1_4(imInPgm.getHeight() , imInPgm.getWidth() , imInPgm.getColor());

	ImageBase imOut2_1(imInPgm.getHeight() , imInPgm.getWidth() , imInPgm.getColor());
	ImageBase imOut2_2(imInPgm.getHeight() , imInPgm.getWidth() , imInPgm.getColor());
	ImageBase imOut2_3(imInPgm.getHeight() , imInPgm.getWidth() , imInPgm.getColor());
	ImageBase imOut2_4(imInPgm.getHeight() , imInPgm.getWidth() , imInPgm.getColor());

	ImageBase imOut3_1(imInPpm.getHeight() , imInPpm.getWidth() , imInPpm.getColor());
	ImageBase imOut3_2(imInPpm.getHeight() , imInPpm.getWidth() , imInPpm.getColor());
	ImageBase imOut4(imInPgm.getHeight() , imInPgm.getWidth() , imInPgm.getColor());



	seuil2(imInPgm , imOut1_1 , 50);
	seuil2(imInPgm , imOut1_2 , 100);
	seuil2(imInPgm , imOut1_3 , 85);
	seuil2(imInPgm , imOut1_4 , 200);

	seuil3(imInPgm , imOut2_1 , 50 , 100 );
	seuil3(imInPgm , imOut2_2 , 110 , 215);
	seuil4(imInPgm , imOut2_3 , 50 , 100 , 150);
	seuil4(imInPgm , imOut2_4 , 60 , 120 , 180);

	profil_pgm(imInPgm , 0 , 15 , "profil1.dat");
	profil_pgm(imInPgm , 1 , 15 , "profil2.dat");

	histogramme_pgm(imInPgm);

	histogramme_ppm(imInPpm);

	seuil_ppm(imInPpm , imOut3_1, 100 , 100 , 100);
	seuil_ppm(imInPpm , imOut3_2, 50, 200 , 50);

	seuil_pgm_auto(imInPgm , imOut4);
	std::cout << seuil_pgm_auto(imInPgm , imOut4) << std::endl;

	imOut1_1.save("img/out/rendu/imOut1_1.pgm");
	imOut1_2.save("img/out/rendu/imOut1_2.pgm");
	imOut1_3.save("img/out/rendu/imOut1_3.pgm");
	imOut1_4.save("img/out/rendu/imOut1_4.pgm");

	imOut2_1.save("img/out/rendu/imOut2_1.pgm");
	imOut2_2.save("img/out/rendu/imOut2_2.pgm");
	imOut2_3.save("img/out/rendu/imOut2_3.pgm");
	imOut2_4.save("img/out/rendu/imOut2_4.pgm");

	imOut3_1.save("img/out/rendu/imOut3_1.ppm");
	imOut3_2.save("img/out/rendu/imOut3_2.ppm");

	imOut4.save("img/out/rendu/imOut4.pgm");
	
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


