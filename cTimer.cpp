#include "stdafx.h"
#include "cTimer.h"

cTimer::cTimer()
{
    timeDiff = 0;
    restart();
}


void cTimer::restart()
{
    time = oldTime = cGetTime();
}


float cTimer::getTimeStamp() // as seconds
{
    time = cGetTime();
    timeDiff = time - oldTime;
    oldTime = time;
    return timeDiff / 1000000.f;
}


LARGE_INTEGER cTimer::getFrequency()
{
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    return frequency;
}


long long cTimer::cGetTime()
{
    static LARGE_INTEGER frequency = getFrequency();
    static LARGE_INTEGER time;
    QueryPerformanceCounter(&time);

    return 1000000 * time.QuadPart / frequency.QuadPart; // in microseconds
}
