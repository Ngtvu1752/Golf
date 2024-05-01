#include<bits/stdc++.h>
#include<SDL.h>
#include "Timer.h"
using namespace std;


void Timer::start()
{
    mStart = 1;
    mPaused = 0;
    started = SDL_GetTicks();
    paused = 0;
}
void Timer::stop()
{
    mStart = 0;
    mPaused = 0;
    started = 0;
    paused = 0;
}
void Timer::pause()
{
    if(mStart && !mPaused)
    {
        mPaused = 1;
        paused = SDL_GetTicks() - started;
        started = 0;
    }
}
void Timer::unpause()
{
    if(mStart && mPaused)
    {
        mPaused = 0;
        started = SDL_GetTicks() - paused;
        paused = 0;
    }
}
Uint32 Timer::getTicks()
{
    Uint32 time = 0;
    if(mStart)
    {
        if(mPaused)
        {
            time = paused;
        }
        else
        {
            time = SDL_GetTicks() - started;
        }
    }
    return time;
}
