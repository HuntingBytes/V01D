#include "raylib.h"
#include <stdio.h>

typedef enum {MENU = 0, LEVEL1, LEVEL2, LEVEL3, ENDING} Level;
#define FPS 60

const int screenWidth = 640;
const int screenHeight = 480;

Level currentLevel = MENU;

bool game_running = true;

//Funções para cada uma das Fases
void mainMenu(void);
void mainLevel1(void);
void mainLevel2(void);
void mainLevel3(void);
void mainEnding(void);
void levelTransition(void);
//-------------------------------

//Funções Gerais
bool init(void);

int main() {
    if(!init()) return -1;
    while (game_running) {
            /*
            switch (currentLevel) {
                case MENU:
                    mainMenu();
                    break;
                case LEVEL1:
                    mainLevel1();
                    break;
                case LEVEL2:
                    mainLevel2();
                    break;
                case LEVEL3:
                    mainLevel3();
                    break;
                case ENDING:
                    mainEnding();
                    break;
                default:
                    break;
            }
             */
    }
    return 0;
}

bool init() {
    InitWindow(screenWidth, screenHeight, "Teste");
    SetTargetFPS(FPS);
    game_running = true;
    currentLevel = MENU;
    return IsWindowReady();
}