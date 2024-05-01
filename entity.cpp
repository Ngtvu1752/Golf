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
//Entity::~Entity()
//{
//    free();
//}
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
void Entity::setCurframe(int x, int y, int w, int h)
{
    currFrame.x = x;
    currFrame.y = y;
    currFrame.w = w;
    currFrame.h = h;
}
void Entity::setCurframe(SDL_Rect src)
{
    currFrame = src;
}
void Entity::free()
{
    if(tex != NULL)
    {
        SDL_DestroyTexture(tex);
        tex = NULL;
    }
}

bool Entity::chkIn(int x, int y)
{
    if(x < pos.x) return false;
    else if(y < pos.y) return false;
    else if(x > currFrame.w + pos.x) return false;
    else if(y > currFrame.h + pos.y) return false;

    return true;
}
