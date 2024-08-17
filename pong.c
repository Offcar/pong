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
    int height;
    int width;
    int speedX;
    int speedY;
    int bounces;
} Ball;

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
#define MAXBOUNCES 25

// BALL FUNCTIONS
void ballReset(Ball *ball) {
    ball->x = SWIDTH / 2 - (int)ball->width / 2;
    ball->y = SHEIGHT / 2 - (int)ball->height / 2;
    ball->speedX = 0;  // BALLSPEED;
    ball->speedY = 0;
    ball->bounces = 0;
}

void ballLaunch(Ball *ball) {
    int randX = GetRandomValue(0, 1);
    int randY = GetRandomValue(0, 1);

    if (randX == 1) {
        ball->speedX = BALLSPEED;
    } else {
        ball->speedX = -BALLSPEED;
    }

    if (randY == 1) {
        ball->speedY = BALLSPEED;
    } else {
        ball->speedY = -BALLSPEED;
    }
}

int ballCollisionCheck(Ball *b, Paddle *p1, Paddle *p2) {
    int nextY = b->y + b->speedY;
    int nextY2 = b->y + b->speedY + b->height;

    if (b->speedY < 0 && nextY < TOP) {  // UP
        b->speedY *= -1;
    } else if (b->speedY > 0 && nextY2 > BOTTOM) {  // DOWN
        b->speedY *= -1;
    }

    // DEBUGGIN: REBOTE EN EJES X
    if(b->x < 0 || b->x + b->width > SWIDTH) {
        return 1;
    }

    if(b->speedX > 0) {
        // Check de player 2
        if(
            p2->x < b->x + b->width
            && p2->x + p2->width > b->x
            && p2->y < b->y + b->height
            && p2->y + p2->height >= b->y
        ) {
            if(GetRandomValue(0, 5) == 0) {
                b->speedY *= -1;
            }

            b->speedX *= -1;
        }
        
    } else if(b->speedX < 0) {
        // Check de player 1
        if(
            p1->x < b->x + b->width
            && p1->x + p1->width > b->x
            && p1->y < b->y + b->height
            && p1->y + p1->height >= b->y
        ) {
            if(GetRandomValue(0, 5) == 0) {
                b->speedY *= -1;
            }
            b->speedX *= -1;
        }
    }

    return 0;
}

void ballUpdatePos(Ball *b) {
    b->x += b->speedX;
    b->y += b->speedY;
}

// PADDLE FUNCTIONS
void paddlePlayerUpdate(Paddle *p, KeyboardKey up, KeyboardKey down) {
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

void paddleReset(Paddle *p1, Paddle *p2) {
    p1->x = 30;
    p1->y = SHEIGHT / 2 - 50;

    p2->x = SWIDTH - (p1->x + p1->width);
    p2->y = p1->y;
}

void paddlesUpdate(Paddle *p1, Paddle *p2, int isPlayer2Enabled) {
    paddlePlayerUpdate(p1, KEY_W, KEY_S);

    if (isPlayer2Enabled == 1) {
        paddlePlayerUpdate(p2, KEY_UP, KEY_DOWN);
    } else {
        calculateCPU(p2);
    }
}

// Draw functions
void DrawPlayableElements(Paddle *p1, Paddle *p2, Ball *b, Color color) {
    DrawRectangle(p1->x, p1->y, p1->width, p1->height, color);
    DrawRectangle(p2->x, p2->y, p2->width, p2->height, color);
    DrawRectangle(b->x, b->y, b->width, b->height, color);
}

void DrawBackground() {
    DrawRectangle(0, 0, SWIDTH, TOP, GRAY);
    DrawRectangle(0, BOTTOM, SWIDTH, BOTTOM, GRAY);
    DrawLine(SWIDTH / 2, 0, SWIDTH / 2, SHEIGHT, GRAY);
}

int main(int argc, char **arvg) {
    Paddle p1 = {30, SHEIGHT / 2 - 50, 30, 100, 20};
    Paddle p2 = {SWIDTH - (p1.x + p1.width), p1.y, 30, 100, 20};
    Ball ball = {SWIDTH / 2, SHEIGHT / 2, 15, 15, 0, 0};

    int ballStatus = 0;

    ROUNDSTATUS round = WAIT;

    InitWindow(SWIDTH, SHEIGHT, "Pong - Raylib/C implementation");

    SetTargetFPS(30);
    while (!WindowShouldClose()) {

        switch (round) {
            case WAIT:
                BeginDrawing();
                ClearBackground(BLACK);

                DrawBackground();
                DrawPlayableElements(&p1, &p2, &ball, GRAY);

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

                paddlesUpdate(&p1, &p2, 1);
                ballStatus = ballCollisionCheck(&ball, &p1, &p2);
                ballUpdatePos(&ball);
                
                BeginDrawing();
                ClearBackground(BLACK);

                DrawBackground();
                DrawPlayableElements(&p1, &p2, &ball, RAYWHITE);
                EndDrawing();

                if(ballStatus == 1) { // Ball reset
                    ballReset(&ball);
                    paddleReset(&p1, &p2);
                    round = WAIT;
                    ballStatus = 0;
                }
                break;
            case END:
                break;
        }
    }

    CloseWindow();
}
