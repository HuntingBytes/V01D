#include "raylib.h"
#include <stdio.h>

typedef enum {MENU = 0, LEVEL1, LEVEL2, LEVEL3, ENDING} Level;
#define FPS 60
#define TEXT_SPEED 10

const int screenWidth = 640;
const int screenHeight = 480;

Level currentLevel = MENU;

bool game_running = true;
bool transition = true;

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
        if(!transition) {
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
            printf("Finalizado\n");
            fflush(stdout);
        } else {
            levelTransition();
        }
    }
    return 0;
}

bool init() {
    InitWindow(screenWidth, screenHeight, "Teste");
    SetTargetFPS(FPS);
    game_running = true;
    transition = true;
    frame_counter = 0;
    currentLevel = MENU;
    return IsWindowReady();
}

void levelTransition() {
    static int frame_counter = 0;
    static char txt[4][50] = {"Prologo", "Ato 1 - Onde?", "Ato 2 - O que?", "Ato 3 - Fim?"};
    BeginDrawing();
    ClearBackground(BLACK);
    frame_counter++;
    DrawText(TextSubtext(txt[currentLevel], 0, frame_counter/TEXT_SPEED), (screenWidth - MeasureText(txt[currentLevel], 32))/2, (screenHeight - MeasureText("A", 32))/2, 32, WHITE);
    if(frame_counter/TEXT_SPEED > TextLength(txt[currentLevel]) + 10u) {
        frame_counter = 0;
        transition = false;
    }
    EndDrawing();
}