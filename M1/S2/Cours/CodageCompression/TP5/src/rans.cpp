#include "rans.h"
#include <vector>
#include "mesh.h"
#include <numeric>


std::vector<int> vector_to_int(std::vector<Eigen::Vector3f> v){
    std::vector<int> result;
    result.reserve(v.size() * 3);
    for (const auto& vec : v) {
        result.push_back(static_cast<int>(vec[0]));
        result.push_back(static_cast<int>(vec[1]));
        result.push_back(static_cast<int>(vec[2]));
    }
    return result;
}


//alphabet -> 0 , 2^qp -1
//mesh gives S , A is given above 
void get_values(Mesh &inMesh , int qp ,std::vector<int> &S , std::vector<int> &A, std::vector<int> &F , std::vector<int> &C){

    std::cout << "Get val" << std::endl;
    //S = list of numbers 
    S = vector_to_int(inMesh.getVertices());

    //Possible alphabet
    A.resize(pow(qp,2)-1); //make its size tha max number of coords
    std::iota(std::begin(A) , std::end(A) , 0); //fill it from 0 to the max size;

    F.resize(A.size(), 0);
    //Cycle through A
    for(int i = 0 ; i < A.size() ; i++){
        //cycle through S
        for(int j = 0 ; j < S.size() ; j++){
            if(A[i] == S[j]){
                F[i]++;
            }
        }
    }
    std::cout << "Got F" << std::endl;

    C.resize(A.size(), 0);
    C[0] = 0;
    for (int i = 1; i < F.size(); ++i) {
        C[i] = C[i - 1] + F[i - 1];
    }
    std::cout << "Got C" << std::endl;

}


unsigned long long int codage_rans(std::vector<int> &S , std::vector<int> &A, std::vector<int> &F , std::vector<int> &C){
    unsigned long long int x = 0;
    int M = 1 << 16;

    std::cout << "Geting rans" << std::endl;
    for (int k = S.size() - 1; k >= 0; --k) {
        if (F[S[k]] != 0) {
            x = (x / F[S[k]]) * M + C[S[k]] + x % F[S[k]];
        }
    }
    
    return x;
}

std::vector<int> decodage_rans(unsigned long long int x, std::vector<int> &A, std::vector<int> &F, std::vector<int> &C, std::vector<int> &S_decoded, int original_size) {
    int M = 1 << 16; 
    S_decoded.resize(original_size);

    for (int k = 0; k < original_size; ++k) {
        int st = 0;
        for (int i = 0; i < A.size(); ++i) {
            if (C[i] <= (x % M) && (x % M) < C[i] + F[i]) {
                st = i;
                break;
            }
        }

        S_decoded[k] = A[st]; 
        x = F[st] * (x / M) + (x % M) - C[st];
    }

    std::reverse(S_decoded.begin(), S_decoded.end()); 
    return S_decoded;
}
