#include <iostream>
#include "EvalPerf.h"
#include <vector>
using namespace std;

#define OP *
#define START 1

template<typename T>
void reduce(const vector<T> &V , T &res){
    res = START ; 
    for(size_t i = 0 ; i < V.size() ; i++){
        res = res OP V[i];
    }
}

template<typename T>
void reduce_roll4(const vector<T> &V , T &res){
    res = START;
    T res1 , res2 , res3 , res4;
    size_t i = 0;
    for(; i + 3 < V.size() ; i+=4){
        res1 = res OP V[i];
        res2 = res OP V[i+2];
        res3 = res OP V[i+3];
        res4 = res OP V[i+4];
        
    }
    for(; i < V.size() ; i++){
        res = res OP V[i];
    }
    res = res1 OP res2 OP res3 OP res4;
}

int main(void){
    EvalPerf PE;
    int lenTab = 20000000;
    int resultat;
    vector<int> vec(lenTab);
    for(size_t i = 0 ; i < vec.size() ; i++){
        vec[i] = std::rand()%500;
    }
    PE.start();
    reduce(vec,resultat);
    PE.stop();
    std::cout << "nb cycles : " << PE.cycles() << std::endl;
    std::cout << "nb sec : " << PE.seconds() << std::endl;
    std::cout << "IPC : " << PE.IPC(lenTab) << std::endl;
    std::cout << "CPI : " << PE.CPI(lenTab) << std::endl;
    PE.start();
    reduce_roll4(vec,resultat);
    PE.stop();
    std::cout << "nb cycles : " << PE.cycles() << std::endl;
    std::cout << "nb sec : " << PE.seconds() << std::endl;
    std::cout << "IPC : " << PE.IPC(lenTab) << std::endl;
    std::cout << "CPI : " << PE.CPI(lenTab) << std::endl;

}