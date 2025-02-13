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
	

	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load("img/in/spidey.pgm");

	ImageBase imSeuil(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	// seuil_pgm_auto(imIn,imSeuil);
	seuil2(imIn, imSeuil , 90);

	ImageBase imErode(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	erosion(imSeuil , imErode);

	ImageBase imDilate(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	dilatation(imSeuil , imDilate);

	ImageBase imFermeture(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	fermeture(imSeuil , imFermeture);

	ImageBase imOuverture(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	ouverture(imSeuil , imOuverture);

	ImageBase imOuvFer(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	ImageBase imTemp(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	fermeture(imSeuil,imTemp);
	ouverture(imTemp,imOuvFer);

	ImageBase imSpammed(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	spamOuvFerme(imSeuil , imSpammed);

	ImageBase imSpammed2(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	spamOuvFerme2(imSeuil , imSpammed2);

	ImageBase imOutline(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	difference(imSeuil , imDilate , imOutline);

	imSeuil.save("img/out/binary/spidey_seuil_90.pgm");
	imErode.save("img/out/binary/spidey_erode.pgm");
	imDilate.save("img/out/binary/spidey_dilat.pgm");
	imFermeture.save("img/out/binary/spidey_ferme.pgm");
	imOuverture.save("img/out/binary/spidey_ouv.pgm");
	imOuvFer.save("img/out/binary/spidey_ouvferme.pgm");
	imSpammed.save("img/out/binary/spidey_spammed.pgm");
	imSpammed2.save("img/out/binary/spidey_spammed2.pgm");
	imOutline.save("img/out/binary/spidey_outline.pgm");
	
	ImageBase imGreyEroded(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	erosion_pgm(imIn , imGreyEroded);
	imGreyEroded.save("img/out/grey/spidey_grey_eroded.pgm");

	std::cout << "we good for fun 1" << std::endl;

	ImageBase imGreyDilated(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	dilatation_pgm(imIn , imGreyDilated);
	imGreyDilated.save("img/out/grey/spidey_grey_dilated.pgm");

	std::cout << "we good for fun 2" << std::endl;

	ImageBase imGreyFermeture(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	fermeture_pgm(imIn , imGreyFermeture);
	imGreyFermeture.save("img/out/grey/spidey_grey_fermeture.pgm");

	std::cout << "we good for fun 3" << std::endl;

	ImageBase imGreyOuverture(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	ouverture_pgm(imIn , imGreyOuverture);
	imGreyOuverture.save("img/out/grey/spidey_grey_ouverture.pgm");

	std::cout << "we good for fun 4" << std::endl;

	ImageBase imGreyDifference(imIn.getHeight(), imIn.getWidth() , imIn.getColor());
	difference_pgm(imIn , imGreyDilated ,imGreyDifference);
	imGreyDifference.save("img/out/grey/spidey_grey_difference.pgm");

	std::cout << "we good for fun 5" << std::endl;

	ImageBase imColorIn;
	imColorIn.load("img/in/spidey.ppm");

	ImageBase imColorEroded(imColorIn.getHeight(), imColorIn.getWidth(), imColorIn.getColor());
	erosion_ppm(imColorIn, imColorEroded);
	imColorEroded.save("img/out/color/spidey_color_eroded.ppm");

	std::cout << "we good for fun 6" << std::endl;

	ImageBase imColorDilated(imColorIn.getHeight(), imColorIn.getWidth(), imColorIn.getColor());
	dilatation_ppm(imColorIn, imColorDilated);
	imColorDilated.save("img/out/color/spidey_color_dilated.ppm");

	std::cout << "we good for fun 7" << std::endl;

	ImageBase imColorFermeture(imColorIn.getHeight(), imColorIn.getWidth(), imColorIn.getColor());
	fermeture_ppm(imColorIn, imColorFermeture);
	imColorFermeture.save("img/out/color/spidey_color_fermeture.ppm");

	std::cout << "we good for fun 8" << std::endl;

	ImageBase imColorOuverture(imColorIn.getHeight(), imColorIn.getWidth(), imColorIn.getColor());
	ouverture_ppm(imColorIn, imColorOuverture);
	imColorOuverture.save("img/out/color/spidey_color_ouverture.ppm");

	std::cout << "we good for fun 9" << std::endl;

	ImageBase imColorDifference(imColorIn.getHeight(), imColorIn.getWidth() , imColorIn.getColor());
	difference_ppm(imColorIn , imColorDilated ,imColorDifference);
	imColorDifference.save("img/out/color/spidey_color_difference.ppm");

	std::cout << "we good for fun 10" << std::endl;



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


