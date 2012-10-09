#ifndef REG_FORMULA_H
#define REG_FORMULA_H
#include "Mode.h"
#include <vector>
using namespace std;

class RegFormula
{
public:
    RegFormula(void);
    ~RegFormula(void);
    void addMode(Mode*);
    static RegFormula* parse(string reg);
    string getNextMatch();
    inline bool hasNext(){return mHasNext;}
    inline long long getTotalCount(){return mRegStrCount;}
private:
    string mRegStr;
    long long mRegStrCount;
    bool mHasNext;
    vector<Mode*> mModes;
};
#endif