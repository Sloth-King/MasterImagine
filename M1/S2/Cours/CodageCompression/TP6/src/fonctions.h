#pragma once
#include "ImageBase.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

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

void histogramme_pgm(ImageBase &imIn, std::vector<int> &greyVal , bool save = 1){
    greyVal.resize(256, 0);
    if(save){
        std::ofstream out("histo.dat");
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

// ------------------------------------------------------------------------------------------------------------------------
// Codage predictif et huffman

float entropy_pgm(ImageBase &imIn){
    float H = 0;

    //Calculate the probabilities
    int N = imIn.getHeight()*imIn.getWidth();
    std::vector<int> histo;
    histogramme_pgm(imIn, histo , 0);
    std::vector<float> p;
    for(int i = 0 ; i < histo.size() ; i++){
        if(histo[i] != 0){
            p.push_back((float)histo[i]/N);
        }

    }

    //calculate the entropy
    for(int i = 0 ; i < p.size() ; i++){
        H+=p[i] * log2(p[i]);
    }
    return -H;
}

void carte_diff(ImageBase &imIn , ImageBase &imOut, int type){
    float A, B , C;
    for(int x = 1; x < imIn.getHeight(); x++){
        for(int y = 1; y < imIn.getWidth(); y++){
            float p_shapo;
            A = imIn[x-1][y];
            B = imIn[x-1][y-1];
            C = imIn[x][y-1];
            switch(type){
                case 0 : 
                    p_shapo = A;
                    break;
                case 1 :
                    p_shapo = (A+C)/2;
                    break;
                case 2 :
                    p_shapo = (A+B)/2;
                    break;
                case 3 : 
                    p_shapo = A+C-B;
                    break;
                case 4 :
                    p_shapo = (3*(A+C) - 2*B)/4;  
                    break;              
            }
            imOut[x][y] = imIn[x][y] - p_shapo + 128;
        }
    }
}

// ------------------------------------------------------------------------------------------------------------------------
//Ondelettes

void transform_ondelettes(ImageBase &imIn ,ImageBase &imBF , ImageBase &imMFh , ImageBase &imMFv , ImageBase &imHF){
    int A , B , C , D;
    
    for(int x = 0; x < imIn.getHeight(); x+=2){
        for(int y = 0; y < imIn.getWidth(); y+=2){
            A = imIn[x][y];
            B = imIn[x][y+1];
            C = imIn[x+1][y];
            D = imIn[x+1][y+1];
            
            imBF[x/2][y/2] = (A+B+C+D)/4;
            imMFh[x/2][y/2] = (A+B-C-D)/2 + 128;
            imMFv[x/2][y/2] = (A-B+C-D)/2 + 128;
            imHF[x/2][y/2] = A-B-C+D + 128;
        }
    }
}

void reconstruct_ondelettes(ImageBase &imBF , ImageBase &imMFh , ImageBase &imMFv , ImageBase &imHF , ImageBase &imOut){
    int A , B , C , D;
    for(int x = 0; x < imBF.getHeight(); x++){
        for(int y = 0; y < imBF.getWidth(); y++){
            A = (imBF[x][y]) + ((imMFh[x][y] - 128) / 2.0f) + ((imMFv[x][y] - 128)/2.0f) + ((imHF[x][y] - 128) / 4.0f) ;
            B = (imBF[x][y]) + ((imMFh[x][y] - 128) / 2.0f) - ((imMFv[x][y] - 128)/2.0f) - ((imHF[x][y] - 128) / 4.0f) ;
            C = (imBF[x][y]) - ((imMFh[x][y] - 128) / 2.0f) + ((imMFv[x][y] - 128)/2.0f) - ((imHF[x][y] - 128) / 4.0f) ;
            D = (imBF[x][y]) - ((imMFh[x][y] - 128) / 2.0f) - ((imMFv[x][y] - 128)/2.0f) + ((imHF[x][y] - 128) / 4.0f) ;

            imOut[x*2][y*2] = std::clamp(A , 0 , 255);
            imOut[x*2][(y*2)+1] = std::clamp(B , 0 , 255);
            imOut[(x*2)+1][y*2] = std::clamp(C , 0 , 255);
            imOut[(x*2)+1][(y*2)+1] = std::clamp(D , 0 , 255);
        }
    }    
}

void quantification_q(ImageBase &imBF , ImageBase &imMFh , ImageBase &imMFv , ImageBase &imHF , int qBF , int qMFh , int qMFv , int qHF){
    for(int x = 0; x < imBF.getHeight(); x++){
        for(int y = 0; y < imBF.getWidth(); y++){
            imBF[x][y] = imBF[x][y] / qBF;
            imMFh[x][y] = imMFh[x][y] / qMFh;
            imMFv[x][y] = imMFv[x][y] / qMFv;
            imHF[x][y] = imHF[x][y] / qHF;
        }
    }
}

void inverse_quantification_q(ImageBase &imBF , ImageBase &imMFh , ImageBase &imMFv , ImageBase &imHF , int qBF , int qMFh , int qMFv , int qHF){
    for(int x = 0; x < imBF.getHeight(); x++){
        for(int y = 0; y < imBF.getWidth(); y++){
            imBF[x][y] = imBF[x][y] * qBF;
            imMFh[x][y] = imMFh[x][y] * qMFh;
            imMFv[x][y] = imMFv[x][y] * qMFv;
            imHF[x][y] = imHF[x][y] * qHF;
        }
    }
}

void reconstruct_ondelettes_recursive(ImageBase &imIn, ImageBase &imOut, int N) {
    std::cout << "Reconstruction Iteration: " << N << std::endl;

    int halfHeight = imIn.getHeight() / 2;
    int halfWidth = imIn.getWidth() / 2;

    ImageBase BF(halfWidth, halfHeight, imIn.getColor());
    ImageBase MFh(halfWidth, halfHeight, imIn.getColor());
    ImageBase MFv(halfWidth, halfHeight, imIn.getColor());
    ImageBase HF(halfWidth, halfHeight, imIn.getColor());

    for (int x = 0; x < halfHeight; x++) {
        for (int y = 0; y < halfWidth; y++) {
            BF[x][y] = imIn[x][y];
            MFh[x][y] = imIn[x][y + halfWidth];
            MFv[x][y] = imIn[x + halfHeight][y];
            HF[x][y] = imIn[x + halfHeight][y + halfWidth];
        }
    }

    if (N > 1) {
        reconstruct_ondelettes_recursive(BF, BF, N - 1);
    }

    int A, B, C, D;
    for (int x = 0; x < halfHeight; x++) {
        for (int y = 0; y < halfWidth; y++) {
            A = (BF[x][y]) + ((MFh[x][y] - 128) / 2.0f) + ((MFv[x][y] - 128) / 2.0f) + ((HF[x][y] - 128) / 4.0f);
            B = (BF[x][y]) + ((MFh[x][y] - 128) / 2.0f) - ((MFv[x][y] - 128) / 2.0f) - ((HF[x][y] - 128) / 4.0f);
            C = (BF[x][y]) - ((MFh[x][y] - 128) / 2.0f) + ((MFv[x][y] - 128) / 2.0f) - ((HF[x][y] - 128) / 4.0f);
            D = (BF[x][y]) - ((MFh[x][y] - 128) / 2.0f) - ((MFv[x][y] - 128) / 2.0f) + ((HF[x][y] - 128) / 4.0f);

            imOut[x * 2][y * 2] = std::clamp(A, 0, 255);
            imOut[x * 2][(y * 2) + 1] = std::clamp(B, 0, 255);
            imOut[(x * 2) + 1][y * 2] = std::clamp(C, 0, 255);
            imOut[(x * 2) + 1][(y * 2) + 1] = std::clamp(D, 0, 255);
        }
    }
}

void ondelettes_recursive(ImageBase &imIn , ImageBase &imOut , int N){

    std::cout << "Iteration : " << N << std::endl;

    int A , B , C , D;
    int halfHeight = imIn.getHeight() / 2;
    int halfWidth = imIn.getWidth() / 2;

    ImageBase BF(imIn.getWidth()/2, imIn.getHeight()/2 , imIn.getColor());
    ImageBase MFh(imIn.getWidth()/2 , imIn.getHeight()/2 , imIn.getColor());
    ImageBase MFv(imIn.getWidth()/2 , imIn.getHeight()/2 , imIn.getColor());
    ImageBase HF(imIn.getWidth()/2, imIn.getHeight()/2 , imIn.getColor());

    for(int x = 0; x < imIn.getHeight(); x+=2){
        for(int y = 0; y < imIn.getWidth(); y+=2){
            A = imIn[x][y];
            B = imIn[x][y+1];
            C = imIn[x+1][y];
            D = imIn[x+1][y+1];

            BF[x/2][y/2] = (A+B+C+D)/4;
            MFh[x/2][y/2] = (A+B-C-D)/2 + 128;
            MFv[x/2][y/2] = (A-B+C-D)/2 + 128;
            HF[x/2][y/2] = A-B-C+D + 128;
        }
    }

    if(N>1){
        ondelettes_recursive(BF , BF , N-1);
    }

    for(int x = 0; x < imIn.getHeight(); x+=2){
        for(int y = 0; y < imIn.getWidth(); y+=2){
            int newX = x / 2;
            int newY = y / 2;

            imOut[newX][newY] = BF[x/2][y/2];
            imOut[newX][newY + halfWidth] = MFh[x/2][y/2];
            imOut[newX + halfHeight][newY] = MFv[x/2][y/2]; 
            imOut[newX + halfHeight][newY + halfWidth] = HF[x/2][y/2]; 
        }
    }
}

void transform_ondelettes_ppm(ImageBase &imIn, ImageBase &imBF, ImageBase &imMFh, ImageBase &imMFv, ImageBase &imHF) {
    int A, B, C, D;
    
    for (int x = 0; x < imIn.getHeight(); x += 2) {
        for (int y = 0; y < imIn.getWidth(); y += 2) {
            for (int c = 0; c < 3; c++) {
                A = imIn[x * 3][y * 3 + c];
                B = imIn[x * 3][(y + 1) * 3 + c];
                C = imIn[(x + 1) * 3][y * 3 + c];
                D = imIn[(x + 1) * 3][(y + 1) * 3 + c];
                
                imBF[(x / 2) * 3][(y / 2) * 3 + c] = (A + B + C + D) / 4;
                imMFh[(x / 2) * 3][(y / 2) * 3 + c] = (A + B - C - D) / 2 + 128;
                imMFv[(x / 2) * 3][(y / 2) * 3 + c] = (A - B + C - D) / 2 + 128;
                imHF[(x / 2) * 3][(y / 2) * 3 + c] = A - B - C + D + 128;
            }
        }
    }
}

void reconstruct_ondelettes_ppm(ImageBase &imBF, ImageBase &imMFh, ImageBase &imMFv, ImageBase &imHF, ImageBase &imOut) {
    int A, B, C, D;
    
    for (int x = 0; x < imBF.getHeight(); x++) {
        for (int y = 0; y < imBF.getWidth(); y++) {
            for (int c = 0; c < 3; c++) {
                A = imBF[x * 3][y * 3 + c] + ((imMFh[x * 3][y * 3 + c] - 128) / 2.0f) + ((imMFv[x * 3][y * 3 + c] - 128) / 2.0f) + ((imHF[x * 3][y * 3 + c] - 128) / 4.0f);
                B = imBF[x * 3][y * 3 + c] + ((imMFh[x * 3][y * 3 + c] - 128) / 2.0f) - ((imMFv[x * 3][y * 3 + c] - 128) / 2.0f) - ((imHF[x * 3][y * 3 + c] - 128) / 4.0f);
                C = imBF[x * 3][y * 3 + c] - ((imMFh[x * 3][y * 3 + c] - 128) / 2.0f) + ((imMFv[x * 3][y * 3 + c] - 128) / 2.0f) - ((imHF[x * 3][y * 3 + c] - 128) / 4.0f);
                D = imBF[x * 3][y * 3 + c] - ((imMFh[x * 3][y * 3 + c] - 128) / 2.0f) - ((imMFv[x * 3][y * 3 + c] - 128) / 2.0f) + ((imHF[x * 3][y * 3 + c] - 128) / 4.0f);

                imOut[(x * 2) * 3][(y * 2) * 3 + c] = std::clamp(A, 0, 255);
                imOut[(x * 2) * 3][(y * 2 + 1) * 3 + c] = std::clamp(B, 0, 255);
                imOut[(x * 2 + 1) * 3][(y * 2) * 3 + c] = std::clamp(C, 0, 255);
                imOut[(x * 2 + 1) * 3][(y * 2 + 1) * 3 + c] = std::clamp(D, 0, 255);
            }
        }
    }
}
void ondelettes_recursive_ppm(ImageBase &imIn, ImageBase &imOut, int N) {
    std::cout << "Iteration: " << N << std::endl;

    int halfHeight = imIn.getHeight() / 2;
    int halfWidth = imIn.getWidth() / 2;

    ImageBase BF(halfWidth, halfHeight, imIn.getColor());
    ImageBase MFh(halfWidth, halfHeight, imIn.getColor());
    ImageBase MFv(halfWidth, halfHeight, imIn.getColor());
    ImageBase HF(halfWidth, halfHeight, imIn.getColor());

    for (int x = 0; x < imIn.getHeight(); x += 2) {
        for (int y = 0; y < imIn.getWidth(); y += 2) {
            for (int c = 0; c < 3; c++) {
                int A = imIn[(x * 3)][(y * 3) + c];
                int B = imIn[(x * 3)][((y + 1) * 3) + c];
                int C = imIn[((x + 1) * 3)][(y * 3) + c];
                int D = imIn[((x + 1) * 3)][((y + 1) * 3) + c];

                BF[(x / 2) * 3][(y / 2) * 3 + c] = (A + B + C + D) / 4;
                MFh[(x / 2) * 3][(y / 2) * 3 + c] = (A + B - C - D) / 2 + 128;
                MFv[(x / 2) * 3][(y / 2) * 3 + c] = (A - B + C - D) / 2 + 128;
                HF[(x / 2) * 3][(y / 2) * 3 + c] = A - B - C + D + 128;
            }
        }
    }

    if (N > 1) {
        ondelettes_recursive_ppm(BF, BF, N - 1);
    }

    for (int x = 0; x < halfHeight; x++) {
        for (int y = 0; y < halfWidth; y++) {
            for (int c = 0; c < 3; c++) {
                imOut[(x * 3)][(y * 3) + c] = BF[(x * 3)][(y * 3) + c];
                imOut[(x * 3)][((y + halfWidth) * 3) + c] = MFh[(x * 3)][(y * 3) + c];
                imOut[((x + halfHeight) * 3)][(y * 3) + c] = MFv[(x * 3)][(y * 3) + c];
                imOut[((x + halfHeight) * 3)][((y + halfWidth) * 3) + c] = HF[(x * 3)][(y * 3) + c];
            }
        }
    }
}

void reconstruct_ondelettes_recursive_ppm(ImageBase &imIn, ImageBase &imOut, int N) {
    std::cout << "Reconstruction Iteration: " << N << std::endl;

    int halfHeight = imIn.getHeight() / 2;
    int halfWidth = imIn.getWidth() / 2;

    ImageBase BF(halfWidth, halfHeight, imIn.getColor());
    ImageBase MFh(halfWidth, halfHeight, imIn.getColor());
    ImageBase MFv(halfWidth, halfHeight, imIn.getColor());
    ImageBase HF(halfWidth, halfHeight, imIn.getColor());

    for (int x = 0; x < halfHeight; x++) {
        for (int y = 0; y < halfWidth; y++) {
            for (int c = 0; c < 3; c++) {
                BF[(x * 3)][(y * 3) + c] = imIn[(x * 3)][(y * 3) + c];
                MFh[(x * 3)][(y * 3) + c] = imIn[(x * 3)][((y + halfWidth) * 3) + c];
                MFv[(x * 3)][(y * 3) + c] = imIn[((x + halfHeight) * 3)][(y * 3) + c];
                HF[(x * 3)][(y * 3) + c] = imIn[((x + halfHeight) * 3)][((y + halfWidth) * 3) + c];
            }
        }
    }

    if (N > 1) {
        reconstruct_ondelettes_recursive_ppm(BF, BF, N - 1);
    }

    int A, B, C, D;
    for (int x = 0; x < halfHeight; x++) {
        for (int y = 0; y < halfWidth; y++) {
            for (int c = 0; c < 3; c++) {
                A = BF[(x * 3)][(y * 3) + c] + ((MFh[(x * 3)][(y * 3) + c] - 128) / 2.0f) + ((MFv[(x * 3)][(y * 3) + c] - 128) / 2.0f) + ((HF[(x * 3)][(y * 3) + c] - 128) / 4.0f);
                B = BF[(x * 3)][(y * 3) + c] + ((MFh[(x * 3)][(y * 3) + c] - 128) / 2.0f) - ((MFv[(x * 3)][(y * 3) + c] - 128) / 2.0f) - ((HF[(x * 3)][(y * 3) + c] - 128) / 4.0f);
                C = BF[(x * 3)][(y * 3) + c] - ((MFh[(x * 3)][(y * 3) + c] - 128) / 2.0f) + ((MFv[(x * 3)][(y * 3) + c] - 128) / 2.0f) - ((HF[(x * 3)][(y * 3) + c] - 128) / 4.0f);
                D = BF[(x * 3)][(y * 3) + c] - ((MFh[(x * 3)][(y * 3) + c] - 128) / 2.0f) - ((MFv[(x * 3)][(y * 3) + c] - 128) / 2.0f) + ((HF[(x * 3)][(y * 3) + c] - 128) / 4.0f);

                imOut[((x * 2) * 3)][((y * 2) * 3) + c] = std::clamp(A, 0, 255);
                imOut[((x * 2) * 3)][((y * 2 + 1) * 3) + c] = std::clamp(B, 0, 255);
                imOut[((x * 2 + 1) * 3)][((y * 2) * 3) + c] = std::clamp(C, 0, 255);
                imOut[((x * 2 + 1) * 3)][((y * 2 + 1) * 3) + c] = std::clamp(D, 0, 255);
            }
        }
    }
}
