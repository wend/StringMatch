#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


#include "RegFormula.h"



int main(int argc, char*argv[])
{
    cout << "reg:"<<argv[1]<<endl;
    cout << "output file:" << argv[2]<<endl;


    ofstream of;
    of.open(argv[2], ios::out);
    if (!of.is_open())
    {
        cout << "open file error"<<endl;
    }
    
    RegFormula* regFormula = RegFormula::parse(argv[1]);

    while(regFormula->hasNext())
    {   
        of<<regFormula->getNextMatch()<<endl;
    }
    of << regFormula->getTotalCount() <<endl;
    of.close();
    
    return 0;
}
