#include <iostream>
#include <fstream> 
#include <vector>
#include "ImageBase.h"
#include <algorithm>

enum Axis{
    x,
    y,
    z
};

struct Image{
    
    int dimX;
    int dimY;
    int dimZ;
    std::vector<unsigned int> data;

    Image(){
        dimX = 0;
        dimY = 0;
        dimZ = 0;
        data = std::vector<unsigned int>();
    }
    Image( int idimX , int idimY , int idimZ){
        dimX = idimX;
        dimY = idimY;
        dimZ = idimZ;
        data = std::vector<unsigned int>(dimX * dimY * dimZ);
    }

    unsigned int getValue(int i, int j, int k){
        return data[k * (dimY * dimX) + j * dimX + i];
    }
    
    unsigned int getMaxValue() {
        unsigned int maxVal = 0;
        for (const auto& val : data) {
            if (val > maxVal) {
                maxVal = val;
            }
        }
        return maxVal;
    }

    unsigned int getMinValue(){
        unsigned int minVal = 0;
        for (const auto& val : data) {
            if (val < minVal) {
                minVal = val;
            }
        }
        return minVal;
    }
};

Image read_img_file(const char* filename, int dimX, int dimY, int dimZ) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Open broke " << filename << std::endl;
        return Image();
    }

    Image img(dimX, dimY, dimZ);
    int totalSize = dimX * dimY * dimZ;
    img.data.resize(totalSize);

    std::vector<uint8_t> buffer(totalSize * 2);
    file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

    for (size_t i = 0; i < buffer.size(); i += 2) {
        img.data[i/2] = (unsigned short) (buffer[i]) * 256 + buffer[i + 1];
    }

    file.close();
    std::cout << "Image data successfully read from " << filename << std::endl;
    return img;
}

void create_aip_image(Image imIn , ImageBase &imOut, Axis axis){
    int dimX = imIn.dimX;
    int dimY = imIn.dimY;
    int dimZ = imIn.dimZ;
    float cpt = 0;

    if (axis == Axis::z) {
        imOut = ImageBase(dimX, dimY , false);
        for (int i = 0; i < dimX; ++i) {
            for (int j = 0; j < dimY; ++j) {
                unsigned int avgVal = 0;
                cpt = 0;
                for (int k = 0; k < dimZ; ++k) {
                    avgVal += imIn.getValue(i,j,k);
                    cpt++;
                }
                avgVal /= cpt;
                imOut[j][i] = std::clamp((int)avgVal, 0, 255);
            }
        }
    } else if (axis == Axis::y) {
        imOut = ImageBase(dimX, dimZ , false);
        for (int i = 0; i < dimX; ++i) {
            for (int k = 0; k < dimZ; ++k) {
                unsigned int avgVal = 0;
                cpt = 0;
                for (int j = 0; j < dimY; ++j) {
                    avgVal += imIn.getValue(i,j,k);
                    cpt++;                
                }
                avgVal /= cpt;
                imOut[k][i] = std::clamp((int)avgVal, 0, 255);
            }
        }
    } else if (axis == Axis::x) {
        imOut = ImageBase(dimY, dimZ , false);
        for (int j = 0; j < dimY; ++j) {
            for (int k = 0; k < dimZ; ++k) {
                unsigned int avgVal = 0;
                cpt = 0;
                for (int i = 0; i < dimX; ++i) {
                    avgVal += imIn.getValue(i,j,k);
                    cpt++;
                }
                avgVal /= cpt;
                imOut[k][j] = std::clamp((int)avgVal, 0, 255);
            }
        }
    }
}

void create_mip_image(Image imIn , ImageBase &imOut, Axis axis){
    int dimX = imIn.dimX;
    int dimY = imIn.dimY;
    int dimZ = imIn.dimZ;

    if (axis == Axis::z) {
        imOut = ImageBase(dimX, dimY , false);
        for (int i = 0; i < dimX; ++i) {
            for (int j = 0; j < dimY; ++j) {
                unsigned int maxVal = 0;
                for (int k = 0; k < dimZ; ++k) {
                    maxVal = std::max(maxVal, imIn.getValue(i, j, k));
                }
                imOut[j][i] = std::clamp((int)maxVal, 0, 255);
            }
        }
    } else if (axis == Axis::y) {
        imOut = ImageBase(dimX, dimZ , false);
        for (int i = 0; i < dimX; ++i) {
            for (int k = 0; k < dimZ; ++k) {
                unsigned int maxVal = 0;
                for (int j = 0; j < dimY; ++j) {
                    maxVal = std::max(maxVal, imIn.getValue(i, j, k));
                }
                imOut[k][i] = std::clamp((int)maxVal, 0, 255);
            }
        }
    } else if (axis == Axis::x) {
        imOut = ImageBase(dimY, dimZ , false);
        for (int j = 0; j < dimY; ++j) {
            for (int k = 0; k < dimZ; ++k) {
                unsigned int maxVal = 0;
                for (int i = 0; i < dimX; ++i) {
                    maxVal = std::max(maxVal, imIn.getValue(i, j, k));
                }
                imOut[k][j] = std::clamp((int)maxVal, 0, 255);
            }
        }
    }
}


int main(int argc , char* argv){

    std::cout << "word is bond" << std::endl;

    char* filename = "img/orange.256x256x64.0.3906x0.3906x1.0.img";
    int dimX = 256;
    int dimY = 256;
    int dimZ = 64;

    Image im = read_img_file(filename , dimX , dimY , dimZ);
    // for(int i = 0 ; i < 256*256*64 ; i++){
    //     std::cout << (unsigned int)im.data[i] <<std::endl;
    // }
    //std::cout << "val : "<< im.getValue(158,143,64) << std::endl;
    std::cout << "max : " << im.getMaxValue() << std::endl;
    std::cout << "min : " << im.getMinValue() << std::endl;

    ImageBase imOut;
    create_aip_image(im , imOut , Axis::z);
    imOut.save("orange_aip_z.pgm");
    
    char* file2 = "img/whatisit.208x208x123.1.0x1.0x1.0.img";
    int dimX_2 = 208;
    int dimY_2 = 208;
    int dimZ_2 = 123;

    Image im1 = read_img_file(file2 , dimX_2 , dimY_2 , dimZ_2);

    ImageBase imOut1;
    ImageBase imOut2;
    ImageBase imOut3;
    ImageBase imOut4;
    ImageBase imOut5;
    ImageBase imOut6;

    create_aip_image(im1 , imOut1 , x);
    imOut1.save("wat_aip_x.pgm");
    create_aip_image(im1 , imOut2 , y);
    imOut2.save("wat_aip_y.pgm");
    create_aip_image(im1 , imOut3 , z);
    imOut3.save("wat_aip_z.pgm");
    create_mip_image(im1 , imOut4 , x);
    imOut4.save("wat_mip_x.pgm");
    create_aip_image(im1 , imOut5 , y);
    imOut5.save("wat_mip_y.pgm");
    create_aip_image(im1 , imOut6 , z);
    imOut6.save("wat_mip_z.pgm");

    return 0;
}