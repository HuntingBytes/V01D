#include "utils.h"

//Player
Player player;

//Common Resources
Font font;
Texture2D player_textures[2];

//Game Variables
const int screenWidth = 640;
const int screenHeight = 480;
Level currentLevel;
bool game_running;
float last_frame;
Camera2D camera;

//Initialization
bool init(void);
bool loadCommonResources(void);
void setPlayer(void);
void startLevel();

//Update
void update(void);
void physicsUpdate(void);
void inputHandler(void);
void render(void);

//Cleaning
void close(void);

int main() {
    if(!init() || !loadCommonResources()) return  -1;

    setPlayer();

    while (game_running)
    {
        startLevel();
        last_frame = GetFrameTime();
        inputHandler();
        update();
        physicsUpdate();
        render();
    }

    close();
    return 0;
}

bool loadCommonResources() {
    font = LoadFont(FONT_DIR"/Unipix.ttf");
    player_textures[0] = LoadTexture(PLAYER_DIR"/Dude_Monster_Attack1_4.png");
    player_textures[1] = LoadTexture(PLAYER_DIR"/Dude_Monster_Idle_4.png");

    if(font.chars == NULL) return  false;
    if(player_textures[0].width == 0) return  false;
    if(player_textures[1].width == 0) return  false;

    return true;

}

void setPlayer() {
    player.health = MAX_HEALTH;
    player.position.x = player.position.y = 80;
    player.texture = &player_textures[0];
    player.src_rect.height = player.src_rect.width = (float) player.texture->height;
    player.src_rect.x = player.src_rect.y = 0;
    player.idle = true;
    player.jumping = player.walking = false;
}

bool init() {
    InitWindow(screenWidth, screenHeight, "Game Name");
    SetTargetFPS(60);
    game_running = true;
    currentLevel = LEVEL2;
    return IsWindowReady();
}

void startLevel() {
    switch (currentLevel) {
        case LEVEL1: break;
        case LEVEL2: startLevel2(); break;
        default: break;
    }
}

void update() {
    switch (currentLevel) {
        case LEVEL1: break;
        case LEVEL2: updateLevel2(); break;
        default: break;
    }
}

void physicsUpdate() {
    switch (currentLevel) {
        case LEVEL1: break;
        case LEVEL2: physicsUpdateLevel2(); break;
        default: break;
    }
}

void inputHandler() {
    game_running = !WindowShouldClose();
    switch (currentLevel) {
        case LEVEL1: break;
        case LEVEL2: inputHandlerLevel2(); break;
        default: break;
    }
}

void close() {
    game_running = 0;
    player.position.x = 0;
    player.position.y = 0;
    player.health = MAX_HEALTH;
    CloseWindow();
}

void render() {
    switch (currentLevel) {
        case LEVEL1: break;
        case LEVEL2: renderLevel2(); break;
        default: break;
    }
}