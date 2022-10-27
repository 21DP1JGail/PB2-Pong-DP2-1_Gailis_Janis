#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>
using namespace std;
using namespace chrono;

using frame = duration<int32_t, ratio<1,66>>;
using ms = duration<float,milli>;

struct Ball{
    double VelX, VelY, centerX, centerY, r;
    Ball(double startVelx, double startVelY, double startX, double startY, double r);
};

struct player{
    double x1, y1;
    player(double startx1, double starty1);
};
Ball::Ball(double startVelX, double startVelY, double startX, double startY, double startR){
        if (startVelY == 0) {
            VelY = 0.5    ;
        }
        else
            VelY = -0.5;
        if (startVelX == 0) {
            VelX = 0.011;
        }
        else
            VelX = -0.011;
        centerX = startX;
        centerY = startY;
        r = startR;
    }

player::player(double startx1, double starty1){
    x1 = startx1;
    y1 = starty1;
}

void DrawCircle(SDL_Renderer * Render, double centerX, double centerY, double radius)
{

    const double diameter = (radius * 2);
    double x = (radius - 1);
    double y = 0;
    double tx = 1;
    double ty = 1;
    double error = (tx - diameter);
    while (x >= y) {
        SDL_RenderDrawPoint(Render, centerX + x, centerY - y);
        SDL_RenderDrawPoint(Render, centerX + x, centerY + y);
        SDL_RenderDrawPoint(Render, centerX - x, centerY - y);
        SDL_RenderDrawPoint(Render, centerX - x, centerY + y);
        SDL_RenderDrawPoint(Render, centerX + y, centerY - x);
        SDL_RenderDrawPoint(Render, centerX + y, centerY + x);
        SDL_RenderDrawPoint(Render, centerX - y, centerY - x);
        SDL_RenderDrawPoint(Render, centerX - y, centerY + x);
        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }
        if (error > 0) {
            --x;
            tx += 2;
           error += (tx - diameter);
        }
    }
}
int main(int argc, char* args[])
{
    int SCREEN_WIDTH = 750;
    int SCREEN_HEIGHT = 700;
    SDL_Window* Screen = SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    SDL_Renderer* Render = SDL_CreateRenderer( Screen, -1, 0 );
    bool quit = false;
    player p1(SCREEN_WIDTH/2 - 125/2, 20);
    player p2(SCREEN_WIDTH/2 - 125/2, 660);
    Ball cum(rand() % 2,rand() % 2,SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 15);
    while( !quit ) {
        time_point<steady_clock> fpsTimer(steady_clock::now());
        frame FPS{};
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {

            if (e.type == SDL_QUIT) {

                quit = true;
            }


            const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_LEFT]) {
                p1.x1 -= 10;
            }
            if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
                p1.x1 += 10;
            }
            if (currentKeyStates[SDL_SCANCODE_A]) {
                p2.x1 -= 10;
            }
            if (currentKeyStates[SDL_SCANCODE_D]) {
                p2.x1 += 10;
            }

            if (p1.x1 < 0)
                p1.x1 = 0;
            if (p1.x1 + 125 > SCREEN_WIDTH)
                p1.x1 = SCREEN_WIDTH - 125;
            if (p2.x1 < 0)
                p2.x1 = 0;
            if (p2.x1 + 125 > SCREEN_WIDTH)
                p2.x1 = SCREEN_WIDTH - 125;

        }
        if (cum.centerX < 7.5)
            cum.VelX = -cum.VelX;
        if (cum.centerX > SCREEN_WIDTH - 7.5)
            cum.VelX = -cum.VelX;


        if (p1.x1 - 10 < cum.centerX and p1.x1 + 135 > cum.centerX and cum.centerY == 50) {
            cum.VelY = -cum.VelY;
            if (p1.x1 - 10 < cum.centerX and p1.x1 + 62.5 > cum.centerX) {
                cum.VelX = -0.05 - rand() % 20 * 0.01;
            } else {
                cum.VelX = 0.05 + rand() % 20 * 0.01;
            }
        }
        if (p2.x1 - 10 < cum.centerX and p2.x1 + 135 > cum.centerX and cum.centerY  == 645) {
            cum.VelY = -cum.VelY;
            if (p2.x1 - 10 < cum.centerX and p2.x1 + 62.5 > cum.centerX) {
                cum.VelX = -0.05 - rand() % 20 * 0.01;
            } else {
                cum.VelX = 0.05 + rand() % 20 * 0.01;
            }
        }
        SDL_SetRenderDrawColor(Render, 0, 0, 0, 255);
        SDL_RenderClear(Render);
        SDL_SetRenderDrawColor(Render, 255, 255, 255, 255);
        cum.centerX += cum.VelX;
        cum.centerY += cum.VelY;
        DrawCircle(Render, cum.centerX, cum.centerY, cum.r);
        SDL_Rect Draw = {int(p1.x1), int(p1.y1), 125, 15};
        SDL_Rect Draw2 = {int(p2.x1), int(p2.y1), 125, 15};
        SDL_RenderFillRect(Render, &Draw);
        SDL_RenderFillRect(Render, &Draw2);
        SDL_RenderPresent(Render);
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_R] and (cum.centerY < 50 or cum.centerY > 645)){
        cum.centerY = SCREEN_HEIGHT / 2;
        cum.centerX = SCREEN_WIDTH / 2;
}

        while (true)
        {
            FPS = duration_cast<frame>(steady_clock::now() - fpsTimer);

            if (FPS.count() >= 1) {
                fpsTimer = steady_clock::now();
            }
        break;
            }
        }


    SDL_DestroyWindow( Screen );
    SDL_Quit();
    return 0;
}
