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

void extract_iso_surface(Image imIn, int seuil, float sizeX, float sizeY, float sizeZ, char* outputFileName){

    std::ofstream outputFile(outputFileName);
    if (!outputFile) {
        std::cerr << "Failed to create output file." << std::endl;
        return;
    }

    for(int i = 0 ; i < imIn.dimX; i++){
        for(int j = 0 ; j < imIn.dimY ; j++){
            for(int k = 0 ; k < imIn.dimZ ; k++){

                //coins
                float x1 = (i-0.5)*sizeX;
                float x2 = (i+0.5)*sizeX;

                float y1 = (j-0.5)*sizeY;
                float y2 = (j+0.5)*sizeY;   

                float z1 = (k-0.5)*sizeZ;
                float z2 = (k+0.5)*sizeZ;       

                float val = imIn.getValue(i,j,k);

                std::vector<std::vector<float>> vertices{
                    {x1, y1, z1},
                    {x2, y1, z1},
                    {x1, y2, z1},
                    {x2, y2, z1},
                    {x1, y1, z2},
                    {x2, y1, z2},
                    {x1, y2, z2},
                    {x2, y2, z2}
                };   

                if(val > seuil){
                    
                    if (i > 0 && imIn.getValue(i - 1, j, k) < seuil){
                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[0][0] << " " << vertices[0][1] << " " << vertices[0][2] << "\n";
                        outputFile << "vertex " << vertices[4][0] << " " << vertices[4][1] << " " << vertices[4][2] << "\n";
                        outputFile << "vertex " << vertices[6][0] << " " << vertices[6][1] << " " << vertices[6][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";

                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[0][0] << " " << vertices[0][1] << " " << vertices[0][2] << "\n";
                        outputFile << "vertex " << vertices[6][0] << " " << vertices[6][1] << " " << vertices[6][2] << "\n";
                        outputFile << "vertex " << vertices[2][0] << " " << vertices[2][1] << " " << vertices[2][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";
                    } 

                    if (i < imIn.dimX - 1 && imIn.getValue(i + 1, j, k) < seuil){
                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[1][0] << " " << vertices[1][1] << " " << vertices[1][2] << "\n";
                        outputFile << "vertex " << vertices[3][0] << " " << vertices[3][1] << " " << vertices[3][2] << "\n";
                        outputFile << "vertex " << vertices[7][0] << " " << vertices[7][1] << " " << vertices[7][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";

                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[1][0] << " " << vertices[1][1] << " " << vertices[1][2] << "\n";
                        outputFile << "vertex " << vertices[7][0] << " " << vertices[7][1] << " " << vertices[7][2] << "\n";
                        outputFile << "vertex " << vertices[5][0] << " " << vertices[5][1] << " " << vertices[5][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";
                    }

                    if (j > 0 && imIn.getValue(i, j - 1, k) < seuil){
                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[0][0] << " " << vertices[0][1] << " " << vertices[0][2] << "\n";
                        outputFile << "vertex " << vertices[1][0] << " " << vertices[1][1] << " " << vertices[1][2] << "\n";
                        outputFile << "vertex " << vertices[5][0] << " " << vertices[5][1] << " " << vertices[5][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";

                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[0][0] << " " << vertices[0][1] << " " << vertices[0][2] << "\n";
                        outputFile << "vertex " << vertices[5][0] << " " << vertices[5][1] << " " << vertices[5][2] << "\n";
                        outputFile << "vertex " << vertices[4][0] << " " << vertices[4][1] << " " << vertices[4][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";
                    }

                    if (j < imIn.dimY - 1 && imIn.getValue(i, j + 1, k) < seuil){
                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[2][0] << " " << vertices[2][1] << " " << vertices[2][2] << "\n";
                        outputFile << "vertex " << vertices[6][0] << " " << vertices[6][1] << " " << vertices[6][2] << "\n";
                        outputFile << "vertex " << vertices[7][0] << " " << vertices[7][1] << " " << vertices[7][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";

                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[2][0] << " " << vertices[2][1] << " " << vertices[2][2] << "\n";
                        outputFile << "vertex " << vertices[7][0] << " " << vertices[7][1] << " " << vertices[7][2] << "\n";
                        outputFile << "vertex " << vertices[3][0] << " " << vertices[3][1] << " " << vertices[3][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";
                    }

                    if (k > 0 && imIn.getValue(i, j, k - 1) < seuil){
                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[0][0] << " " << vertices[0][1] << " " << vertices[0][2] << "\n";
                        outputFile << "vertex " << vertices[2][0] << " " << vertices[2][1] << " " << vertices[2][2] << "\n";
                        outputFile << "vertex " << vertices[3][0] << " " << vertices[3][1] << " " << vertices[3][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";

                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[0][0] << " " << vertices[0][1] << " " << vertices[0][2] << "\n";
                        outputFile << "vertex " << vertices[3][0] << " " << vertices[3][1] << " " << vertices[3][2] << "\n";
                        outputFile << "vertex " << vertices[1][0] << " " << vertices[1][1] << " " << vertices[1][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";
                    } 

                    if (k < imIn.dimZ - 1 && imIn.getValue(i, j, k + 1) < seuil){
                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[4][0] << " " << vertices[4][1] << " " << vertices[4][2] << "\n";
                        outputFile << "vertex " << vertices[5][0] << " " << vertices[5][1] << " " << vertices[5][2] << "\n";
                        outputFile << "vertex " << vertices[7][0] << " " << vertices[7][1] << " " << vertices[7][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";

                        outputFile << "facet normal 0 0 0\n";
                        outputFile << "outer loop\n";
                        outputFile << "vertex " << vertices[4][0] << " " << vertices[4][1] << " " << vertices[4][2] << "\n";
                        outputFile << "vertex " << vertices[7][0] << " " << vertices[7][1] << " " << vertices[7][2] << "\n";
                        outputFile << "vertex " << vertices[6][0] << " " << vertices[6][1] << " " << vertices[6][2] << "\n";
                        outputFile << "endloop\n";
                        outputFile << "endfacet\n";
                    } 
                }
            }
        }
    }
}

void imageHistogram(Image im, char* histoName){
    std::ofstream histoFile(histoName);
    if (!histoFile) {
        std::cerr << "Failed to create histogram file." << std::endl;
        return;
    }

    unsigned int min = im.getMinValue();
    unsigned int max = im.getMaxValue();
    std::vector<unsigned int> histogram(max - min + 1, 0);

    for (int i = 0; i < im.dimX; i++) {
        for (int j = 0; j < im.dimY; j++) {
            for (int k = 0; k < im.dimZ; k++) {
                unsigned int value = im.getValue(i, j, k);
                histogram[value - min]++;
            }
        }
    }

    for (size_t i = 0; i < histogram.size(); i++) {
        histoFile << (min + i) << " " << histogram[i] << "\n";
    }

    histoFile.close();
    std::cout << "Histogram data successfully written to " << histoName << std::endl;
}

int main(int argc , char* argv){

    std::cout << "word is bond" << std::endl;

    //char* filename = "img/cube.128x128x64.1.0x1.0x2.0.img";
    //char* filename = "img/engine.256x256x128.1.0x1.0x1.0.img";
    //char* filename = "img/statueLeg.341x341x93.1.0x1.0x4.0.img";
    char* filename = "img/manixSansIV.512x512x48.0.4570x0.4570x3.0.img";
    char* filenameOutput = "img/cube.stl";
    char* histogramName = "img/histo.dat";
    int dimX = 512;
    int dimY = 512;
    int dimZ = 48;

    float sizeX = 0.4570;
    float sizeY = 0.4570;
    float sizeZ = 3;
    Image im = read_img_file(filename , dimX , dimY , dimZ);
    extract_iso_surface(im , 900 , sizeX, sizeY, sizeZ, filenameOutput);
    imageHistogram(im, histogramName);

    return 0;
}