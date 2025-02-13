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