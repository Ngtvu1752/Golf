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
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}
void Graphic::render(SDL_Texture* p_tex)
{
    SDL_RenderCopy(renderer, p_tex, NULL, NULL);
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
void Graphic::display()
{
    SDL_RenderPresent(renderer);
}
void Graphic::quitSDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
void Graphic::clear()
{
    SDL_RenderClear(renderer);
}
