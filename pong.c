#include "raylib.h"
#include "raymath.h"
#include "stdlib.h"
#include "stdio.h"


int main (int argc, char** arvg) {

    int screenWidth = 1200;
    int screenHeigth = 800;

    InitWindow(screenWidth, screenHeigth, "Pong - Raylib/C implementation");

    // Loading a png of the title screen
    Image titleScreen = LoadImage("./resources/titleScreen.png");
    Texture2D texture = LoadTextureFromImage(titleScreen);

    UnloadImage(titleScreen);

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTexture(texture, 0, 0, RAYWHITE);

        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
}

