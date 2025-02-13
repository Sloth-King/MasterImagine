#include <iostream>
#include "EvalPerf.h"


double f(float a){
    return 1 - a*a*a*a;
}

int main(void){
    EvalPerf PE;
    PE.start();
    f(13);
    PE.stop();
    std::cout << "nb cycles : " << PE.cycles() << std::endl;
    std::cout << "nb sec : " << PE.seconds() << std::endl;
    std::cout << "IPC : " << PE.IPC(5) << std::endl;
    std::cout << "CPI : " << PE.CPI(5) << std::endl;
}