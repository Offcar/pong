#include "raylib.h"
#include "stdio.h"
#include "stdlib.h"

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
    int height;
    int width;
    int speedX;
    int speedY;
} Ball;

/* typedef enum { } GAMESTATUS; */

typedef enum {
    WAIT,
    RUNNING,
    END,
} ROUNDSTATUS;

#define SWIDTH 800
#define SHEIGHT 500
#define TOP 30
#define BOTTOM SHEIGHT - TOP
#define BALLSPEED 20

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

void ballLaunch(Ball *ball) {
    int randX = GetRandomValue(0, 1);
    int randY = GetRandomValue(0, 1);

    if (randX == 1) {
        /* ball->speedX = BALLSPEED; */
    } else {
        /* ball->speedX = -BALLSPEED; */
    }

    if (randY == 1) {
        ball->speedY = BALLSPEED;
    } else {
        ball->speedY = -BALLSPEED;
    }
}

void ballReset(Ball *ball, int *bounces) {
    ball->x = SWIDTH / 2 - (int)ball->width / 2;
    ball->y = SHEIGHT / 2 - (int)ball->height / 2;
    ball->speedX = 0; //BALLSPEED;
    ball->speedY = BALLSPEED;

    bounces = 0;
}

void paddleReset(Paddle *p1, Paddle *p2) {
    p1->x = 30;
    p1->y = SHEIGHT / 2 - 50;

    p2->x = SWIDTH - (p1->x + p1->width);
    p2->y = p1->y;
}

void calculatePaddles(Paddle *p1, Paddle *p2, int isPlayer2Enabled) {
    calculatePlayer(p1, KEY_W, KEY_S);

    if (isPlayer2Enabled == 1) {
        calculatePlayer(p2, KEY_UP, KEY_DOWN);
    } else {
        calculateCPU(p2);
    }
}

void DrawPaddles(Paddle *p1, Paddle *p2, Color color) {
    DrawRectangle(p1->x, p1->y, p1->width, p1->height, color);
    DrawRectangle(p2->x, p2->y, p2->width, p2->height, color);
}

void DrawBackground() {
    DrawRectangle(0, 0, SWIDTH, TOP, GRAY);
    DrawRectangle(0, BOTTOM, SWIDTH, BOTTOM, GRAY);
    DrawLine(SWIDTH / 2, 0, SWIDTH / 2, SHEIGHT, GRAY);
}

void DrawBall(Ball *b, Color color) {
    DrawRectangle(b->x, b->y, b->width, b->height, color);
}

void calculateBallNextStep(Ball *b) {
    int nextStepX = b->x + b->speedX;
    int nextStepY = b->y + b->speedY;

    if (b->speedY < 0 && nextStepY < TOP) {  // UP
        b->speedY *= -1;
    } else if (b->speedY > 0 && nextStepY + b->height > BOTTOM) {  // DOWN
        b->speedY *= -1;
    }



    b->x += b->speedX;
    b->y += b->speedY;
}

int main(int argc, char **arvg) {
    Paddle p1 = {30, SHEIGHT / 2 - 50, 30, 100, 20};
    Paddle p2 = {SWIDTH - (p1.x + p1.width), p1.y, 30, 100, 20};
    Ball ball = {SWIDTH / 2, SHEIGHT / 2, 15, 15, 0, 0};
    int bounces = 0;

    int i = 0;

    ROUNDSTATUS round = WAIT;

    InitWindow(SWIDTH, SHEIGHT, "Pong - Raylib/C implementation");

    SetTargetFPS(30);
    while (!WindowShouldClose()) {
        printf(
            "Step: %d | ballX: %d | ballY: %d | ballSpeedX: %d | ballSpeedY: "
            "%d \n",
            i, ball.x, ball.y, ball.speedX, ball.speedY);

        switch (round) {
            case WAIT:
                BeginDrawing();
                ClearBackground(BLACK);

                DrawPaddles(&p1, &p2, GRAY);
                DrawBall(&ball, GRAY);
                DrawBackground();

                // Centrar bien yisus christ
                DrawText("PRESS SPACE TO START ROUND", SWIDTH / 2 - 180,
                         SHEIGHT / 2 - 20, 20, RAYWHITE);

                if (IsKeyDown(KEY_SPACE)) {
                    round = RUNNING;
                }

                EndDrawing();
                break;
            case RUNNING:
                if (ball.speedX == 0 && ball.speedY == 0) {
                    ballLaunch(&ball);
                }

                calculatePaddles(&p1, &p2, 1);

                calculateBallNextStep(&ball);

                BeginDrawing();
                ClearBackground(BLACK);

                DrawBackground();
                DrawPaddles(&p1, &p2, RAYWHITE);
                DrawBall(&ball, RAYWHITE);
                EndDrawing();

                // ball increases speed on every bounce ??
                // when ball hits x 0 or x SWIDTH update score
                // round = WAIT
                // discount live or point (ft10?)

                break;
            case END:

                // one player lost all lives
                // declare winer, clear window, display winner
                // closes game and starts again

                break;
        }

        // calculatePaddles(&p1, &p2, 1);

        // DrawRectangle(0, 0, SWIDTH, TOP, GRAY);
        // DrawRectangle(0, BOTTOM, SWIDTH, BOTTOM, GRAY);
        // DrawLine(SWIDTH / 2, 0, SWIDTH / 2, SHEIGHT, GRAY);

        i += 1;
    }

    CloseWindow();
}
