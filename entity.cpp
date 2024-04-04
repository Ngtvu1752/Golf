#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>

#include "entity.h"
using namespace std;

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
:pos(p_pos), tex(p_tex)
{
    currFrame.x = 0;
    currFrame.y = 0;
    SDL_QueryTexture(p_tex, NULL, NULL, &currFrame.w, &currFrame.h);
}

SDL_Texture* Entity::getTex()
{
    return tex;
}


SDL_Rect Entity::getCurrFrame()
{
    return currFrame;
}

void Entity::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
}
void Entity::setAngle(float p_angle)
{
    angle = p_angle;
}
void Entity::setScale(float w, float h)
{
    scale.x = w;
    scale.y = h;
}
