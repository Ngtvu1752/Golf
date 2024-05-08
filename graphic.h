#pragma once
#ifndef _GRAPHIC__H
#define _GRAPHIC__H
#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "defs.h"
#include "entity.h"
//const int WIDTH = 640, HEIGHT  = 480;
//inline const char* Window_Title = "Hello SDL2 World";
inline int state = 0;
inline int cntHole = 1;
inline int sprite = 0;
class Graphic
{
public:
    Graphic(int w, int h, const char* filename);
    SDL_Texture* loadingTexture(const char* filename);
    TTF_Font* loadFont(const char* filename, int size);
    Mix_Chunk* loadSound(const char* filename);
    void quitSDL();
    void Clear();
    void render(SDL_Texture* p_tex, int x, int y, SDL_Rect* clip);
    void renderEntity(Entity& p_entity);
    void renderTexture(int x, int y, SDL_Texture* p_tex);
    void renderText(int x, int y, const char* text, TTF_Font* font, SDL_Color textColor );
    void display();
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif // _GRAPHIC__H

