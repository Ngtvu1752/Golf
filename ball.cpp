#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>

#include "defs.h"
#include "entity.h"
#include "math.h"
#include "Ball.h"
#include "Hole.h"
#include "graphic.h"

using namespace std;
Ball::Ball(Vector2f p_pos, SDL_Texture* p_tex,SDL_Texture* p_point, SDL_Texture* powerBE, SDL_Texture* powerFE)
:Entity(p_pos, p_tex)
{
    point.push_back(Entity(Vector2f(-50,-50), p_point));
    forceBar.push_back(Entity(Vector2f(-50,-50),powerBE));
    forceBar.push_back(Entity(Vector2f(-50,-50), powerFE));
}
void Ball::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity.y = y;
}
void Ball::setInitialMousePos(float x, float y)
{
    initialMousePos.x = x;
    initialMousePos.y = y;
}
void Ball::setLauchedVelocity(float x, float y)
{
    lauchedVelocity.x = x;
    lauchedVelocity.y = y;
}
void Ball::setWin(bool p_win)
{
    win = p_win;
}

void Ball::update(double deltaTime, bool mousePressed, bool mouseDown, Hole hole,vector<Entity>wall, Mix_Chunk* holeSfx, Mix_Chunk* collision)
{
    target.x = hole.getPos().x ;
    target.y = hole.getPos().y + 3;
    if(win)
    {
        if(getPos().x < target.x)
        {
            setPos(getPos().x += 0.1*deltaTime, getPos().y);
        }
        else if(getPos().x > target.x)
        {
            setPos(getPos().x -= 0.1*deltaTime, getPos().y);
        }

        if(getPos().y < target.y)
        {
            setPos(getPos().x, getPos().y += 0.1*deltaTime);
        }
        else if(getPos().y > target.y)
        {
            setPos(getPos().x, getPos().y -= 0.1*deltaTime);
        }
        setScale(getScale().x - 0.001*deltaTime, getScale().y - 0.001*deltaTime);
        return;
    }
    if(getPos().x +4 > hole.getPos().x && getPos().x < hole.getPos().x + 4 && getPos().y+4 >hole.getPos().y && getPos().y < hole.getPos().y+4 )
    {
        Mix_PlayChannel(-1, holeSfx, 0);
        setWin(true);
        target.x = hole.getPos().x ;
        target.y = hole.getPos().y + 3;
        swings++;
    }
    if(mousePressed &&canMove)
    {
        swings++;
        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        setInitialMousePos(mouseX, mouseY);
    }
    if( mouseDown && canMove )
    {
        int mouseX = 0;
        int mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        setVelocity((mouseX - getInitialMousePos().x)/-150, (mouseY - getInitialMousePos().y)/-150);
        setLauchedVelocity((mouseX - getInitialMousePos().x)/-150, (mouseY - getInitialMousePos().y)/-150);
        velocity1D = SDL_sqrt(getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y);
        lauchedVelocity1D = velocity1D;

        point[0].setPos(getPos().x , getPos().y + 8 - 32 );
        point[0].setAngle(SDL_atan2(velocity.y, velocity.x)*(180/3.1415)+90);

//        forceBar[0].setPos(getPos().x + 40, getPos().y - 30);
//        forceBar[1].setPos(getPos().x + 44, getPos().y + 4 - 32*forceBar[1].getScale().y);
        forceBar[0].setPos(mouseX+10, mouseY+10);
        forceBar[1].setPos(mouseX + 14, mouseY +32 +14 - 32*forceBar[1].getScale().y);
        dirX = velocity.x/abs(velocity.x);
        dirY = velocity.y/abs(velocity.y);
        if(velocity1D > 1)
        {
            velocity1D = 1;
            lauchedVelocity1D = 1;
        }
        forceBar[1].setScale(1, velocity1D);
    }
    else
    {
        canMove = 0;
//        Mix_PlayChannel(-1,hit,0);
        point[0].setPos(-50,-50);
        forceBar[0].setPos(-50,-50);
        forceBar[1].setPos(-50,-50);
        setPos(getPos().x + getVelocity().x * deltaTime, getPos().y + getVelocity().y*deltaTime);
        if(getVelocity().x > 0.001 || getVelocity().x < -0.001 || getVelocity().y > 0.001 || getVelocity().y < -0.001)
        {
            if(velocity1D > 0)
            {
                velocity1D -= friction*deltaTime;
            }
            else
            {
                velocity1D = 0;
            }
            velocity.x = velocity1D/lauchedVelocity1D* (abs(lauchedVelocity.x)*dirX);
            velocity.y = velocity1D/lauchedVelocity1D* (abs(lauchedVelocity.y)*dirY);
        }
        else
        {
            setVelocity(0,0);
            int mouseX = 0, mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            setInitialMousePos(mouseX, mouseY);
            canMove = 1;
        }
        if(getPos().x + getCurrFrame().w > WIDTH)
        {
            Mix_PlayChannel(-1,collision, 0);
            setVelocity(-(abs(getVelocity().x)), getVelocity().y);
            dirX = -1;
        }
        else if(getPos().y + getCurrFrame().h > HEIGHT)
        {
            Mix_PlayChannel(-1,collision, 0);
            setVelocity(getVelocity().x, -abs(getVelocity().y));
            dirY = -1;
        }
        if(getPos().x < 0)
        {
            Mix_PlayChannel(-1,collision, 0);
            setVelocity(abs(getVelocity().x), getVelocity().y);
            dirX = 1;
        }
        if(getPos().y < 0)
        {
            Mix_PlayChannel(-1,collision, 0);
            setVelocity(getVelocity().x, abs(getVelocity().y));
            dirY = 1;
        }

        for(Entity& e : wall)
        {
            float nX =  getPos().x + getVelocity().x*deltaTime;
            float nY = getPos().y;
            if(nX + 16 > e.getPos().x && nX  < e.getPos().x + e.getCurrFrame().w
               && nY + 16 > e.getPos().y && nY  < e.getPos().y + e.getCurrFrame().h-3)
            {
                Mix_PlayChannel(-1,collision, 0);
                setVelocity(getVelocity().x * -1, getVelocity().y);
                dirX *= -1;
            }

             nX =  getPos().x  ;
             nY = getPos().y + getVelocity().y*deltaTime;
            if(nX + 16 > e.getPos().x && nX  < e.getPos().x + e.getCurrFrame().w
               && nY + 16 > e.getPos().y && nY  < e.getPos().y + e.getCurrFrame().h-3)
            {
                Mix_PlayChannel(-1,collision, 0);
                setVelocity(getVelocity().x , getVelocity().y * -1);
                dirY *= -1;
            }

        }

    }
}
