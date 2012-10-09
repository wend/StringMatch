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
    Mode(void);
    virtual ~Mode(void) = 0;
    virtual void reset() = 0;
    virtual string& gotoNextMatch() = 0;
    virtual bool hasNext() = 0;
    virtual string& getCurrentMatch() = 0;
};

#endif //MODE_H

