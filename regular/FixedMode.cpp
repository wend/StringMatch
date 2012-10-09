#include "FixedMode.h"


FixedMode::FixedMode(vector<string> v)
    :mCurrentIndex(0)
    ,mHasNext(true)
    ,mEmptyStr("")
{
    mFixedStr = v;
}


FixedMode::~FixedMode(void)
{
}

void FixedMode::reset()
{
    mHasNext = true;
    mCurrentIndex = 0;
}

string& FixedMode::gotoNextMatch()
{
    mCurrentIndex++;
    if (mCurrentIndex >= mFixedStr.size())
    {
        mHasNext = false;
        return mEmptyStr;
    }
    return mFixedStr[mCurrentIndex];
}
