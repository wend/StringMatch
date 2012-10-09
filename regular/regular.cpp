#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;



#include "Mode.h"

int main(int argc, char*argv[])
{
    string reg = argv[1];
cout << "reg:"<<reg<<endl;
cout << "output file:" << argv[2]<<endl;
    vector<Mode*> vec;
    while(true)
    {
        string::size_type pos = reg.find("[");
        if (pos == std::string::npos)
        {
            break;
        }
        if (pos != 0)
        {
            string fixed_str = reg.substr(0, pos);
            Mode *mode = new Mode(fixed_str, 0, 0, MODE_FIXED);
            vec.push_back(mode);
        }
        reg = reg.substr(pos + 1);
        string str;
        char minChar = reg[0];
        char maxChar = reg[2];
        while(minChar <= maxChar)
        {
            str.append(1, minChar);
            minChar++;
        }
        pos = reg.find("{");
        reg = reg.substr(pos + 1);
        int min = reg[0] - '0';
        int max = min;
        if (reg[1] == ',')
        {
            max = reg[2] - '0';
        }
        Mode *mode = new Mode(str, min, max, MODE_VARIABLE);
        vec.push_back(mode);

        pos = reg.find("}");
        reg = reg.substr(pos + 1);
    }

    ofstream of;
    of.open(argv[2], ios::out);
    if (!of.is_open())
    {
        cout << "open file error"<<endl;
    }
    bool hasNext = true;

    while(hasNext)
    {   
        string regular_str;
        for(int i = 0; i< vec.size(); i++)
        {
            Mode *mode = vec[i];
            regular_str += mode->getCurrentMatch();
        }
        of << regular_str <<endl;
        for(int i = 0; i< vec.size(); i++)
        {
            Mode *mode = vec[i];
            mode->getNextMatch();
            if(mode->hasNext())
            {
                break;
            }
            else
            {
                mode->reset();
                if (i == vec.size() - 1)
                    hasNext = false;
            }
        }
    }

    of.close();
    
    return 0;
}
