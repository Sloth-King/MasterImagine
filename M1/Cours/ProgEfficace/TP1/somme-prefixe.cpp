#include <iostream>
#include "EvalPerf.h"


void sommePrefixe(int * tab , int size){
    for(int i = 1 ; i < size ; i++){
        tab[i] = tab[i] + tab[i-1];
        //std::cout<<"Tab["<<i<<"]"<<tab[i]<<std::endl;
    }
}

int main(void){
    EvalPerf PE;
    int lenTab = 2000000;
    int * tab = (int*) malloc(lenTab * sizeof(int));
    for(int i = 0 ; i < lenTab ; i++){
        tab[i] = std::rand() % 500; 
    }


    PE.start();
    sommePrefixe(tab,lenTab);
    PE.stop();
    std::cout << "nb cycles : " << PE.cycles() << std::endl;
    std::cout << "nb sec : " << PE.seconds() << std::endl;
    std::cout << "IPC : " << PE.IPC(lenTab) << std::endl;
    std::cout << "CPI : " << PE.CPI(lenTab) << std::endl;

}