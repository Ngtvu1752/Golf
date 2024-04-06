#pragma once
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

#include "entity.h"
#include "math.h"
#include "Hole.h"
using namespace std;
class Ball : public Entity
{
public:
    Ball(Vector2f p_pos, SDL_Texture* p_tex, SDL_Texture* p_point, SDL_Texture* powerBE, SDL_Texture* powerFE);
    Vector2f& getVelocity()
    {
        return velocity;
    }
    Vector2f& getInitialMousePos()
    {
        return initialMousePos;
    }
    vector<Entity> getPoint()
    {
        return point;
    }
    vector<Entity> getBar()
    {
        return forceBar;
    }
    bool isWin()
    {
        return win;
    }
    void setWin(bool p_win);
    void setVelocity(float x, float y);
    void setLauchedVelocity(float x, float y);
    void setInitialMousePos(float x, float y);
    void update(double deltaTime, bool mousePressed, bool mouseDown, Hole hole, Mix_Chunk* holeSfx);
private:
    Vector2f velocity;
    Vector2f lauchedVelocity;
    Vector2f target;
    float velocity1D;
    float lauchedVelocity1D;
    Vector2f initialMousePos;
    float friction = 0.001;
    int dirX = 1;
    int dirY = 1;
    bool canMove = 1;
    bool win = false;
    vector<Entity> point; //optimise
    vector<Entity> forceBar;
};
