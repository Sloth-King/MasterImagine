#include "ImageBase.h"
#include <stdio.h>
#include "fonctions.h"
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image

	ImageBase colorMap;
	colorMap.load("img/in/colormap.ppm");
	ImageBase imIn;
	imIn.load("img/in/input.pgm");

	ImageBase identifierMap(colorMap.getWidth() , colorMap.getHeight() , false);

	colormap_to_identifiermap(colorMap , identifierMap , 24);
	identifierMap.save("img/out/identifierMap.pgm");

	ImageBase avgPerRegion(imIn.getWidth() , imIn.getHeight() , false);
	synthesize_avg(imIn , identifierMap , avgPerRegion);
	avgPerRegion.save("img/out/synthesized_avg.pgm");




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


