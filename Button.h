#pragma once
#include<bits/stdc++.h>
#include "graphic.h"
using namespace std;
const int BUTTON_WIDTH = 161;
const int BUTTON_HEIGHT = 61;
enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_DOWN = 1,
    BUTTON_SPRITE_TOTAL = 2
};
class Button
{
public:
    Button();
    void setPos(int x, int y);
    void handleEvent(SDL_Event* e);
    LButtonSprite getButton()
    {
        return mCurrSprite;
    }
private:
    Vector2f pos;
    LButtonSprite mCurrSprite;
};
