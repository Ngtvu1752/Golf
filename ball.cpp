#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>

#include "defs.h"
#include "entity.h"
#include "math.h"
#include "Ball.h"

using namespace std;
Ball::Ball(Vector2f p_pos, SDL_Texture* p_tex)
:Entity(p_pos, p_tex)
{

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
void Ball::update(double deltaTime, bool mousePressed, bool mouseDown)
{
    if(mousePressed &&canMove)
    {
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

        dirX = velocity.x/abs(velocity.x);
        dirY = velocity.y/abs(velocity.y);
        if(velocity1D > 1)
        {
            velocity1D = 1;
            lauchedVelocity1D = 1;
        }
    }
    else
    {
        canMove = 0;
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
            setVelocity(-(abs(getVelocity().x)), getVelocity().y);
            dirX = -1;
        }
        else if(getPos().y + getCurrFrame().h > HEIGHT)
        {
            setVelocity(getVelocity().x, -abs(getVelocity().y));
            dirY = -1;
        }
        if(getPos().x < 0)
        {
            setVelocity(abs(getVelocity().x), getVelocity().y);
            dirX = 1;
        }
        if(getPos().y < 0)
        {
            setVelocity(getVelocity().x, abs(getVelocity().y));
            dirY = 1;
        }
    }
}
