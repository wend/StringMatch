#include "RegFormula.h"


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
            Mode *mode = new Mode(fixed_str, 0, 0, MODE_FIXED);
            regFormula->addMode(mode);
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
    for(int i = 0; i< mModes.size(); i++)
    {
        Mode *mode = mModes[i];
        mode->getNextMatch();
        if(mode->hasNext())
        {
            break;
        }
        else
        {
            mode->reset();
            if (i == mModes.size() - 1)
                mHasNext = false;
        }
    }
    mRegStrCount++;

    return mRegStr;
}
