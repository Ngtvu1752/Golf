#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_mixer.h>
#include "graphic.h"
#include "entity.h"
using namespace std;

void logErrorAndExit(const char*msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

Graphic::Graphic(int w, int h, const char* filename)
    :window(NULL),renderer(NULL)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        logErrorAndExit("SDL_Init", SDL_GetError());
    }
    window = SDL_CreateWindow(filename, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_ALLOW_HIGHDPI);

    //ktra xem window có được create thành công không
    if(window == NULL)
    {
        logErrorAndExit("CreateWindow", SDL_GetError());
    }
    if(!IMG_Init(IMG_INIT_JPG|| IMG_INIT_PNG))
    {
        logErrorAndExit("SDL_IMG loi mm roi: ", IMG_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));
    if (TTF_Init() == -1)
    {
        logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                        TTF_GetError());
    }
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    if (renderer == NULL) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

}
SDL_Texture* Graphic::loadingTexture(const char* filename)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        cout << "Failed to load texture. Error: " << SDL_GetError() <<endl;

    return texture;
}
Mix_Chunk* Graphic::loadSound(const char* filename)
{
        Mix_Chunk* gChunk = Mix_LoadWAV(filename);
        if (gChunk == nullptr)
        {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }

}
TTF_Font* Graphic::loadFont(const char* filename, int size)
{
    TTF_Font* gFont = TTF_OpenFont( filename, size );
    if (gFont == nullptr)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                       SDL_LOG_PRIORITY_ERROR,
                       "Load font %s", TTF_GetError());
    }

}
void Graphic::render(SDL_Texture* p_tex, int x, int y, SDL_Rect* src)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(p_tex, NULL, NULL, &dst.w, &dst.h);

    if(src != nullptr)
    {
        dst.w = src->w;
        dst.h = src->h;
    }
    SDL_RenderCopy(renderer, p_tex, src, &dst);
}
void Graphic::renderEntity(Entity& p_entity)
{
    SDL_Rect src;
    src.x = p_entity.getCurrFrame().x;
    src.y = p_entity.getCurrFrame().y;
    src.w = p_entity.getCurrFrame().w;
    src.h = p_entity.getCurrFrame().h;

    SDL_Rect dst;
    dst.x = p_entity.getPos().x + (p_entity.getCurrFrame().w - p_entity.getCurrFrame().w*p_entity.getScale().x)/2;
    dst.y = p_entity.getPos().y + (p_entity.getCurrFrame().h - p_entity.getCurrFrame().h*p_entity.getScale().y)/2;
    dst.w = p_entity.getCurrFrame().w*p_entity.getScale().x;
    dst.h = p_entity.getCurrFrame().h*p_entity.getScale().y;

    SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(),0, SDL_FLIP_NONE);
}

void Graphic::renderTexture( int x, int y, SDL_Texture* texture)
{
    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w;
    src.h;
    SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;
//    QueryTexture lam nhiem vu lay w va h cua texture cho rect

    SDL_RenderCopy(renderer, texture, &src, &dst);
}
void Graphic::renderText(int x, int y, const char* text, TTF_Font* font, SDL_Color textColor )
{
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, text, textColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void Graphic::display()
{
    SDL_RenderPresent(renderer);
}
void Graphic::quitSDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
void Graphic::Clear()
{
    SDL_RenderClear(renderer);
}
