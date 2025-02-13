#include "ImageBase.h"
#include <iostream>
#include <string>
#include <fstream>

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

void histogramme_pgm(ImageBase &imIn){
    std::ofstream out("histo.dat");
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
