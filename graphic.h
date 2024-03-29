#pragma once
#ifndef _GRAPHIC__H
#define _GRAPHIC__H
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "entity.h"
//const int WIDTH = 640, HEIGHT  = 480;
//inline const char* Window_Title = "Hello SDL2 World";
class Graphic
{
public:
    Graphic(int w, int h, const char* filename);
    SDL_Texture* loadingTexture(const char* filename);
    void quitSDL();
    void clear();
    void render(SDL_Texture* p_tex);
    void renderEntity(Entity& p_entity);
    void renderTexture(int x, int y, SDL_Texture* p_tex);
    void display();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // _GRAPHIC__H

