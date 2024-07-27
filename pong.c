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

void ballLaunch(Ball *ball, int speedX, int speedY) {
    if (GetRandomValue(0, 1) == 1) {
        ball->speedX = speedX;
        ball->speedY = speedY;
    } else {
        ball->speedX = -speedX;
        ball->speedY = -speedY;
    }
}

void ballReset(Ball *ball) {
    ball->x = SHEIGHT / 2;
    ball->y = SWIDTH / 2;
    ball->speedX = 0;
    ball->speedY = 0;
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
    DrawCircle(b->x, b->y, b->radius, color);
}

void calculateBallNextStep(Ball *b) {
    int nextStepX = b->x + b->speedX + (int)b->radius / 2;
    int nextStepY = b->y + b->speedY + (int)b->radius / 2;
    // check bounce
    // if bounce, speed up ball
    // if bounce, check angle

    // check collision on either side of the screen
    if (b->speedX > 0) {
    } else {
    }

    if (nextStepY <= TOP || nextStepY >= BOTTOM) {
        b->speedY *= -1;
    }

    if (nextStepX <= 0 || nextStepX >= SWIDTH + (int)b->radius) {
        b->speedX *= -1;
    }


    b->x += b->speedX;
    b->y += b->speedY;
}

int main(int argc, char **arvg) {
    Paddle p1 = {30, SHEIGHT / 2 - 50, 30, 100, 20};
    Paddle p2 = {SWIDTH - (p1.x + p1.width), p1.y, 30, 100, 20};
    Ball ball = {SWIDTH / 2, SHEIGHT / 2, 10, 25, 25};

    ROUNDSTATUS round = WAIT;

    InitWindow(SWIDTH, SHEIGHT, "Pong - Raylib/C implementation");

    SetTargetFPS(20);
    while (!WindowShouldClose()) {
        switch (round) {
            case WAIT:
                paddleReset(&p1, &p2);

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
                    ballLaunch(&ball, 1, 1);
                }

                calculatePaddles(&p1, &p2, 1);

                // check collision

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
    }

    CloseWindow();
}
