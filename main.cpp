# include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include "graphic.h"
#include "Ball.h"
#include "Hole.h"
#include "Button.h"
#include "Timer.h"
using namespace std;

//void logErrorAndExit(const char*msg, const char* error)
//{
//    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
//    SDL_Quit();
//}
Button but, buttonNewGame;
Graphic window(WIDTH, HEIGHT, Window_Title);
Timer timer;
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
SDL_Texture* golfClub = window.loadingTexture("img/golfclub.png");
SDL_Texture* button = window.loadingTexture("img/button.png");
SDL_Texture* newGame = window.loadingTexture("img/newGame.png");

SDL_Texture* corner = window.loadingTexture("img/block_corner_large.png");
SDL_Texture* cir = window.loadingTexture("img/block_rotate_narrow.png");
Mix_Chunk* collision = Mix_LoadWAV("music/swing.mp3");
Mix_Chunk* holeSfx = Mix_LoadWAV("music/hihi.mp3");
Mix_Chunk* hit = Mix_LoadWAV("music/hit.mp3");

Ball ball = Ball(pos, ballTex, pointTex, powerBE, powerFE);
Hole hole(Vector2f(300,300), holeTex);

TTF_Font* font32 = window.loadFont("font.ttf", 32);
TTF_Font* font48 = window.loadFont("font.ttf", 48);
TTF_Font* font24 = window.loadFont("font.ttf", 24);
SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
int lv = 1;
vector<Entity> wall ;
Entity circle(Vector2f(300,300), cir);
Entity club(Vector2f(0,0), golfClub);
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
SDL_Rect clip[BUTTON_SPRITE_TOTAL];
SDL_Rect clipClub[3];
void rectClub()
{
    clipClub[0].x = 0;
    clipClub[0].y = 0;
    clipClub[0].w = 0;
    clipClub[0].h = 0;

    clipClub[1].x = 0;
    clipClub[1].y = 0;
    clipClub[1].w = 16;
    clipClub[1].h = 17;

    clipClub[2].x = 0;
    clipClub[2].y = 17;
    clipClub[2].w = 16;
    clipClub[2].h = 16;
}
void rectButton()
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
        ball.setPos(160, 240);
        hole.setPos(635,240);
        wall.push_back(Entity(Vector2f(380,215),blockB));
        wall.push_back(Entity(Vector2f(300,165),wallS));
        wall.push_back(Entity(Vector2f(300 + 128+1, 165),wallS));
        wall.push_back(Entity(Vector2f(300 + 128*2+1,165),wallS));
        wall.push_back(Entity(Vector2f(300 ,305),wallS));
        wall.push_back(Entity(Vector2f(300 +128+1,305),wallS));
        wall.push_back(Entity(Vector2f(300+128*2+1,305),wallS));
    }
    if(lv == 4)
    {
        ball.setPos(240, 260);
        hole.setPos(570,100);
        wall.push_back(Entity(Vector2f(324,111),wallS));
        wall.push_back(Entity(Vector2f(400,238),wallS));
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
                club.setCurframe(clipClub[2]);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(e.button.button  == SDL_BUTTON_LEFT)
            {
                Mix_PlayChannel(-1, hit, 0);
                mouseDown = 0;
                club.setCurframe(clipClub[1]);
            }
            break;
        }
    }
    ball.update(deltaTime, mousePressed, mouseDown, hole, wall, holeSfx, collision);
    if(ball.getScale().x <-1 && ball.getScale().y <-1)
    {
        lv++;
        cntHole++;
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
const char* getHole()
{
    string s = to_string(cntHole);
    string s1 = "HOLE: " + s;
    return s1.c_str();
}
void show()
{
    window.Clear();
    window.renderTexture(0,0,bg);
    window.renderEntity(hole);
    club.setPos(ball.getPos().x - 10, ball.getPos().y - 10);
    for(Entity& e : ball.getPoint())
    {
        window.renderEntity(e);
    }
    for(Entity& f : ball.getBar())
    {
        window.renderEntity(f);
    }

    if(lv == 3)
    {
                wall[0].setPos(wall[0].getPos().x, 215+ 20 * SDL_sin(SDL_GetTicks()*(3.14/1500)));

    }
    for(Entity& w : wall)
    {
        window.renderEntity(w);
    }

    window.renderTexture(ball.getBar()[0].getPos().x, ball.getBar()[0].getPos().y, power);
    window.renderEntity(ball);
    window.renderEntity(club);
    if(state == 2)
    {
        window.renderText(0, 16 + 3, getTex(), font24, black);
        window.renderText(0, 16, getTex(), font24, white);
        window.renderText(WIDTH - 100, 0, getHole(), font24, white);
    }
    window.display();
}


void menu()
{

    if(state == 0)
    {
        window.Clear();
        window.renderTexture(0,0, bg3);
        window.renderTexture(64*2, 32 + 4 * SDL_sin(SDL_GetTicks()*(3.14/1500)), logo);
        window.renderEntity(circle);
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
    if( state == 1)
    {
        window.Clear();
        window.renderTexture(0,0,bg3);
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                gameRunning = false;
            }
            buttonNewGame.handleEvent(&e);
            if(buttonNewGame.getButton() == BUTTON_SPRITE_MOUSE_DOWN)
            {
                if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    state = 2;
                }
            }
        }
        window.render(newGame,WIDTH/2 - 32*3,HEIGHT/2,&clip[buttonNewGame.getButton()]);
        window.display();
    }

}
void game()
{
    if(state <= 1)
    {
        menu();
    }
    else
    {
        update();
        show();
    }
}
float degrees = 0;
int main( int argc, char* args[])
{
    rectButton();
    rectClub();
    club.setCurframe(clipClub[0]);
    if(holeSfx == NULL)
    {
        cout<<11111;
    }
//    Button.setCurframe(0,0, Button.getCurrFrame().w, Button.getCurrFrame().h/2);
//    window.renderEntity(Button);
//    window.display();
//    keyPress();
    loadLevel(lv);
    timer.start();
    while(gameRunning)
    {
        Uint32 ticks = timer.getTicks();
        if(ticks >= 1)
        {
            degrees += 4;
            circle.setAngle(degrees);
            ball.setAngle(degrees);
            timer.pause();
            game();
            timer.start();
        }
    }
    SDL_DestroyTexture(ballTex);
    ballTex = NULL;
    SDL_DestroyTexture(bg3);
    bg3 = NULL;
    window.quitSDL();
    return 0;
}
