#pragma once
#include<bits/stdc++.h>
#include<SDL.h>

using namespace std;

class Timer
{
public:
    Timer()
    {
    started = 0;
    paused = 0;
    mStart = 0;
    mPaused = 0;
    }
    void start();
    void stop();
    void pause();
    void unpause();
    Uint32 getTicks();
    bool isStart()
    {
        return mStart;
    }
    bool isPause()
    {
        return mPaused;
    }

private:
    Uint32 started;
    Uint32 paused;
    bool mStart;
    bool mPaused;
};
