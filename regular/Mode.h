#ifndef MODE_H
#define MODE_H

#include <string>
using namespace std;
enum
{
    MODE_FIXED,
    MODE_VARIABLE
};

class Mode
{
public:
    Mode(string str, int min, int max, int type);
    ~Mode(void);
    void reset();
    string getNextMatch();
    bool hasNext();
    string getCurrentMatch();

public:
    string mStr;
    int mMin;
    int mMax;
    int mType;

    int *mCurrentCharsIndex;
    char *mValues;
    bool mHasNext;
};

#endif //MODE_H

