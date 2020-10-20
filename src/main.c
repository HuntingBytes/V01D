#include "raylib.h"
#include "level3_phase1.h"

#define NUM_PLAYER_TEXTURES 5

const int screenWidth = 640;
const int screenHeight = 480;

Player player;

Texture2D playerTextures[NUM_PLAYER_TEXTURES];
Animation playerAnimations[NUM_PLAYER_TEXTURES];
Texture2D bullet;
Texture2D tile;
Camera2D camera;

int game_running = 1;

bool init(void);
bool loadAssets(void);
void update(void);
void inputHandler(void);
void close(void);

int main() {
    if(!init()) return  -1;
   /* random();
    loadTextures();
    loadAssets();
    initPieces();
    */
    loadAssets();
    initPlayer();
    initLevel();
   while (game_running)
    {
        inputHandler();
        update();
    }

    close();
    return 0;
}

bool init() {
    InitWindow(screenWidth, screenHeight, "Teste");
    SetTargetFPS(60);
    return IsWindowReady();
}

void close() {
    CloseWindow();
}