#include "raylib.h"
#include "raymath.h"
#include "stdlib.h"
#include "stdio.h"

typedef enum GAMESTATE {
    MAIN_MENU = 1,
    RUNNING = 2,
    PAUSE = 3,
    STOP = 0
} GAMESTATE;

void clearBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c !=EOF) {}
}

int main (int argc, char** arvg) {
    GAMESTATE gameState = RUNNING;


    int input;

    while(gameState == RUNNING) {
        printf("Probando cambiar el estado de un enum con un valor puntal.\n");
        printf("Escribir '69420' para cambiar el estado de RUNNING a STOP.\n");
        printf("input: ");

        scanf("%5d", &input);
        clearBuffer();

        if (input == 69420) {
            gameState = STOP;
        }
    }
}

