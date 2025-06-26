#include "ImageBase.h"
#include <stdio.h>
#include "fonctions.h"
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
	///////////////////////////////////////// Exemple d'un seuillage d'image


	//carte verité

	ImageBase carte;
	carte.load("img/in/echidna_carte_1.pgm");

	ImageBase realCarte(carte.getWidth() , carte.getHeight() , carte.getColor());

	seuil2(carte,realCarte, 10);
	realCarte.save("img/in/echidna_carte_real.pgm");

	//Ex 1 : créer une image gris a partir de coul
	ImageBase imIn;
	imIn.load("img/in/echidna.ppm");

	ImageBase imGrey(imIn.getWidth() , imIn.getHeight() , false);

	color_to_grey(imIn , imGrey);

	histogramme_pgm(imGrey);
	histogramme_ppm(imIn);

	imGrey.save("img/out/echidna_grey.pgm");

	//Ex 2 : Seuiller

	ImageBase imSeuil(imGrey.getWidth() , imGrey.getHeight() , imGrey.getColor());

	//seuil_pgm_auto(imGrey , imSeuil);
	seuil2(imGrey , imSeuil , 155);

	imSeuil.save("img/out/echidna_seuil155.pgm");

	//Ex 3 : flouter images

	ImageBase imBlurG(imGrey.getWidth() , imGrey.getHeight() , imGrey.getColor());
	ImageBase imBlurC(imIn.getWidth() , imIn.getHeight() , imIn.getColor());


	blur_pgm(imGrey , imBlurG);
	blur_ppm(imIn , imBlurC);

	histogramme_pgm(imBlurG);
	histogramme_ppm(imBlurC);

	imBlurG.save("img/out/echidna_blur_grey.pgm");
	imBlurC.save("img/out/echidna_blur_color.ppm");

	ImageBase imBlurBg(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	blur_bg(imIn , imSeuil , imBlurBg);
	blur_bg(imBlurBg , imSeuil , imBlurBg);
	blur_bg(imBlurBg , imSeuil , imBlurBg);
	imBlurBg.save("img/out/echidna_blur_bg.ppm");

	ImageBase imErDil(imGrey.getWidth() , imGrey.getHeight() , imGrey.getColor());
	ouverture(imSeuil , imErDil);
	imErDil.save("img/out/echidna_ouv.pgm");

	ImageBase imBlurBg2(imIn.getWidth() , imIn.getHeight() , imIn.getColor());
	blur_bg(imIn , imErDil , imBlurBg2);
	imBlurBg2.save("img/out/echidna_blur_bg2.ppm");


	ImageBase seuilTest(imGrey.getWidth() , imGrey.getHeight() , imGrey.getColor());
	
	int false_pos = 0;
	int false_neg = 0;
	int true_pos = 0;
	int true_neg = 0;
	int FPFN = 0;
	int min_FPFN = __FLT_MAX__;
	int goat_seuil = 0;


	std::ofstream datFile("results.dat");
	datFile << "grey true_pos true_neg false_pos false_neg\n";
	for(int i = 0 ; i < 256 ; i++){
		seuil2(imGrey , seuilTest , i);
		true_pos = 0;
		true_neg = 0;
		false_pos = 0;
		false_neg = 0;
		FPFN = 0;
		for(int x = 0 ; x < seuilTest.getHeight() ; x++){
			for(int y = 0 ; y < seuilTest.getWidth() ; y++){
				if(seuilTest[x][y] == realCarte[x][y] && seuilTest[x][y] == 0){
					true_pos++;
				}
				else if(seuilTest[x][y] == realCarte[x][y] && seuilTest[x][y] == 255){
					true_neg++;
				}
				else if(seuilTest[x][y] != realCarte[x][y] && seuilTest[x][y] == 0){
					false_pos++;
				}
				else if(seuilTest[x][y] != realCarte[x][y] && seuilTest[x][y] == 255){
					false_neg++;
				}
			}
		}
		FPFN = false_pos + false_neg;
		std::cout << "FPFN : " << FPFN << std::endl;
		if(FPFN < min_FPFN){
			min_FPFN = FPFN;
			goat_seuil = i;
		}
		datFile << i << " " << true_pos << " " << true_neg << " " << false_pos << " " << false_neg << "\n";
	}

	datFile.close();

	std::cout << "Goat seuil : " << goat_seuil << std::endl << "FPFN = " << min_FPFN << std::endl;


	// Calculate and store the ROC curve data into a file and give the F1 score
	std::ofstream rocFile("roc_curve.dat");
	rocFile << "Niveau De Gris Recall Precision F1\n";

	for(int i = 0 ; i < 256 ; i++){
		seuil2(imGrey , seuilTest , i);
		true_pos = 0;
		true_neg = 0;
		false_pos = 0;
		false_neg = 0;
		for(int x = 0 ; x < seuilTest.getHeight() ; x++){
			for(int y = 0 ; y < seuilTest.getWidth() ; y++){
				if(seuilTest[x][y] == realCarte[x][y] && seuilTest[x][y] == 0){
					true_pos++;
				}
				else if(seuilTest[x][y] == realCarte[x][y] && seuilTest[x][y] == 255){
					true_neg++;
				}
				else if(seuilTest[x][y] != realCarte[x][y] && seuilTest[x][y] == 0){
					false_pos++;
				}
				else if(seuilTest[x][y] != realCarte[x][y] && seuilTest[x][y] == 255){
					false_neg++;
				}
			}
		}

		double TPR = (true_pos + false_neg) != 0 ? (double)true_pos / (true_pos + false_neg) : 0;
		double FPR = (false_pos + true_neg) != 0 ? (double)false_pos / (false_pos + true_neg) : 0;
		double precision = (true_pos + false_pos) != 0 ? (double)true_pos / (true_pos + false_pos) : 0;
		double recall = (true_pos + false_neg) != 0 ? (double)true_pos / (true_pos + false_neg) : 0;

		double F1;
		if(precision+recall == 0){
			F1 = 0;
		}  
		else F1 = 2 * (precision * recall) / (precision + recall);

		rocFile << i << " " << FPR << " " << TPR << " " << F1 << "\n";
	}

	rocFile.close();

	
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


