#include "ImageBase.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void seuil2(ImageBase &imIn, ImageBase &imOut, int S1){
    for(int x = 0; x < imIn.getHeight(); ++x)
        for(int y = 0; y < imIn.getWidth(); ++y)
        {
            int pixel = imIn[x][y];
            if (pixel < S1)
                imOut[x][y] = 0;
            else imOut[x][y] = 255;
        }

}

void seuil3(ImageBase &imIn, ImageBase &imOut, int S1, int S2){
    for(int x = 0; x < imIn.getHeight(); x++){
            for(int y = 0; y < imIn.getWidth(); y++){
                int pixel = imIn[x][y];

                if(pixel < S1){
                    imOut[x][y] = 0;
                }else if (pixel < S2){
                    imOut[x][y] = 128;
                }else{
                    imOut[x][y] = 255;
                }

            }
        }
}

void seuil4(ImageBase &imIn, ImageBase &imOut, int S1, int S2, int S3){
    for(int x = 0; x < imIn.getHeight(); x++){
            for(int y = 0; y < imIn.getWidth(); y++){
                int pixel = imIn[x][y];

                if(pixel < S1){
                    imOut[x][y] = 0;
                }else if (pixel < S2){
                    imOut[x][y] = 85;
                }else if (pixel < S3){
                    imOut[x][y] = 170;
                }else{
                    imOut[x][y] = 255;
                }

            }
        }
}

void profil_pgm(ImageBase & imIn , int type , int numLC , char *fileName){ //type is line (0) or culumn (1)
    std::ofstream out(fileName);
    if(out.is_open()){
        if(type == 0){
            for(int i = 0 ; i < imIn.getWidth() ; i++){
                out << i << " " << (int) imIn[numLC][i] << "\n";
            }
        }
        if(type == 1){
            for(int i = 0 ; i < imIn.getHeight() ; i++){
                out << i << " " << (int) imIn[i][numLC] << "\n";
            } 
        }
    }
    out.close();
}

void histogramme_pgm(ImageBase &imIn , char* filename="histo.dat"){
    std::ofstream out(filename);
    int greyVal[256] = {0};
    for(int x = 0; x < imIn.getHeight(); x++){
        for(int y = 0; y < imIn.getWidth(); y++){
            greyVal[imIn[x][y]]++;
        }
    }
    for(int i = 0; i < 256 ; i++){
        out << i << " " << greyVal[i] << "\n";
    }
    out.close();
}

void histogramme_pgm(ImageBase &imIn, std::vector<int> &greyVal , bool save = 1 , char *fileName = "histo.dat"){
    greyVal.resize(256, 0);
    if(save){
        std::ofstream out(fileName);
        for(int x = 0; x < imIn.getHeight(); x++){
            for(int y = 0; y < imIn.getWidth(); y++){
                greyVal[imIn[x][y]]++;
            }
        }
        for(int i = 0; i < 256 ; i++){
            out << i << " " << greyVal[i] << "\n";
        }
        out.close();
    }
    else{
        for(int x = 0; x < imIn.getHeight(); x++){
            for(int y = 0; y < imIn.getWidth(); y++){
                greyVal[imIn[x][y]]++;
            }
        }
    }
}

void histogramme_ppm(ImageBase &imIn){
    std::ofstream out("histo_ppm.dat");
    int redVal[256] = {0};
    int greenVal[256] = {0};
    int blueVal[256] = {0};

    for(int x = 0; x < imIn.getHeight(); x++){
        for(int y = 0; y < imIn.getWidth(); y++){
            redVal[imIn[x*3][y*3]]++;
            greenVal[imIn[x*3][y*3+1]]++;
            blueVal[imIn[x*3][y*3+2]]++;
        }
    }

    for(int i = 0; i < 256; i++){
        out << i << " " << redVal[i] << " " << greenVal[i] << " " << blueVal[i] << "\n";
    }
    out.close();
}

void histogramme_ppm(ImageBase &imIn , std::vector<int> &histoR , std::vector<int> &histoG, std::vector<int> &histoB, bool save = true, char *fileName = "histo_ppm.dat") {
    histoR.resize(256, 0);
    histoG.resize(256, 0);
    histoB.resize(256, 0);

    if (save) {
        std::ofstream out(fileName);
        for (int x = 0; x < imIn.getHeight(); x++) {
            for (int y = 0; y < imIn.getWidth(); y++) {
                histoR[imIn[x * 3][y * 3]]++;
                histoG[imIn[x * 3][y * 3 + 1]]++;
                histoB[imIn[x * 3][y * 3 + 2]]++;
            }
        }
        for (int i = 0; i < 256; i++) {
            out << i << " " << histoR[i] << " " << histoG[i] << " " << histoB[i] << "\n";
        }
        out.close();
    } else {
        for (int x = 0; x < imIn.getHeight(); x++) {
            for (int y = 0; y < imIn.getWidth(); y++) {
                histoR[imIn[x * 3][y * 3]]++;
                histoG[imIn[x * 3][y * 3 + 1]]++;
                histoB[imIn[x * 3][y * 3 + 2]]++;
            }
        }
    }
}

void seuil_ppm(ImageBase &imIn , ImageBase &imOut, int sR , int sG , int sB){
    for(int x = 0; x < imIn.getHeight(); x++){
        for(int y = 0; y < imIn.getWidth(); y++){
            if(imIn[x*3][y*3+0] < sR) imOut[x*3][y*3+0] = 0;
            else imOut[x*3][y*3+0] = 255;
            if(imIn[x*3][y*3+1] < sG) imOut[x*3][y*3+1] = 0;
            else imOut[x*3][y*3+1] = 255;
            if(imIn[x*3][y*3+2] < sB) imOut[x*3][y*3+2] = 0;
            else imOut[x*3][y*3+2] = 255;
        }
    }
}

int seuil_pgm_auto(ImageBase &imIn , ImageBase &imOut){
    int histo[256] = {0};
    int totalPixels = imIn.getHeight() * imIn.getWidth();
    int sum = 0, sumB = 0, q1 = 0, q2 = 0;
    float varMax = 0;
    int seuil = 0;

    for(int x = 0; x < imIn.getHeight(); x++){
        for(int y = 0; y < imIn.getWidth(); y++){
            histo[imIn[x][y]]++;
        }
    }

    for(int i = 0 ; i < 256 ; i++){
        sum += i * histo[i];
    }

    for(int t = 0 ; t < 256 ; t++){
        q1 += histo[t];
        if(q1 == 0) continue;
        q2 = totalPixels - q1;

        sumB += t * histo[t];
        float mu1 = (float)sumB / q1;
        float mu2 = (float)(sum - sumB) / q2;

        float varBetween = (float)q1 * q2 * (mu1 - mu2) * (mu1 - mu2);

        if(varBetween > varMax){
            varMax = varBetween;
            seuil = t;
        }
    }

    for(int x = 0; x < imIn.getHeight(); x++){
        for(int y = 0; y < imIn.getWidth(); y++){
            if(imIn[x][y] < seuil) imOut[x][y] = 0;
            else imOut[x][y] = 255;
        }
    }

    return seuil;
}   

//--------------------------------------------
//Operations Morphologies d'une image binaire

void erosion(ImageBase &imIn , ImageBase &imOut){
    for(int x = 1 ; x < imIn.getHeight()-1 ; x++){
        for(int y = 1 ; y < imIn.getWidth()-1 ; y++){
            imOut[x][y] = imIn[x][y];
            if(imIn[x][y+1]==255 || imIn[x+1][y]==255 || imIn[x-1][y]==255 || imIn[x][y-1]==255){
                imOut[x][y] = 255;
            }
        }
    }
}

void dilatation(ImageBase &imIn , ImageBase &imOut){
    for(int x = 1 ; x < imIn.getHeight()-1 ; x++){
        for(int y = 1 ; y < imIn.getWidth()-1 ; y++){
            imOut[x][y] = imIn[x][y];
            if(imIn[x][y+1]==0 || imIn[x+1][y]==0 || imIn[x-1][y]==0 || imIn[x][y-1]==0){
                imOut[x][y] = 0;
            }
        }
    }
}

void fermeture(ImageBase &imIn , ImageBase &imOut){
    ImageBase imTemp(imIn.getHeight(),imIn.getWidth(),imIn.getColor());
    dilatation(imIn , imTemp);
    erosion(imTemp , imOut);
}

void ouverture(ImageBase &imIn , ImageBase &imOut){
    ImageBase imTemp(imIn.getHeight(),imIn.getWidth(),imIn.getColor());
    erosion(imIn , imTemp);
    dilatation(imTemp , imOut);
}

void spamOuvFerme(ImageBase &imIn, ImageBase &imOut) {
    ImageBase imTemp1(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
    ImageBase imTemp2(imIn.getHeight(), imIn.getWidth(), imIn.getColor());

    dilatation(imIn, imTemp1);
    dilatation(imTemp1, imTemp2);
    dilatation(imTemp2, imTemp1);

    erosion(imTemp1, imTemp2);
    erosion(imTemp2, imTemp1);
    erosion(imTemp1, imTemp2);
    erosion(imTemp2, imTemp1);
    erosion(imTemp1, imTemp2);
    erosion(imTemp2, imTemp1);

    dilatation(imTemp1, imTemp2);
    dilatation(imTemp2, imTemp1);
    dilatation(imTemp1, imOut);
}

void spamOuvFerme2(ImageBase &imIn, ImageBase &imOut) {
    ImageBase imTemp1(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
    ImageBase imTemp2(imIn.getHeight(), imIn.getWidth(), imIn.getColor());
    
    erosion(imIn, imTemp1);
    erosion(imTemp1, imTemp2);
    erosion(imTemp2, imTemp1);

    dilatation(imTemp1, imTemp2);
    dilatation(imTemp2, imTemp1);
    dilatation(imTemp1, imTemp2);
    dilatation(imTemp2, imTemp1);
    dilatation(imTemp1, imTemp2);
    dilatation(imTemp2, imTemp1);

    erosion(imTemp1, imTemp2);
    erosion(imTemp2, imTemp1);
    erosion(imTemp1, imOut);
}

void difference(ImageBase &imIn, ImageBase &imDilat , ImageBase &imOut){
    for(int x = 1 ; x < imIn.getHeight()-1 ; x++){
        for(int y = 1 ; y < imIn.getWidth()-1 ; y++){
            if(imIn[x][y]==imDilat[x][y]){
                imOut[x][y]=0;
            }
            else{
                imOut[x][y] = 255;
            }
        } 
    }
}

// ----------------------------------------------------------------------------------------------------------------------
//Op morpho d'une image en 256 niveaux de gris 

void erosion_pgm(ImageBase &imIn , ImageBase &imOut){
    for(int x = 1 ; x < imIn.getHeight()-1 ; x++){
        for(int y = 1 ; y < imIn.getWidth()-1 ; y++){
            int minVal = 255;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (imIn[x + i][y + j] < minVal) {
                        minVal = imIn[x + i][y + j];
                    }
                }
            }
            imOut[x][y] = minVal;
        }
    }
}

void dilatation_pgm(ImageBase &imIn , ImageBase &imOut){
    for(int x = 1 ; x < imIn.getHeight()-1 ; x++){
        for(int y = 1 ; y < imIn.getWidth()-1 ; y++){
            int maxVal = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (imIn[x + i][y + j] > maxVal) {
                        maxVal = imIn[x + i][y + j];
                    }
                }
            }
            imOut[x][y] = maxVal;
        }
    }
}

void fermeture_pgm(ImageBase &imIn , ImageBase &imOut){
    ImageBase imTemp(imIn.getHeight(),imIn.getWidth(),imIn.getColor());
    dilatation_pgm(imIn , imTemp);
    erosion_pgm(imTemp , imOut);
}

void ouverture_pgm(ImageBase &imIn , ImageBase &imOut){
    ImageBase imTemp(imIn.getHeight(),imIn.getWidth(),imIn.getColor());
    erosion_pgm(imIn , imTemp);
    dilatation_pgm(imTemp , imOut);
}

void difference_pgm(ImageBase &imIn, ImageBase &imDilat, ImageBase &imOut) {
    for (int x = 1; x < imIn.getHeight() - 1; x++) {
        for (int y = 1; y < imIn.getWidth() - 1; y++) {
            int diff = abs(imIn[x][y] - imDilat[x][y]);
            imOut[x][y] = diff;
        }
    }
}


// ----------------------------------------------------------------------------------------------------------------------
//Op morpho d'une image RGB

void erosion_ppm(ImageBase &imIn, ImageBase &imOut) {
    for (int x = 1; x < imIn.getHeight() - 1; x++) {
        for (int y = 1; y < imIn.getWidth() - 1; y++) {
            int minR = 255, minG = 255, minB = 255;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int r = imIn[(x + i) * 3][(y + j) * 3 + 0];
                    int g = imIn[(x + i) * 3][(y + j) * 3 + 1];
                    int b = imIn[(x + i) * 3][(y + j) * 3 + 2];
                    if (r < minR) minR = r;
                    if (g < minG) minG = g;
                    if (b < minB) minB = b;
                }
            }
            imOut[x * 3][y * 3 + 0] = minR;
            imOut[x * 3][y * 3 + 1] = minG;
            imOut[x * 3][y * 3 + 2] = minB;
        }
    }
}

void dilatation_ppm(ImageBase &imIn, ImageBase &imOut) {
    for (int x = 1; x < imIn.getHeight() - 1; x++) {
        for (int y = 1; y < imIn.getWidth() - 1; y++) {
            int maxR = 0, maxG = 0, maxB = 0;
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int r = imIn[(x + i) * 3][(y + j) * 3 + 0];
                    int g = imIn[(x + i) * 3][(y + j) * 3 + 1];
                    int b = imIn[(x + i) * 3][(y + j) * 3 + 2];
                    if (r > maxR) maxR = r;
                    if (g > maxG) maxG = g;
                    if (b > maxB) maxB = b;
                }
            }
            imOut[x * 3][y * 3 + 0] = maxR;
            imOut[x * 3][y * 3 + 1] = maxG;
            imOut[x * 3][y * 3 + 2] = maxB;
        }
    }
}

void fermeture_ppm(ImageBase &imIn , ImageBase &imOut){
    ImageBase imTemp(imIn.getHeight(),imIn.getWidth(),imIn.getColor());
    dilatation_ppm(imIn , imTemp);
    erosion_ppm(imTemp , imOut);
}

void ouverture_ppm(ImageBase &imIn , ImageBase &imOut){
    ImageBase imTemp(imIn.getHeight(),imIn.getWidth(),imIn.getColor());
    erosion_ppm(imIn , imTemp);
    dilatation_ppm(imTemp , imOut);
}

void difference_ppm(ImageBase &imIn, ImageBase &imDilat, ImageBase &imOut) {
    for (int x = 1; x < imIn.getHeight() - 1; x++) {
        for (int y = 1; y < imIn.getWidth() - 1; y++) {
            int diffR = abs(imIn[x * 3][y * 3 + 0] - imDilat[x * 3][y * 3 + 0]);
            int diffG = abs(imIn[x * 3][y * 3 + 1] - imDilat[x * 3][y * 3 + 1]);
            int diffB = abs(imIn[x * 3][y * 3 + 2] - imDilat[x * 3][y * 3 + 2]);
            imOut[x * 3][y * 3 + 0] = diffR;
            imOut[x * 3][y * 3 + 1] = diffG;
            imOut[x * 3][y * 3 + 2] = diffB;
        }
    }
}

//Spec d'histo

int get_x1(std::vector<int> histo){
    for(int i = 0 ; i < histo.size() ; i++){
        if(histo[i] != 0){
            return i;
        }
    }
}

int get_x2(std::vector<int> histo){
    for(int i = histo.size()-1 ; i >= 0 ; i--){
        if(histo[i] != 0){
            return i;
        }
    }
}

int get_alpha(int x1 , int x2){return (int)(-255*x1)/(x2-x1);}
int get_beta(int x1 , int x2){return (int)(255)/(x2-x1);}


void expansion_dynamique(ImageBase &imIn , ImageBase &imOut){
    std::vector<int> histo; 
    histogramme_pgm(imIn , histo , 1 , "histo_unexpanded.dat");

    int x1 = get_x1(histo);
    int x2 = get_x2(histo);
    int alpha = get_alpha(x1,x2);
    int beta = get_beta(x1,x2);

    for(int x = 0; x < imIn.getHeight(); x++){
        for(int y = 0; y < imIn.getWidth(); y++){
            int pixel = imIn[x][y];
            int newPixel = alpha + beta * pixel;
            if (newPixel < 0) newPixel = 0;
            if (newPixel > 255) newPixel = 255;
            imOut[x][y] = newPixel;
        }
    }
    histogramme_pgm(imOut , histo , 1 , "histo_expanded.dat");
}

void expansion_dynamique_ppm(ImageBase &imIn, ImageBase &imOut) {
    std::vector<int> histoR, histoG, histoB;
    histogramme_ppm(imIn, histoR, histoG, histoB, true , "histo_unexpanded_ppm.dat");

    // for (int i = 0; i < 256; i++) {
    //     std::cout << "R: " << histoR[i] << " G: " << histoG[i] << " B: " << histoB[i] << std::endl;
    // }

    int x1R = get_x1(histoR);
    int x2R = get_x2(histoR);
    int alphaR = get_alpha(x1R, x2R);
    int betaR = get_beta(x1R, x2R);

    int x1G = get_x1(histoG);
    int x2G = get_x2(histoG);
    int alphaG = get_alpha(x1G, x2G);
    int betaG = get_beta(x1G, x2G);

    int x1B = get_x1(histoB);
    int x2B = get_x2(histoB);
    int alphaB = get_alpha(x1B, x2B);
    int betaB = get_beta(x1B, x2B);

    for (int x = 0; x < imIn.getHeight(); x++) {
        for (int y = 0; y < imIn.getWidth(); y++) {
            int pixelR = imIn[x * 3][y * 3 + 0];
            int newPixelR = alphaR + betaR * pixelR;
            if (newPixelR < 0) newPixelR = 0;
            if (newPixelR > 255) newPixelR = 255;
            imOut[x * 3][y * 3 + 0] = newPixelR;

            int pixelG = imIn[x * 3][y * 3 + 1];
            int newPixelG = alphaG + betaG * pixelG;
            if (newPixelG < 0) newPixelG = 0;
            if (newPixelG > 255) newPixelG = 255;
            imOut[x * 3][y * 3 + 1] = newPixelG;

            int pixelB = imIn[x * 3][y * 3 + 2];
            int newPixelB = alphaB + betaB * pixelB;
            if (newPixelB < 0) newPixelB = 0;
            if (newPixelB > 255) newPixelB = 255;
            imOut[x * 3][y * 3 + 2] = newPixelB;
        }
    }
    histogramme_ppm(imOut);
}

void save_histogram_from_array(std::vector<int> greyValues , char *filename){
    std::ofstream out(filename);
    if (out.is_open()) {
        for (int i = 0; i < greyValues.size(); ++i) {
            out << i << " " << greyValues[i] << "\n";
        }
        out.close();
    } else {
        std::cerr << "Unable to open file " << filename << std::endl;
    }
}

void auto_seuil_smin_smax(ImageBase &imIn , ImageBase &imOut){
    std::vector<int> histoR, histoG, histoB;
    histogramme_ppm(imIn, histoR, histoG, histoB, true , "histo_original_ppm.dat");
    save_histogram_from_array(histoR , "histo_r_original.dat");
    save_histogram_from_array(histoG , "histo_g_original.dat");
    save_histogram_from_array(histoB , "histo_b_original.dat");

    int minValR = 255, maxValR = 0;
    int minValG = 255, maxValG = 0;
    int minValB = 255, maxValB = 0;
    for (int i = 0; i < 256; i++) {
        if (histoR[i] > 0) {
            if (i < minValR) minValR = i;
            if (i > maxValR) maxValR = i;
        }
        if (histoG[i] > 0) {
            if (i < minValG) minValG = i;
            if (i > maxValG) maxValG = i;
        }
        if (histoB[i] > 0) {
            if (i < minValB) minValB = i;
            if (i > maxValB) maxValB = i;
        }
    }

    std::cout << "minVal R: " << minValR << " maxVal R: " << maxValR << std::endl;
    std::cout << "minVal G: " << minValG << " maxVal G: " << maxValG << std::endl;
    std::cout << "minVal B: " << minValB << " maxVal B: " << maxValB << std::endl;

    for (int x = 0; x < imIn.getHeight(); x++) {
        for (int y = 0; y < imIn.getWidth(); y++) {
            int pixelR = imIn[x * 3][y * 3 + 0];
            if (pixelR < minValR) pixelR = minValR;
            else if (pixelR > maxValR) pixelR = maxValR;
            imOut[x * 3][y * 3 + 0] = pixelR;

            int pixelG = imIn[x * 3][y * 3 + 1];
            if (pixelG < minValG) pixelG = minValG;
            else if (pixelG > maxValG) pixelG = maxValG;
            imOut[x * 3][y * 3 + 1] = pixelG;

            int pixelB = imIn[x * 3][y * 3 + 2];
            if (pixelB < minValB) pixelB = minValB;
            else if (pixelB > maxValB) pixelB = maxValB;
            imOut[x * 3][y * 3 + 2] = pixelB;
        }
    }

    std::vector<int> histoRNew, histoGNew, histoBNew;
    histogramme_ppm(imOut, histoRNew, histoGNew, histoBNew, true, "histo_seuil_ppm.dat");
    save_histogram_from_array(histoRNew, "histo_r_expanded.dat");
    save_histogram_from_array(histoGNew, "histo_g_expanded.dat");
    save_histogram_from_array(histoBNew, "histo_b_expanded.dat");

}

void save_repartition(std::vector<float> f_rep , char* filename = "f_rep.dat"){
    std::ofstream out(filename);
    if (out.is_open()) {
        for (int i = 0; i < f_rep.size(); ++i) {
            out << i << " " << f_rep[i] << "\n";
        }
        out.close();
    } else {
        std::cerr << "Unable to open file f_rep.dat" << std::endl;
    }
}

std::vector<float> egalisation_pgm(ImageBase &imIn , ImageBase &imOut , char* ddpname="ddp.dat"){
    std::vector<int> histo(256, 0);
    histogramme_pgm(imIn, histo, true , "histo_cuttle.dat");

    int totalPixels = imIn.getHeight() * imIn.getWidth();
    std::vector<float> f_rep(256, 0.0);

    std::vector<float> ddp(256, 0.0);
    for (int i = 0; i < 256; i++) {
        ddp[i] = (float)histo[i] / totalPixels;
    }
    f_rep[0] = ddp[0];

    for (int i = 1; i < 256; i++) {
        f_rep[i] = f_rep[i - 1] + ddp[i];
    }

    for (int x = 0; x < imIn.getHeight(); x++) {
        for (int y = 0; y < imIn.getWidth(); y++) {
            int pixel = imIn[x][y];
            int newPixel = f_rep[pixel]*255;
            imOut[x][y] = newPixel;
        }
    }

    save_repartition(ddp , ddpname);

    //histogramme_pgm(imOut, histo, true, "histo_equalized.dat");
    return f_rep;
}


void specification_pgm(ImageBase &imIn , ImageBase &imOut , std::vector<float> f_in_rep){ //f_rep is the fonction de repartition of the other image (here imma use lena)
    std::vector<float> f_rep = egalisation_pgm(imIn , imOut);
    save_repartition(f_rep,"specification_function.dat");
    float val;
    //egalisation inverse avec f_in_rep 
    for (int x = 0; x < imIn.getHeight(); x++) {
        for (int y = 0; y < imIn.getWidth(); y++) {
            val = (float)imIn[x][y]/255;
            for(int i = 0 ; i < 256 ; i++){
                if(f_in_rep[i] >= val){
                    imOut[x][y] = i;
                    break;
                }
            }
        }
    }
}

