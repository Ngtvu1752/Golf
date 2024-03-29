#pragma once
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>

#include "entity.h"
#include "math.h"

class Ball : public Entity
{
public:
    Ball(Vector2f p_pos, SDL_Texture* p_tex);
    Vector2f& getVelocity()
    {
        return velocity;
    }
    Vector2f& getInitialMousePos()
    {
        return initialMousePos;
    }
    void setVelocity(float x, float y);
    void setLauchedVelocity(float x, float y);
    void setInitialMousePos(float x, float y);
    void update(double deltaTime, bool mousePressed, bool mouseDown);
private:
    Vector2f velocity;
    Vector2f lauchedVelocity;
    float velocity1D;
    float lauchedVelocity1D;
    Vector2f initialMousePos;
    float friction = 0.001;
    int dirX = 1;
    int dirY = 1;
    bool canMove = 1;
};
