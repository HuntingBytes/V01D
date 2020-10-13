//Moesiof
#include "raylib.h"

//hell yeah now we have business!

const int screenWidth = 640;
const int screenHeight = 480;

Texture2D player_asset;
Texture2D tile;

int game_running = 1;


bool init(void);
bool loadAssets(void);
void update(void);
void inputHandler(void);
void close(void);

int main() {
    if(!init()) return  -1; 
    loadAssets();

    while (game_running)
    {
        inputHandler();
        update();
    }

    close();
    return 0;
}

bool loadAssets() {
    player_asset = LoadTexture("assets/player/Dude_Monster_Attack1_4.png");
    player_asset.height = (int)(player_asset.height*1.5);
    player_asset.width = (int)(player_asset.width*1.5);
    tile = LoadTexture("assets/maps/level2/phase1/final.png");
    return  true;
}

bool init() {
    InitWindow(screenWidth, screenHeight, "Teste");
    SetTargetFPS(60);
    return IsWindowReady();
}

void update() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawTexture(tile, 0, 0, WHITE);
    DrawTexture(player_asset, 10, 145, WHITE);
    EndDrawing();
}

void inputHandler() {
    if(WindowShouldClose()) game_running = 0;
}

void close() {
    CloseWindow();
}