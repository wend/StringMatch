#include <string.h>
#include "Mode.h"


Mode::Mode(string str, int min, int max, int type)
    :mCurrentCharsIndex(NULL)
    ,mMax(max)
    ,mMin(min)
    ,mStr(str)
    ,mType(type)
    ,mHasNext(true)
    ,mValues(NULL)
{
    if (MODE_FIXED == mType)
    {
        mRetStr = mStr;
    }
    else
    {
       mValues = new char[max+1];
       memset(mValues, 0, max+1);
       mCurrentCharsIndex = new int[max];
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
        mRetStr = mValues;
    }   
}


Mode::~Mode(void)
{
    if (mValues)
        delete mValues;
    if (mCurrentCharsIndex)
        delete mCurrentCharsIndex;
}


void Mode::reset()
{
    mHasNext = true;
    if (MODE_FIXED != mType)
    {
        memset(mValues, 0, mMax+1);
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
        mRetStr = mValues;
    }    
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
    mRetStr = mValues;
    return mRetStr;
}
