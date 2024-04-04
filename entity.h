#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include "math.h"


class Entity
{
public:
    Entity(Vector2f p_pos, SDL_Texture* p_tex);
    Vector2f& getPos()
    {
        return pos;
    }
    float getAngle()
    {
        return angle;
    }
    Vector2f getScale()
    {
        return scale;
    }
    SDL_Texture* getTex();
    SDL_Rect getCurrFrame();
    void setPos(float x, float y);
    void setAngle(float angle);
    void setScale(float w, float h);

private:
    Vector2f pos;
    float angle = 0;
    SDL_Texture* tex;
    SDL_Rect currFrame;
    Vector2f scale = Vector2f(1,1);
};
