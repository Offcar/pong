#include "raylib.h"
#include "stdlib.h"
#include "stdio.h"
 
int main (int argc, char** arvg) {
    int screenWidth = 800;
    int screenHeigth = 500;

    int paddleXOffset = 10;
    int paddleLenght = 100;
    int paddleWidth = 20;

    int stageYLimit = 30;

    int centerScreenWidth = 0;

    int i = 0;

    InitWindow(screenWidth, screenHeigth, "Pong - Raylib/C implementation");

    // Loading a png of the title screen
    /* Image titleScreen = LoadImage("./resources/titleScreen.png"); */
    /* Texture2D texture = LoadTextureFromImage(titleScreen); */
    /* UnloadImage(titleScreen); */

    SetTargetFPS(30);
    while(!WindowShouldClose()) {
        BeginDrawing();

        DrawRectangle(0,0,screenWidth,stageYLimit,RAYWHITE);
        ClearBackground(BLACK);
        /* DrawRectangle(0,screenHeigth - (), screenWidth,stageYLimit,RAYWHITE); */

        // Paddles
        DrawRectangle(i + paddleXOffset,0,paddleWidth,paddleLenght,RAYWHITE);
        DrawRectangle(screenWidth - (paddleWidth + paddleXOffset) ,0,paddleWidth,paddleLenght,RAYWHITE);

        EndDrawing();

        i += 10;
    }

    /* UnloadTexture(texture); */
    CloseWindow();
}

