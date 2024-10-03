#include <iostream>
#include "EvalPerf.h"

int p(int alpha , int* coef , int n){

    int res = coef[0];
    int a = alpha;

    for(int i = 1 ; i < n ; i++)
    {
        res += coef[i]*a;
        a *= alpha; 
    }

    return res;
}

int p_horner(int alpha , int* coef , int n){
    int res = 0;
    for(int i = n-1 ; i > -1 ; i--){
        res = (res*alpha) + coef[i];
    }
    return res;
}

int main(void){
    EvalPerf PE;
    int cLen = 200000000;
    int * tabC = (int*) malloc( cLen * sizeof(int) );
    for(int i = 0 ; i < cLen ; i++){
        tabC[i] = std::rand() % 300;
    }


    //p
    int re;
    PE.start();
    re =p(3,tabC,cLen);
    PE.stop();
    std::cout << "Res p : " << re << std::endl;
    std::cout << "nb cycles p : " << PE.cycles() << std::endl;
    std::cout << "nb sec p : " << PE.seconds() << std::endl;
    std::cout << "IPC p : " << PE.IPC(cLen) << std::endl;
    std::cout << "CPI p : " << PE.CPI(cLen) << std::endl;
    
    int r;
    //horner   
    PE.start();
    r = p_horner(3,tabC,cLen);
    PE.stop();
    std::cout << "Res horner : " << r << std::endl;
    std::cout << "nb cycles horner : " << PE.cycles() << std::endl;
    std::cout << "nb sec horner : " << PE.seconds() << std::endl;
    std::cout << "IPC horner : " << PE.IPC(cLen) << std::endl;
    std::cout << "CPI horner : " << PE.CPI(cLen) << std::endl;

}

