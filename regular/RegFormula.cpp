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

void RegFormula::parseFixedStr(string fixed_str, RegFormula* regFormula)
{
    while(fixed_str.length() > 0 )
    {
        string::size_type pos1 = fixed_str.find("<");
        string::size_type pos2 = fixed_str.find(">");
        if (pos1 != string::npos)
        {
            if (pos1 != 0)
            {
                string str = fixed_str.substr(0, pos1);
                string::size_type pos3 = str.find("{");
                if (pos3 != string::npos)
                {
                    string fixed_str1 = str.substr(0, pos3);
                    str = str.substr(pos3+1);
                    int min = str[0] - '0';
                    int max = min;
                    if (str[1] == ',')
                    {
                        max = str[2] - '0';
                    }
                    vector<string> v;
                    v.push_back(fixed_str1);
                    Mode *mode = new FixedMode(v, min, max);
                    regFormula->addMode(mode);
                }
                else
                {
                    vector<string> v;
                    v.push_back(str);
                    Mode *mode = new FixedMode(v, 1, 1);
                    regFormula->addMode(mode);
                }

            }
            string file = fixed_str.substr(pos1+1, pos2 - pos1 -1);
            vector<string> v = readFixedStr(file);
            fixed_str = fixed_str.substr(pos2 + 1);
            if(v.size())
            {
                if (fixed_str.find("{") != string::npos)
                {
                    fixed_str = fixed_str.substr(1);
                    int min = fixed_str[0] - '0';
                    int max = min;
                    if (fixed_str[1] == ',')
                    {
                        max = fixed_str[2] - '0';
                    }
                    //fixed_str = fixed_str.substr(fixed_str.find("}") + 1);
                    Mode *mode = new FixedMode(v, min, max);
                    regFormula->addMode(mode);
                }
                else
                {
                    Mode *mode = new FixedMode(v, 1, 1);
                    regFormula->addMode(mode);
                }
            }
        }
        else
        {
            string::size_type pos3 = fixed_str.find("{");
            if (pos3 != string::npos)
            {
                string fixed_str1 = fixed_str.substr(0, pos3);
                fixed_str = fixed_str.substr(pos3+1);
                int min = fixed_str[0] - '0';
                int max = min;
                if (fixed_str[1] == ',')
                {
                    max = fixed_str[2] - '0';
                }
                vector<string> v;
                v.push_back(fixed_str1);
                fixed_str = fixed_str.substr(fixed_str.find("}") + 1);
                Mode *mode = new FixedMode(v, min, max);
                regFormula->addMode(mode);
            }
            else
            {
                vector<string> v;
                v.push_back(fixed_str);
                Mode *mode = new FixedMode(v, 1, 1);
                regFormula->addMode(mode);
            }
        }
    }
}

RegFormula* RegFormula::parse(string reg)
{
    RegFormula* regFormula = new RegFormula();
    while(true)
    {
        string::size_type pos = reg.find("[");
        if (pos == std::string::npos)
        {
            parseFixedStr(reg, regFormula);
            break;
        }
        else if (pos != 0)
        {
            parseFixedStr(reg.substr(0, pos), regFormula);
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
