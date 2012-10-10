#include "FixedMode.h"


FixedMode::FixedMode(vector<string> v, int min, int max)
    :mCurrentStringIndex(0)
    ,mHasNext(true)
    ,mRetStr("")
    ,mMin(min)
    ,mMax(max)
    ,mCurrentStringCount(min)
{
    mFixedStr = v;
    for (int i = 0; i < min; i++)
    {
        mRetStr += mFixedStr[mCurrentStringIndex];
    }
}


FixedMode::~FixedMode(void)
{
}

void FixedMode::reset()
{
    mHasNext = true;
    mCurrentStringIndex = 0;
    mCurrentStringCount = mMin;
    for (int i = 0; i < mMin; i++)
    {
        mRetStr += mFixedStr[mCurrentStringIndex];
    }
}

string& FixedMode::getCurrentMatch()
{
    return mRetStr;
}

string& FixedMode::gotoNextMatch()
{
    mCurrentStringCount++;
    if (mCurrentStringCount > mMax)
    {
        mRetStr = "";
        mCurrentStringCount = mMin;
        mCurrentStringIndex++;
        if (mCurrentStringIndex >= mFixedStr.size())
        {
            mHasNext = false;
            return mRetStr;
        }
        else
        {
            for (int i = 0; i < mMin; i++)
            {
                mRetStr += mFixedStr[mCurrentStringIndex];
            }
        }
    }
    else
    {
        mRetStr += mFixedStr[mCurrentStringIndex];
    }
    return mRetStr;
}
