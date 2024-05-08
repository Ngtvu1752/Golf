#include<bits/stdc++.h>
#include "graphic.h"
#include "Ball.h"
#include "Button.h"
#include "Timer.h"
using namespace std;
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
SDL_Texture* quit = window.loadingTexture("img/exit.png");
SDL_Texture* ending = window.loadingTexture("img/endscreen.png");
SDL_Texture* cir = window.loadingTexture("img/block_rotate_narrow.png");

Mix_Chunk* collision = window.loadSound("music/swing.mp3");
Mix_Chunk* holeSfx = window.loadSound("music/hihi.mp3");
Mix_Chunk* hit = window.loadSound("music/hit.mp3");
Mix_Chunk* click = window.loadSound("music/pick.mp3");
Ball ball = Ball(pos, ballTex, pointTex, powerBE, powerFE);
Hole hole(Vector2f(300,300), holeTex);
Button butPlay, butQuit;
TTF_Font* font32 = window.loadFont("font.ttf", 32);
TTF_Font* font48 = window.loadFont("font.ttf", 48);
TTF_Font* font24 = window.loadFont("font.ttf", 24);
SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
int lv = 1;
vector<Entity> wall ;
Entity circle(Vector2f(200,300), cir);
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
    circle.free();
    club.free();
    ball.free();
    TTF_CloseFont(font24);
    TTF_CloseFont(font32);
    TTF_CloseFont(font48);
    Mix_FreeChunk(collision);
    Mix_FreeChunk(hit);
    Mix_FreeChunk(click);
    Mix_FreeChunk(holeSfx);
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
    clipClub[1].w = 256;
    clipClub[1].h = 177;

    clipClub[2].x = 0;
    clipClub[2].y = 177;
    clipClub[2].w = 256;
    clipClub[2].h = 177;
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
    if(lv > 5)
    {
        state = 2;
    }
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
        ball.setPos(32*4,HEIGHT/2);
        hole.setPos(64*9,HEIGHT/2);

        wall.push_back(Entity(Vector2f(21*15,21*5), blockS));
        wall.push_back(Entity(Vector2f(21*17,21*7), blockS));
        wall.push_back(Entity(Vector2f(21*12,21*8), blockS));
        wall.push_back(Entity(Vector2f(21*14,21*9), blockS));
        wall.push_back(Entity(Vector2f(21*13,21*14), blockS));
        wall.push_back(Entity(Vector2f(21*13,21*14), blockS));
        wall.push_back(Entity(Vector2f(21*13,21*14), blockS));
        wall.push_back(Entity(Vector2f(21*17,21*18), blockS));
        wall.push_back(Entity(Vector2f(21*20,21*12), blockS));
        wall.push_back(Entity(Vector2f(21*23,21*17), blockS));
        wall.push_back(Entity(Vector2f(21*25,21*18), blockS));
        wall.push_back(Entity(Vector2f(21*30,21*8), blockS));
        wall.push_back(Entity(Vector2f(21*33,21*10), blockS));
        wall.push_back(Entity(Vector2f(21*25,21*8), blockS));
        wall.push_back(Entity(Vector2f(21*28,21*13), blockS));
        wall.push_back(Entity(Vector2f(21*2,21*2), blockB));
        wall.push_back(Entity(Vector2f(21*20,21*2), blockB));
    }
    if(lv == 4)
    {
        ball.setPos(160, 240);
        hole.setPos(635,240);
        wall.push_back(Entity(Vector2f(380,215),blockB));
        wall.push_back(Entity(Vector2f(300,165),wallS));
        wall.push_back(Entity(Vector2f(300 + 128+1, 165),wallS));
        wall.push_back(Entity(Vector2f(300 + 128*2+1,165),wallS));
        wall.push_back(Entity(Vector2f(300,305),wallS));
        wall.push_back(Entity(Vector2f(300 +128+1,305),wallS));
        wall.push_back(Entity(Vector2f(300+128*2+1,305),wallS));
    }
    if(lv == 5)
    {
        ball.setPos(240, 260);
        hole.setPos(570,100);
        wall.push_back(Entity(Vector2f(324,111),wallS));
        wall.push_back(Entity(Vector2f(400,238),wallS));
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
//                club.setCurframe(clipClub[2]);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(e.button.button  == SDL_BUTTON_LEFT)
            {
                Mix_PlayChannel(-1, hit, 0);
                mouseDown = 0;
                sprite = 1;
//                club.setCurframe(clipClub[1]);
            }
            break;
        }
    }
    if(state == 1)
    {
        ball.update(deltaTime, mousePressed, mouseDown, &hole, &wall, holeSfx, collision, hit);
        if(ball.getScale().x < 0)
        {
            lv++;
            cntHole++;
            wall.clear();
            loadLevel(lv);
        }
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

const char* getTopScore()
{
    int topScore = 0;
    string topScoreFile = "topscore.txt";
    ifstream infile(topScoreFile);
    if(infile.is_open())
    {
        infile >> topScore;
        infile.close();
    }
    int playScore = ball.getSwings();
    if(playScore <= topScore)
    {
        topScore = playScore;
        ofstream outFile("topscore.txt");
        if(outFile.is_open())
        {
            outFile<<topScore;
            outFile.close();
        }
        string s = to_string(topScore);
        string best = "BEST SWING: " + s;
        return best.c_str();
    }
    else
    {
        string s = "You need to try harder!!!!!";
        return s.c_str();
    }

}

void show()
{
    SDL_DestroyTexture(bg3);
    bg3= NULL;
    SDL_DestroyTexture(logo);
    logo= NULL;
    window.Clear();
    window.renderTexture(0,0,bg);
    window.renderEntity(hole);
    club.setCurframe(&clipClub[sprite]);
    for(Entity& e : ball.getPoint())
    {
        window.renderEntity(e);
    }
    for(Entity& w : wall)
    {
        window.renderEntity(w);
    }
    for(Entity& f : ball.getBar())
    {
        window.renderEntity(f);
    }
    if(lv == 4)
    {
        wall[0].setPos(wall[0].getPos().x, 215+ 20 * SDL_sin(SDL_GetTicks()*(3.14/1500)));

    }
    window.renderTexture(ball.getBar()[0].getPos().x, ball.getBar()[0].getPos().y, power);
    window.renderEntity(club);
    window.renderEntity(ball);
    if(state == 1)
    {
        window.renderText(0, 3, getTex(), font24, black);
        window.renderText(0, 0, getTex(), font24, white);
        window.renderText(WIDTH - 100, 3, getHole(), font24, black);
        window.renderText(WIDTH - 100, 0, getHole(), font24, white);
    }
    else
    {
        window.renderTexture(0,0,ending);
        window.renderText(200,200 +3, "YOU COMPLETED THE GAME", font48,black);
        window.renderText(200,200, "YOU COMPLETED THE GAME", font48,white);
        window.renderText(250, 200 + 60, getTopScore(), font32, black);
        window.renderText(250, 200 + 60 +3, getTopScore(), font32, white);
        butQuit.setPos(WIDTH/2 - 32*3, 280);
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                gameRunning = false;
            }
            butQuit.handleEvent(&e);
            if(butQuit.getButton() == BUTTON_SPRITE_MOUSE_DOWN)
            {
                if(e.type == SDL_MOUSEBUTTONDOWN)
                {
                    Mix_PlayChannel(-1,click,0);
                    gameRunning = false;
                }
            }
        }
        window.render(quit,WIDTH/2 - 32*3,HEIGHT/2 + 70,&clip[butQuit.getButton()]);
    }
    window.display();
    club.setPos(ball.getPos().x - 64 -28 - 43 - 20, ball.getPos().y - 150 + 10);
}

void menu()
{
    butQuit.setPos(WIDTH/2 - 32*3, HEIGHT/2 + 70);
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
        butPlay.handleEvent(&e);
        if(butPlay.getButton() == BUTTON_SPRITE_MOUSE_DOWN)
        {
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {

                Mix_PlayChannel(-1,click,0);SDL_Delay(1000);
                state = 1;
            }
        }
        butQuit.handleEvent(&e);
        if(butQuit.getButton() == BUTTON_SPRITE_MOUSE_DOWN)
        {
            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                Mix_PlayChannel(-1,click,0);
                gameRunning = false;
            }
        }
    }
    window.render(button,WIDTH/2 - 32*3,HEIGHT/2,&clip[butPlay.getButton()]);
    window.render(quit,WIDTH/2 - 32*3,HEIGHT/2 + 70,&clip[butQuit.getButton()]);
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
float degrees = 0;
int main( int argc, char* args[])
{
    rectButton();
    rectClub();
    club.setCurframe(&clipClub[0]);
    loadLevel(lv);
    timer.start();
    while(gameRunning)
    {
        Uint32 ticks = timer.getTicks();
        if(ticks >= 1)
        {
            degrees += 4;
            if(degrees >=360) degrees = 0;
            circle.setAngle(degrees);
            ball.setAngle(degrees);
            timer.pause();
            game();
            timer.start();
        }
    }
    destroy();
    window.quitSDL();
    return 0;
}
