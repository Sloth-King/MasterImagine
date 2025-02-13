#include "ImageBase.h"
#include <iostream>
#include <string>
#include <fstream>

void seuil2(ImageBase * imIn, ImageBase * imOut, int S1){
    for(int x = 0; x < imIn->getHeight(); ++x)
        for(int y = 0; y < imIn->getWidth(); ++y)
        {
            int pixel = (*imIn)[x][y];
            if (pixel < S1)
                (*imOut)[x][y] = 0;
            else (*imOut)[x][y] = 255;
        }

}

void seuil3(ImageBase * imIn, ImageBase * imOut, int S1, int S2){
    for(int x = 0; x < imIn->getHeight(); x++){
            for(int y = 0; y < imIn->getWidth(); y++){
                int pixel = (*imIn)[x][y];

                if(pixel < S1){
                    (*imOut)[x][y] = 0;
                }else if (pixel < S2){
                    (*imOut)[x][y] = 128;
                }else{
                    (*imOut)[x][y] = 255;
                }

            }
        }
}

void seuil4(ImageBase * imIn, ImageBase * imOut, int S1, int S2, int S3){
    for(int x = 0; x < imIn->getHeight(); x++){
            for(int y = 0; y < imIn->getWidth(); y++){
                int pixel = (*imIn)[x][y];

                if(pixel < S1){
                    (*imOut)[x][y] = 0;
                }else if (pixel < S2){
                    (*imOut)[x][y] = 85;
                }else if (pixel < S3){
                    (*imOut)[x][y] = 170;
                }else{
                    (*imOut)[x][y] = 255;
                }

            }
        }
}

void profil_pgm(ImageBase & imIn , int type , int numLC){ //type is line (0) or culumn (1)
    std::ofstream out("profil.dat");
    if(out.is_open()){
        if(type == 0){
            std::cout << "huh" << std::endl;
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
    else std::cout << "oh.." << std::endl;
    out.close();
}