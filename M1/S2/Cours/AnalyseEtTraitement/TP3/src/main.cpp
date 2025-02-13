#include "ImageBase.h"
#include <stdio.h>
#include "fonctions.h"
#include <iostream>

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image

  
	//In case i want command line input
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
	

	//Ex 1
	// ImageBase imIn;
	// imIn.load("img/in/black.pgm");
	
	// ImageBase imOut(imIn.getWidth() , imIn.getHeight() , imIn.getColor());

	// expansion_dynamique(imIn , imOut);

	// imOut.save("img/out/blackp.pgm");

	// ImageBase imIn2;
	// imIn2.load("img/in/black.ppm");
	
	// ImageBase imOut2(imIn2.getWidth() , imIn2.getHeight() , imIn2.getColor());

	// expansion_dynamique_ppm(imIn2 , imOut2);

	// imOut2.save("img/out/blackp.ppm");	

	//Ex 2
	ImageBase imIn2;
	imIn2.load("img/in/kirkdik.ppm");

	ImageBase imOut(imIn2.getWidth() , imIn2.getHeight() , imIn2.getColor());

	auto_seuil_smin_smax(imIn2 , imOut);

	ImageBase imOut2(imOut.getWidth() , imOut.getHeight() , imOut.getColor());

	expansion_dynamique_ppm(imOut , imOut2);

	imOut2.save("img/out/dikdikseuil.ppm");

	//Ex3
	ImageBase imIn3;
	imIn3.load("img/in/cuttlefish.pgm");

	ImageBase imOut3(imIn3.getWidth() , imIn3.getHeight() , imIn3.getColor());
	egalisation_pgm(imIn3 ,imOut3 , "cuttle_ddp.dat");
	imOut3.save("img/out/egalisation.pgm");

	// Ex4:
	ImageBase imIn4;
	imIn4.load("img/in/cuttlefish.pgm");
	ImageBase imLena;

	imLena.load("img/in/lena.pgm");
	ImageBase imLeEqual(imLena.getWidth(),imLena.getHeight(),imLena.getColor());
	std::vector<float> f_r = egalisation_pgm(imLena,imLeEqual);
	save_repartition(f_r,"lena_function.dat");

	histogramme_pgm(imLena , "histo_lena.dat");

	ImageBase imOut4(imIn4.getWidth(), imIn4.getHeight(), imIn4.getColor());

	specification_pgm(imIn4, imOut4 , f_r);
	histogramme_pgm(imOut4 , "histo_spec.dat");
	imOut4.save("img/out/specification.pgm");

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


