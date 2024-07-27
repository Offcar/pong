#include "raylib.h"

typedef struct {
    int x;
    int y;
    int speed;
    int height;
    int width;
} Paddle;

typedef struct {
    int x;
    int y;
    int radius;
    int speedX;
    int speedY;
} Ball;

typedef enum {
} GAMESTATUS;

typedef enum {
    WAIT,
    RUNNING,
    END,
} ROUNDSTATUS;


#define SWIDTH 800
#define SHEIGHT 500
#define TOP 30
#define BOTTOM SHEIGHT - TOP


void calculatePlayer(Paddle *p, KeyboardKey up, KeyboardKey down) {
    if (IsKeyDown(up)) {
        if (p->y - p->speed <= TOP) {
            p->y = TOP;
        } else {
            p->y -= p->speed;
        }
    }

    if (IsKeyDown(down)) {
        if (p->y + p->speed + p->height >= BOTTOM) {
            p->y = BOTTOM - p->height;
        } else {
            p->y += p->speed;
        }
    }
}

void calculateCPU(Paddle *CPU) {}

void launchBall() {

}

void ballLaunch(Ball *ball, int speedX, int speedY) {
    if(GetRandomValue(0, 1) == 1) {
        ball->speedX = speedX;
        ball->speedY = speedY;
    } else {
        ball->speedX = -speedX;
        ball->speedY = -speedY;
    }
}

void ballReset() {

}

void calculatePaddles(Paddle *p1, Paddle *p2, int isPlayer2Enabled) {
    calculatePlayer(p1, KEY_W, KEY_S);

    if(isPlayer2Enabled == 1) {
        calculatePlayer(p2, KEY_UP, KEY_DOWN);
    } else {
        calculateCPU(p2);
    }
}

int main(int argc, char **arvg) {
    Paddle p1 = {30, SHEIGHT / 2 - 50, 30, 100, 20};
    Paddle p2 = {SWIDTH - (p1.x + p1.width), p1.y, 30, 100, 20};
    Ball ball = {SWIDTH/2, SHEIGHT/2, 10, 0, 0};
    
    ROUNDSTATUS round = WAIT;
    
    InitWindow(SWIDTH, SHEIGHT, "Pong - Raylib/C implementation");

    SetTargetFPS(20);
    while (!WindowShouldClose()) {
        calculatePaddles(&p1, &p2, 1);

        /*
        switch(round){
            case WAIT:

                draw background, stationary elements in round start
                wait for space/enter
                exit when key is pressed
                exit => round = RUNNING

                break;
            case RUNNING:

                game runs, calculates and draws paddles and ball
                ball increases speed on every bounce ??
                when ball hits x 0 or x SWIDTH update score
                round = WAIT
                discount live or point (ft10?)

                break;
            case END:

                one player lost all lives
                declare winer, clear window, display winner
                closes game and starts again

                break;
        }
        */



        BeginDrawing();
        ClearBackground(BLACK);
        // BorderLimits
        DrawRectangle(0, 0, SWIDTH, TOP, GRAY);
        DrawRectangle(0, BOTTOM, SWIDTH, BOTTOM, GRAY);
        // Center screen split
        DrawLine(SWIDTH / 2, 0, SWIDTH / 2, SHEIGHT, GRAY);
        DrawRectangle(p1.x, p1.y, p1.width, p1.height, RAYWHITE);
        DrawRectangle(p2.x, p2.y, p2.width, p2.height, RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
}

