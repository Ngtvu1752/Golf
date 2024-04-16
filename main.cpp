#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include "graphic.h"
#include "Ball.h"
#include "Hole.h"
#include "Button.h"
using namespace std;

//void logErrorAndExit(const char*msg, const char* error)
//{
//    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
//    SDL_Quit();
//}
Button but;
Graphic window(WIDTH, HEIGHT, Window_Title);
Vector2f pos(200,200);
SDL_Texture* bg3 = window.loadingTexture("img/bg3.png");
SDL_Texture* bg = window.loadingTexture("img/bg.png");
SDL_Texture* pointTex = window.loadingTexture("img/point.png");
SDL_Texture* holeTex = window.loadingTexture("img/hole.png");
SDL_Texture* ballTex = window.loadingTexture("img/ball_blue.png");
SDL_Texture* powerBE = window.loadingTexture("img/powermeter_bg.png");
SDL_Texture* powerFE = window.loadingTexture("img/powermeter_fg.png");
SDL_Texture* power = window.loadingTexture("img/powermeter_overlay.png");
SDL_Texture* wallB = window.loadingTexture("img/block_large.png");
SDL_Texture* wallS = window.loadingTexture("img/block_narrow.png");
SDL_Texture* blockB = window.loadingTexture("img/block_square.png");
SDL_Texture* blockS = window.loadingTexture("img/block_small.png");
SDL_Texture* logo = window.loadingTexture("img/logo.png");
SDL_Texture* button = window.loadingTexture("img/button.png");
SDL_Texture* corner = window.loadingTexture("img/block_corner_large.png");
Mix_Chunk* collision = Mix_LoadWAV("music/swing.mp3");
Mix_Chunk* holeSfx = Mix_LoadWAV("music/hihi.mp3");

Ball ball = Ball(pos, ballTex, pointTex, powerBE, powerFE);
Hole hole(Vector2f(300,300), holeTex);

TTF_Font* font32 = window.loadFont("font.ttf", 32);
TTF_Font* font48 = window.loadFont("font.ttf", 48);
TTF_Font* font24 = window.loadFont("font.ttf", 24);
SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
int lv = 1;
vector<Entity> wall ;

void destroy()
{
    SDL_DestroyTexture(blockB);
    blockB = NULL;
    SDL_DestroyTexture(blockS);
    blockS = NULL;
    SDL_DestroyTexture(wallB);
    wallB = NULL;
    SDL_DestroyTexture(wallS);
    wallS = NULL;
    SDL_DestroyTexture(power);
    power = NULL;
    SDL_DestroyTexture(powerBE);
    powerBE = NULL;
    SDL_DestroyTexture(powerFE);
    powerFE = NULL;
    SDL_DestroyTexture(ballTex);
    ballTex = NULL;
    SDL_DestroyTexture(pointTex);
    pointTex = NULL;
    SDL_DestroyTexture(holeTex);
    holeTex= NULL;
    SDL_DestroyTexture(bg3);
    bg3= NULL;
}
void loadLevel(int lv)
{
    ball.setVelocity(0,0);
    ball.setScale(1,1);
    ball.setWin(false);

    if(lv == 1)
    {
        ball.setPos(32*4,HEIGHT/2);
        hole.setPos(64*9,HEIGHT/2);

    }
    if(lv == 2)
    {
        ball.setPos(32*4,HEIGHT/2);
        hole.setPos(64*9,HEIGHT/2);
        wall.push_back(Entity(Vector2f(370, 180),wallB));
    }
    if(lv == 3)
    {
        ball.setPos(32*4, 32*7);
        hole.setPos(200,200);
        wall.push_back(Entity(Vector2f(32*9,32),wallB));
        wall.push_back(Entity(Vector2f(64*4,64*6),wallB));
        wall.push_back(Entity(Vector2f(32,32),wallS));
        wall.push_back(Entity(Vector2f(0,HEIGHT - 128), corner));
    }
    if(lv == 4)
    {
        ball.setPos(240, 260);
        hole.setPos(570,100);
        wall.push_back(Entity(Vector2f(324,111),blockB));
        wall.push_back(Entity(Vector2f(400,238),blockB));
    }
}
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
    ball.update(deltaTime, mousePressed, mouseDown, hole, wall, holeSfx, collision);
    if(ball.getScale().x <-1 && ball.getScale().y <-1)
    {
        lv++;
        wall.clear();
        loadLevel(lv);
    }

}
const char* getTex()
{
    int cnt = ball.getSwings();
    string s = to_string(cnt);
    string s1 = "SWINGS: " + s;
    return s1.c_str();
}
void show()
{
    window.Clear();
    window.renderTexture(0,0,bg);
    window.renderEntity(hole);

    for(Entity& e : ball.getPoint())
    {
        window.renderEntity(e);
    }
    for(Entity& f : ball.getBar())
    {
        window.renderEntity(f);
    }
    for(Entity& w : wall)
    {
        window.renderEntity(w);
    }
    window.renderTexture(ball.getBar()[0].getPos().x, ball.getBar()[0].getPos().y, power);
    window.renderEntity(ball);
    if(state == 1)
    {
        window.renderText(0, 16 + 3, getTex(), font24, black);
		window.renderText(0, 16, getTex(), font24, white);
    }
    window.display();
}
SDL_Rect clip[BUTTON_SPRITE_TOTAL];
void rect()
{
    clip[0].x = 0;
    clip[0].y = 0;
    clip[0].w = BUTTON_WIDTH;
    clip[0].h = BUTTON_HEIGHT;

    clip[1].x = 0;
    clip[1].y = 65;
    clip[1].w = BUTTON_WIDTH;
    clip[1].h = BUTTON_HEIGHT;
}

void menu()
{
    rect();
    window.Clear();
    window.renderTexture(0,0, bg3);
    window.renderTexture(64*2, 32 + 4 * SDL_sin(SDL_GetTicks()*(3.14/1500)), logo);
    while(SDL_PollEvent(&e))
    {
        if(e.type == SDL_QUIT)
        {
            gameRunning = false;
        }
        but.handleEvent(&e);
        if(but.getButton() == BUTTON_SPRITE_MOUSE_DOWN)
        {
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                state = 1;
            }
        }
    }
    window.render(button,WIDTH/2 - 32*3,HEIGHT/2,&clip[but.getButton()]);
    window.display();

}
void game()
{
    if(state == 0)
    {
        menu();
    }
    else
    {
        update();
        show();
    }
}
int main( int argc, char* args[])
{
    if(holeSfx == NULL)
    {
        cout<<11111;
    }
//    Button.setCurframe(0,0, Button.getCurrFrame().w, Button.getCurrFrame().h/2);
//    window.renderEntity(Button);
//    window.display();
//    keyPress();
    loadLevel(lv);
    while(gameRunning)
    {
        game();
    }
    SDL_DestroyTexture(ballTex);
    ballTex = NULL;
    SDL_DestroyTexture(bg3);
    bg3 = NULL;
    window.quitSDL();
    return 0;
}
