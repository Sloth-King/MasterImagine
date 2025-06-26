#pragma once
#include "mesh.h"
#include <vector>
#include "Eigen/Dense"


std::vector<int> vector_to_int(std::vector<Eigen::Vector3f> v);
void get_values(Mesh &inMesh , int qp ,std::vector<int> &S , std::vector<int> &A, std::vector<int> &F , std::vector<int> &C);
unsigned long long int codage_rans(std::vector<int> &S , std::vector<int> &A, std::vector<int> &F , std::vector<int> &C);
std::vector<int> decodage_rans(unsigned long long int x, std::vector<int> &A, std::vector<int> &F, std::vector<int> &C, std::vector<int> &S , int original_size);