#pragma once
#include<bits/stdc++.h>
#include "graphic.h"
#include "Button.h"
using namespace std;

Button::Button()
{
    pos.x = WIDTH/2 - 32*3;
    pos.y = HEIGHT/2;
    mCurrSprite = BUTTON_SPRITE_MOUSE_OUT;
}
void Button::setPos(int x, int y)
{
    pos.x = x;
    pos.y = y;
}
void Button::handleEvent(SDL_Event* e)
{

    if(e->type == SDL_MOUSEMOTION)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);
        bool check = true;
        if( x < pos.x ) check = false;
        else if(y < pos.y) check = false;
        else if(x > pos.x + BUTTON_WIDTH) check = false;
        else if(y > pos.y + BUTTON_HEIGHT) check = false;
        if(check == 0)
        {
            mCurrSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        else
        {
            switch(e->type)
            {
            case SDL_MOUSEMOTION:
                mCurrSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
            }
        }
    }
}
