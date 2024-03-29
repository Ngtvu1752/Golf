#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>

#include "graphic.h"
#include "Ball.h"
using namespace std;

//void logErrorAndExit(const char*msg, const char* error)
//{
//    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
//    SDL_Quit();
//}

Graphic window(WIDTH, HEIGHT, Window_Title);
Vector2f pos(200,200);
SDL_Texture* pointTex = window.loadingTexture("img/point.png");
void keyPress()
{
    SDL_Event e;
    while(true)
    {
        while(SDL_PollEvent(&e))
        {
            int x, y;
            SDL_GetMouseState(&x,&y);
//            cout<<x<<' '<<y<<'\n';
            if(e.type == SDL_QUIT || e.type == SDL_KEYDOWN)
                return;
            SDL_Delay(100);
        }

    }
}
Uint64 curTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;
bool mousePressed = 0, mouseDown = 0;

int main( int argc, char* args[])
{
    SDL_Texture* bg = window.loadingTexture("img/bg.png");
    window.render(bg);
    window.display();
    keyPress();
    SDL_Texture* ballTex = window.loadingTexture("img/ball.png");
    Ball ball(pos, ballTex);
    window.renderEntity(ball);
    window.display();

    SDL_Event e;

    while(true)
    {
        mousePressed = 0;
        lastTick = curTick;
        curTick = SDL_GetPerformanceCounter();
        deltaTime = double((curTick - lastTick)*1000/(double)(SDL_GetPerformanceFrequency()));
        while(SDL_PollEvent(&e))
        {
            switch(e.type)
            {
            case SDL_QUIT:
                return 0;
                SDL_Delay(1000);
            case SDL_MOUSEBUTTONDOWN:
                if(e.button.button == SDL_BUTTON_LEFT)
                {
                    mousePressed = 1;
                    mouseDown = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if(e.button.button  == SDL_BUTTON_LEFT)
                {
                    mouseDown = 0;
                }
                break;
            }
        }
        ball.update(deltaTime, mousePressed, mouseDown);
        window.clear();
        window.render(bg);
        window.renderEntity(ball);
        window.display();

    }
    SDL_DestroyTexture(ballTex);
    ballTex = NULL;
    SDL_DestroyTexture(bg);
    bg = NULL;
    window.quitSDL();
    return 0;
}
