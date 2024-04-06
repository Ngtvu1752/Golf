#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include "graphic.h"
#include "Ball.h"
#include "Hole.h"

using namespace std;

//void logErrorAndExit(const char*msg, const char* error)
//{
//    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
//    SDL_Quit();
//}

Graphic window(WIDTH, HEIGHT, Window_Title);
Vector2f pos(200,200);
SDL_Texture* bg = window.loadingTexture("img/bg.png");
SDL_Texture* pointTex = window.loadingTexture("img/point.png");
SDL_Texture* holeTex = window.loadingTexture("img/hole.png");
SDL_Texture* ballTex = window.loadingTexture("img/ball.png");
SDL_Texture* powerBE = window.loadingTexture("img/powermeter_bg.png");
SDL_Texture* powerFE = window.loadingTexture("img/powermeter_fg.png");
SDL_Texture* power = window.loadingTexture("img/powermeter_overlay.png");
Mix_Chunk* chargeSfx = Mix_LoadWAV("music/charge.mp3");
Mix_Chunk* holeSfx = Mix_LoadWAV("music/hihi.mp3");

Ball ball = Ball(pos, ballTex, pointTex, powerBE, powerFE);
Hole hole(Vector2f(300,300), holeTex);

int state = 0;
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
bool gameRunning = 1;
bool win = 0;
SDL_Event e;
void update()
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
                gameRunning = 0;
                break;
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
        ball.update(deltaTime, mousePressed, mouseDown, hole,holeSfx);
        window.clear();
        window.render(bg);
        window.renderEntity(hole);

        for(Entity& e : ball.getPoint())
        {
            window.renderEntity(e);
        }
        for(Entity& f : ball.getBar())
        {
            window.renderEntity(f);
        }
        window.renderTexture(ball.getBar().at(0).getPos().x, ball.getBar().at(0).getPos().y, power);
        window.renderEntity(ball);
        window.display();
}

//void game()
//{
//    if(state == 0)
//    {
//        titleScreen();
//    }
//    else
//    {
//        update();
//    }
//}
int main( int argc, char* args[])
{
    window.render(bg);
    window.display();
    keyPress();
    window.renderEntity(ball);
    window.display();
    keyPress();
    window.renderEntity(hole);
    window.display();
    SDL_Event e;
    if(holeSfx == NULL)
    {
        cout<<11111;
    }
    ball.setWin(false);
    while(true)
    {
        update();
        if(gameRunning == 0) break;
    }
    SDL_DestroyTexture(ballTex);
    ballTex = NULL;
    SDL_DestroyTexture(bg);
    bg = NULL;
    window.quitSDL();
    return 0;
}
