#ifndef VARIABLE_MODE_H
#define VARIABLE_MODE_H

#include "Mode.h"
#include <string>
using namespace std;

class VariableMode:public Mode
{
public:
    VariableMode(string str, int min, int max, int type);
    virtual ~VariableMode(void);
    void reset();
    string& gotoNextMatch();
    bool hasNext(){return mHasNext;}
    string& getCurrentMatch(){return mRetStr;}

private:
    char* mStr;
    int len;
    int mMin;
    int mMax;
    int mType;
    int *mCurrentCharsIndex;
    char *mValues;
    string mRetStr;
    bool mHasNext;
};
#endif

