#ifndef CTIMER_H
#define CTIMER_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class cTimer
{
public:
    cTimer();

    void restart();
    float getTimeStamp(); // as seconds

private:
    // time, oldTime and timeDiff are in microseconds
    long long time, oldTime, timeDiff;

    LARGE_INTEGER getFrequency();
    long long cGetTime();
};

#endif // CTIMER_H
