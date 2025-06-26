#include "ImageBase.h"
#include <stdio.h>
#include "fonctions.h"
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image

	//Gradient
	ImageBase imIn;
	imIn.load("img/in/toucan.pgm");

	ImageBase imGradient(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	gradient(imIn , imGradient);

	profil_pgm(imIn , 0 , 52 , "image_profil.dat");
	profil_pgm(imGradient , 0 , 52 , "gradient_profil.dat");

	imGradient.save("img/out/toucan_gradient.pgm");

	//Seuils

	ImageBase imSeuil(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	ImageBase imSeuil2(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	ImageBase imSeuil3(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	ImageBase imSeuil4(imIn.getWidth() , imIn.getHeight() , imIn.getColor());


	seuil_pgm_auto(imGradient , imSeuil);
	seuil2(imGradient , imSeuil2 , 20);
	seuil2(imGradient , imSeuil3 , 90);
	seuil2(imGradient , imSeuil4 , 130);

	imSeuil.save("img/out/toucan_gradient_seuil.pgm");
	imSeuil2.save("img/out/toucan_gradient_seuil2.pgm");
	imSeuil3.save("img/out/toucan_gradient_seuil3.pgm");
	imSeuil4.save("img/out/toucan_gradient_seuil4.pgm");

	//Hystérésis

	ImageBase imHysterisis(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	ImageBase imHysterisis2(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	ImageBase imHysterisis3(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	ImageBase imHysterisis4(imIn.getWidth() , imIn.getHeight() , imIn.getColor());


	hysteresis(imGradient , imHysterisis , 97 , 65);
	hysteresis(imGradient , imHysterisis2 , 130 , 65);
	hysteresis(imGradient , imHysterisis3 , 65 , 20);
	hysteresis(imGradient , imHysterisis4 , 65 , 50);

	imHysterisis.save("img/out/toucan_gradient_hyst.pgm");
	imHysterisis2.save("img/out/toucan_gradient_hyst2.pgm");
	imHysterisis3.save("img/out/toucan_gradient_hyst3.pgm");
	imHysterisis4.save("img/out/toucan_gradient_hyst4.pgm");

	//Blur

	ImageBase imBlur(imIn.getWidth() , imIn.getHeight() , imIn.getColor());

	blur_pgm(imIn , imBlur);
	
	imBlur.save("img/out/toucan_blur.pgm");

	ImageBase imBlurGradient(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	gradient(imBlur , imBlurGradient);

	profil_pgm(imBlur , 0 , 52 , "blur_profil.dat");
	profil_pgm(imBlurGradient , 0 , 52 , "blur_gradient_profil.dat");

	imBlurGradient.save("img/out/toucan_blur_gradient.pgm");


	ImageBase imBlurSeuil(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	seuil2(imBlurGradient , imBlurSeuil , 65);
	imBlurSeuil.save("img/out/toucan_blur_seuil.pgm");

	ImageBase imBlurHyst(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	hysteresis(imBlurGradient , imBlurHyst , 65 , 50);
	imBlurHyst.save("img/out/toucan_blur_hyst.pgm");

	//Laplacien

	ImageBase imLaplace(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	laplace(imIn, imLaplace);
	imLaplace.save("img/out/toucan_laplace.pgm");

	ImageBase imLaplace2(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	laplace(imGradient, imLaplace2);
	imLaplace2.save("img/out/toucan_laplace2.pgm");


	//Detection 0
	ImageBase imZero(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	detection_zero2(imLaplace , imZero);
	imZero.save("img/out/toucan_zero.pgm");

	//hysteresis
	ImageBase imZeroHyst(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	hysteresis(imZero, imZeroHyst, 65, 50);
	imZeroHyst.save("img/out/toucan_zero_hyst.pgm");

	// Detection 0 for laplace2
	ImageBase imZero2(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	detection_zero2(imLaplace2 , imZero2);
	imZero2.save("img/out/toucan_zero2.pgm");

	// hysteresis for laplace2
	ImageBase imZeroHyst2(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	hysteresis(imZero2, imZeroHyst2, 65, 50);
	imZeroHyst2.save("img/out/toucan_zero_hyst2.pgm");

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


