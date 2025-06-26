#pragma once

#include "ImageBase.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

enum IntraType
{
    VERTICAL,
    HORIZONTAL,
    NONE,
};

struct Block
{

    Block() : data(16, std::vector<float>(16, 0)) {}

    Block(int size) : data(size, std::vector<float>(size, 0)) {}

    std::vector<std::vector<float>> data;

    IntraType intraType = NONE;

    int distance_squared(Block &comparedBlock)
    {
        int distance = 0;
        for (int i = 0; i < data.size(); i++)
        {
            for (int j = 0; j < data[i].size(); j++)
            {
                int diff = data[i][j] - comparedBlock.data[i][j];
                distance += diff * diff;
            }
        }
        int blockSize = data.size();
        return distance / blockSize;
    }
};

std::vector<Block> getBlocks(ImageBase &imIn, int blockSize)
{
    std::vector<Block> blocks;
    int height = imIn.getHeight();
    int width = imIn.getWidth();

    for (int i = 0; i < height; i += blockSize)
    {
        for (int j = 0; j < width; j += blockSize)
        {
            Block block(blockSize);

            for (int k = 0; k < blockSize; k++)
            {
                for (int l = 0; l < blockSize; l++)
                {

                    int x = i + k;
                    int y = j + l;

                    if (x < height && y < width)
                    {
                        block.data[k][l] = imIn[x][y];
                    }
                    else
                    {
                        block.data[k][l] = 0; // Remplissage avec 0
                    }
                }
            }

            blocks.push_back(block);
        }
    }

    return blocks;
    
}

std::vector<std::vector<Block>> getBlocksMat(ImageBase &imIn, int blockSize)
{
    std::vector<std::vector<Block>> blocks;
    blocks.resize((imIn.getHeight() + blockSize - 1) / blockSize, std::vector<Block>((imIn.getWidth() + blockSize - 1) / blockSize));
    int height = imIn.getHeight();
    int width = imIn.getWidth();

    for (int i = 0; i < height; i += blockSize)
    {
        for (int j = 0; j < width; j += blockSize)
        {
            Block block(blockSize);

            for (int k = 0; k < blockSize; k++)
            {
                for (int l = 0; l < blockSize; l++)
                {

                    int x = i + k;
                    int y = j + l;

                    if (x < height && y < width)
                    {
                        block.data[k][l] = imIn[x][y];
                    }
                    else
                    {
                        block.data[k][l] = 0; // Remplissage avec 0
                    }
                }
            }

            blocks[i / blockSize][j / blockSize] = block;
        }
    }

    return blocks;
}

void reconstructImageFromBlocks(ImageBase &imOut, std::vector<std::vector<Block>> imageBlocks)
{
    int blockSize = imageBlocks[0][0].data.size();
    int height = imOut.getHeight();
    int width = imOut.getWidth();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blockRow = i / blockSize;
            int blockCol = j / blockSize;
            int localRow = i % blockSize;
            int localCol = j % blockSize;

            imOut[i][j] = imageBlocks[blockRow][blockCol].data[localRow][localCol];
        }
    }
}

// Intra vertical
std::vector<std::vector<Block>> intra_16x16_vertical(ImageBase &imIn, int blockSize)
{

    std::vector<std::vector<Block>> imageBlocks = getBlocksMat(imIn, blockSize);
    int columns_n = imageBlocks.size();
    int rows_n = imageBlocks[0].size();

    std::vector<std::vector<Block>> outBlocks = imageBlocks;

    Block previousBlock;
    for (int i = 1; i < columns_n; i++)
    {
        for (int j = 0; j < rows_n; j++)
        {

            previousBlock = imageBlocks[i - 1][j];

            for (int k = 0; k < blockSize; k++)
            {
                for (int l = 0; l < blockSize; l++)
                {
                    outBlocks[i][j].data[k][l] = previousBlock.data[k][blockSize - 1];
                    outBlocks[i][j].intraType = VERTICAL;
                }
            }
        }
    }
    return outBlocks;
}

// Intra vertical
std::vector<std::vector<Block>> intra_16x16_horizontal(ImageBase &imIn, int blockSize)
{

    std::vector<std::vector<Block>> imageBlocks = getBlocksMat(imIn, blockSize);
    int columns_n = imageBlocks.size();
    int rows_n = imageBlocks[0].size();

    std::vector<std::vector<Block>> outBlocks = imageBlocks;

    Block previousBlock;
    for (int i = 0; i < columns_n; i++)
    {
        for (int j = 1; j < rows_n; j++)
        {

            previousBlock = imageBlocks[i][j - 1];

            for (int k = 0; k < blockSize; k++)
            {
                for (int l = 0; l < blockSize; l++)
                {
                    outBlocks[i][j].data[k][l] = previousBlock.data[blockSize - 1][l];
                    outBlocks[i][j].intraType = HORIZONTAL;
                }
            }
        }
    }
    return outBlocks;
}

void blockDistMap(std::vector<std::vector<Block>> blocks_base,
                  std::vector<std::vector<Block>> blocks_type1,
                  std::vector<std::vector<Block>> blocks_type2,
                  ImageBase &imIn,
                  ImageBase &imOut,
                  int seuil = 100000)
{
    int height = imIn.getHeight();
    int width = imIn.getWidth();
    int blockSize = blocks_base[0][0].data.size();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blockRow = i / blockSize;
            int blockCol = j / blockSize;

            int dist1 = blocks_base[blockRow][blockCol].distance_squared(blocks_type1[blockRow][blockCol]);
            int dist2 = blocks_base[blockRow][blockCol].distance_squared(blocks_type2[blockRow][blockCol]);

            // if(dist1 > seuil || dist2 > seuil){
                // imOut[i][j] = 0;
            // }
            // else 
            if (dist1 < dist2)
            {
                imOut[i][j] = 128;
            }
            else if(dist1 > dist2)
            {
                imOut[i][j] = 255;
            }
        }
    }
}

std::vector<std::vector<Block>> splitIntoSubBlocks(std::vector<std::vector<Block>> blocks, int subBlockSize) {
    int numRows = blocks.size() * blocks[0][0].data.size() / subBlockSize;
    int numCols = blocks[0].size() * blocks[0][0].data[0].size() / subBlockSize;

    std::vector<std::vector<Block>> subBlocks(numRows, std::vector<Block>(numCols, Block(subBlockSize)));

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            for (int k = 0; k < subBlockSize; k++) {
                for (int l = 0; l < subBlockSize; l++) {
                    int parentBlockRow = (i * subBlockSize + k) / blocks[0][0].data.size();
                    int parentBlockCol = (j * subBlockSize + l) / blocks[0][0].data[0].size();
                    int localRow = (i * subBlockSize + k) % blocks[0][0].data.size();
                    int localCol = (j * subBlockSize + l) % blocks[0][0].data[0].size();

                    subBlocks[i][j].data[k][l] = blocks[parentBlockRow][parentBlockCol].data[localRow][localCol];
                }
            }
        }
    }

    return subBlocks;
}

