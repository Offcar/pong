#include "raylib.h"
#include "stdio.h"


void checkUserInput(Vector2 *p1, Vector2 *p2, int pSpeed, int pLenght, int isPlayer2Enabled);

void ballSpeedUp(Vector4 *ball, int xspeedValue, int yspeedValue);

void ballUpdate(Vector4 *ball);

void ballBounceCheck(Vector4 *ball);

void roundStart();

#define SWIDTH 800
#define SHEIGHT 500
#define TOP 30
#define BOTTOM SHEIGHT - TOP


int main (int argc, char** arvg) {
    int pStartX = 10;
    int pLenght = 100;
    int pWidth = 20;
    int pSpeed = 30;

    int p2Enabled = 1;

    int borderTop = 30;
    int borderBottom = SHEIGHT - borderTop;

    InitWindow(SWIDTH, SHEIGHT, "Pong - Raylib/C implementation");

    Vector2 p1 = {(float) pStartX, (float) SHEIGHT/2 - (float) pLenght/2};
    Vector2 p2 = {(float) SWIDTH - (pStartX + pWidth), (float) SHEIGHT/2 - (float) pLenght/2};
    Vector4 ball = {(float) SWIDTH/2 , (float) SHEIGHT/2, (float) 10, (float) 10};

    SetTargetFPS(20);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        //BorderLimits
        DrawRectangle(0, 0, SWIDTH, borderTop, GRAY);
        DrawRectangle(0, borderBottom, SWIDTH, borderBottom, GRAY);

        //Center screen split
        DrawLine(SWIDTH/2, 0, SWIDTH/2, SHEIGHT,GRAY);

        //Ball
        ballUpdate(&ball);
        DrawCircle(ball.x, ball.y, 10, RAYWHITE);

        // Paddles
        checkUserInput(&p1, &p2, pSpeed, pLenght, p2Enabled);
        DrawRectangle(p1.x ,p1.y, pWidth, pLenght, RAYWHITE);
        DrawRectangle(p2.x ,p2.y, pWidth, pLenght, RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
}



void checkUserInput(Vector2 *p1, Vector2 *p2, int pSpeed, int pLength, int isPlayer2Enabled) {
    // Player 1 update
    if (IsKeyDown(KEY_W)) {
        if(p1->y - pSpeed <= TOP) {
            p1->y = TOP;
        } else {
            p1->y -= pSpeed;
        }
    }

    if (IsKeyDown(KEY_S)) {
        if(p1->y + pSpeed + pLength >= BOTTOM) {
            p1->y = BOTTOM - pLength;
        } else {
            p1->y += pSpeed;
        }
    }


    // Player 2
    if(isPlayer2Enabled == 1) {

        if (IsKeyDown(KEY_UP)) {
            if(p2->y - pSpeed <= TOP) {
                p2->y = TOP;
            } else {
                p2->y -= pSpeed;
            }
        }

        if (IsKeyDown(KEY_DOWN)) {
            if(p2->y + pSpeed + pLength >= BOTTOM) {
                p2->y = BOTTOM - pLength;
            } else {
                p2->y += pSpeed;
            }
        }
    }
}

void ballUpdate(Vector4 *ball) {
    ball->x += ball->z;
    ball->y += ball->w;
}
