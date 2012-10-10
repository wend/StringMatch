#ifndef FIXED_MODE_H
#define FIXED_MODE_H

#include "Mode.h"
#include <string>
#include <vector>
using namespace std;

class FixedMode:public Mode
{
public:
    FixedMode(vector<string> v, int min, int max);
    ~FixedMode(void);
    virtual void reset();
    virtual string& gotoNextMatch();
    virtual string& getCurrentMatch();
    bool hasNext(){return mHasNext;}
private:
    vector<string> mFixedStr;
    string mRetStr;
    bool mHasNext;
    int mCurrentStringIndex;
    int mCurrentStringCount;
    int mMin;
    int mMax;
};
#endif


