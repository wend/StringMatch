#include "VariableMode.h"
#include <string.h>
#include <algorithm>
VariableMode::VariableMode(string str, int min, int max, int type)
    :mCurrentCharsIndex(NULL)
    ,mMax(max)
    ,mMin(min)
    ,mType(type)
    ,mHasNext(true)
    ,mValues(NULL)
{
    len = str.size() + 1;
    mStr = new char[len];
    memset(mStr, 0, len);
    memcpy(mStr+1, str.c_str(), str.length());

    mValues = new char[mMax+1];
    memset(mValues, 0, mMax+1);
    mCurrentCharsIndex = new int[mMax];
    for (int i = 0; i < mMax; i ++)
    {
        if (i < mMin)
        {
            mCurrentCharsIndex[i] = 1;
            mValues[i] = mStr[mCurrentCharsIndex[i]];
        }
        else
        {
            mCurrentCharsIndex[i] = 0;
        }
    }
    mRetStr = mValues;  
}


VariableMode::~VariableMode(void)
{
    if (mStr)
        delete mStr;
    if (mValues)
        delete mValues;
    if (mCurrentCharsIndex)
        delete mCurrentCharsIndex;
}

void VariableMode::reset()
{
    mHasNext = true;
    memset(mValues, 0, mMax+1);
    for (int i = 0; i < mMax; i ++)
    {
        if (i < mMin)
        {
            mCurrentCharsIndex[i] = 1;
            mValues[i] = mStr[mCurrentCharsIndex[i]];
        }
        else
        {
            mCurrentCharsIndex[i] = 0;
        }
    }
    mRetStr = mValues;  
}

string& VariableMode::gotoNextMatch()
{
    for (int i = 0; i < mMax; i++)
    {
        mCurrentCharsIndex[i]++;
        if (mCurrentCharsIndex[i] >= len)
        {
            if (i == mMax -1)
            {
                mHasNext = false;
                break;
            }
            else
            {
                mCurrentCharsIndex[i] = 1;
                mValues[i] = mStr[mCurrentCharsIndex[i]];
            }
        }
        else
        {
            mValues[i] = mStr[mCurrentCharsIndex[i]];
            break;
        }
    }
    if (mMin == mMax && mMin ==0)
    {
        mHasNext = false;
    }
    mRetStr = mValues;
    reverse(mRetStr.begin(), mRetStr.end());
    return mRetStr;
}
