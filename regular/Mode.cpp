#include <string.h>
#include "Mode.h"


Mode::Mode(string str, int min, int max, int type)
    :mCurrentCharsIndex(NULL)
    ,mMax(max)
    ,mMin(min)
    ,mStr(str)
    ,mType(type)
{
    mCurrentCharsIndex = new int[max];
    for (int i = 0; i < max; i ++)
    {
        mCurrentCharsIndex[i] = mStr.size();
        if (i < min)
            mCurrentCharsIndex[i]--;
    }
    mValues = new char[max+1];
    memset(mValues, 0, max+1);
    mHasNext = true;
}


Mode::~Mode(void)
{
    delete mValues;
    delete mCurrentCharsIndex;
}


void Mode::reset()
{
    for (int i = 0; i < mMax; i ++)
    {
        mCurrentCharsIndex[i] = mStr.size();
        if (i < mMin)
            mCurrentCharsIndex[i]--;
    }
    mHasNext = true;
}


bool Mode::hasNext()
{
    return mHasNext;
}

string Mode::getCurrentMatch()
{
    if (MODE_FIXED == mType)
    {
        return mStr;
    }
    //string str;
    for (int i = 0; i < mMax; i ++)
    {
        mValues[i] = mStr.c_str()[mCurrentCharsIndex[i]];
        //if (mStr.c_str()[mCurrentCharsIndex[i]] != '\0')
          //  str.append(1, mStr.c_str()[mCurrentCharsIndex[i]]);
    }
    return mValues;
}

string Mode::getNextMatch()
{
    if (MODE_FIXED == mType)
    {
        mHasNext = false;
        return mStr;
    }
    //string str;
    for (int i = 0; i < mMax; i ++)
    {
        mValues[i] = mStr.c_str()[mCurrentCharsIndex[i]];
        //if (mStr.c_str()[mCurrentCharsIndex[i]] != '\0')
          //  str.append(1, mStr.c_str()[mCurrentCharsIndex[i]]);
    }
    for (int i = 0; i < mMax; i++)
    {
        mCurrentCharsIndex[i]--;
        if (mCurrentCharsIndex[i] < 0)
        {
            if (i == mMax -1)
            {
                mHasNext = false;
                return mValues;
            }
            else
            {
                mCurrentCharsIndex[i] = mStr.size() - 1;
            }
        }
        else
        {
            break;
        }
    }
    mHasNext = true;
    return mValues;
}
