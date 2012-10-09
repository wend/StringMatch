#include <string.h>
#include "Mode.h"


Mode::Mode(string str, int min, int max, int type)
    :mCurrentCharsIndex(NULL)
    ,mMax(max)
    ,mMin(min)
    ,mStr(str)
    ,mType(type)
    ,mHasNext(true)
{
    mValues = new char[max+1];
    memset(mValues, 0, max+1);
    mCurrentCharsIndex = new int[max];
    if (MODE_FIXED == mType)
    {
        memcpy(mValues, mStr.c_str(), mStr.size());
    }
    else
    {
       for (int i = 0; i < mMax; i ++)
        {
            if (i < mMin)
            {
                mCurrentCharsIndex[i] = mStr.size() - 1;
                mValues[i] = mStr[mCurrentCharsIndex[i]];
            }
            else
            {
                mCurrentCharsIndex[i] = mStr.size();
            }
        }
    }   
    mRetStr = mValues;
}


Mode::~Mode(void)
{
    delete mValues;
    delete mCurrentCharsIndex;
}


void Mode::reset()
{
    mHasNext = true;
    memset(mValues, 0, mMax+1);
    if (MODE_FIXED == mType)
    {
        memcpy(mValues, mStr.c_str(), mStr.size());
    }
    else
    {
       for (int i = 0; i < mMax; i ++)
        {
            if (i < mMin)
            {
                mCurrentCharsIndex[i] = mStr.size() - 1;
                mValues[i] = mStr[mCurrentCharsIndex[i]];
            }
            else
            {
                mCurrentCharsIndex[i] = mStr.size();
            }
        }
    }    
    mRetStr = mValues;
}


bool Mode::hasNext()
{
    return mHasNext;
}

string& Mode::getCurrentMatch()
{
    return mRetStr;
}

string& Mode::getNextMatch()
{
    mRetStr = mValues;
    if (MODE_FIXED == mType)
    {
        mHasNext = false;
        return mRetStr;
    }

    for (int i = 0; i < mMax; i++)
    {
        mCurrentCharsIndex[i]--;
        if (mCurrentCharsIndex[i] < 0)
        {
            if (i == mMax -1)
            {
                mHasNext = false;
                break;
            }
            else
            {
                mCurrentCharsIndex[i] = mStr.size() - 1;
                mValues[i] = mStr[mCurrentCharsIndex[i]];
            }
        }
        else
        {
            mValues[i] = mStr[mCurrentCharsIndex[i]];
            break;
        }
    }
    
    return mRetStr;
}
