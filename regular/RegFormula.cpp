#include <fstream>
#include <iostream>
#include "VariableMode.h"
#include "FixedMode.h"
#include "RegFormula.h"
#include <string.h>



RegFormula::RegFormula(void)
    :mHasNext(true)
    ,mRegStrCount(0)
{
}


RegFormula::~RegFormula(void)
{
    vector<Mode*>::iterator it = mModes.begin();
    for(; it != mModes.end(); it++)
    {
        delete (*it);
    }
    mModes.clear();
}

void RegFormula::addMode(Mode*mode)
{
    mModes.push_back(mode);
}

vector<string> RegFormula::readFixedStr(string inputFile)
{
    vector<string> v;

    ifstream file;
    file.open(inputFile.c_str(), std::ios::in);
    if (!file.is_open())
    {
        cout << "open file error:" << inputFile<<endl;
        return v;
    }

    char *tmp = new char[255];
    while(!file.eof())
    {
        file.getline(tmp, 254);
        if (strlen(tmp) == 0)
        {
            continue;
        }
        v.push_back(tmp);
    }
    delete tmp;

    return v;
}

RegFormula* RegFormula::parse(string reg)
{
    RegFormula* regFormula = new RegFormula();
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
            if (fixed_str.find(".txt") != string::npos)
            {
                vector<string> v = readFixedStr(fixed_str);
                if(v.size())
                {
                    Mode *mode = new FixedMode(v);
                    regFormula->addMode(mode);
                }
            }
            else
            {
                vector<string> v;
                v.push_back(fixed_str);
                Mode *mode = new FixedMode(v);
                regFormula->addMode(mode);
            }
        }
        reg = reg.substr(pos + 1);
        pos = reg.find("]");
        string subStr = reg.substr(0,pos);
        string str;
        char minChar = reg[0];
        for (int i = 0; i<subStr.length(); i++)
        {
            if(subStr[i] == '-')
            {
                while(minChar < subStr[i+1])
                {
                    minChar++;
                    str.append(1, minChar);
                }
                i += 1;
            }
            else
            {
                minChar = subStr[i];
                str.append(1, minChar);
            }
        }
        //char minChar = reg[0];
        //char maxChar = reg[2];
        //while(minChar <= maxChar)
        //{
        //    str.append(1, minChar);
        //    minChar++;
        //}


        pos = reg.find("{");
        reg = reg.substr(pos + 1);
        int min = reg[0] - '0';
        int max = min;
        if (reg[1] == ',')
        {
            max = reg[2] - '0';
        }
        Mode *mode = new VariableMode(str, min, max, MODE_VARIABLE);
        regFormula->addMode(mode);

        pos = reg.find("}");
        reg = reg.substr(pos + 1);
    }
    return regFormula;
}

string RegFormula::getNextMatch()
{   
    mRegStr = "";
    for(int i = 0; i< mModes.size(); i++)
    {
        Mode *mode = mModes[i];
        mRegStr += mode->getCurrentMatch();
    }
    for(int i = mModes.size()-1; i>=0; i--)
    {
        Mode *mode = mModes[i];
        mode->gotoNextMatch();
        if(mode->hasNext())
        {
            break;
        }
        else
        {
            mode->reset();
            if (i == 0)
                mHasNext = false;
        }
    }
    mRegStrCount++;

    return mRegStr;
}
