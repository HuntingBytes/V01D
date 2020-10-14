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
Camera2D camera;

//Initialization
bool init(void); //Create Window; Set currentLevel; Game is now running;
bool loadCommonResources(void); //Resources available at all time
void startLevel(void); //Start a level once
void initializePlayer(void); //Initialize Player

//Update
void inputHandler(void);
void update(void); //Simulate World
void physicsUpdate(void); //Collision Detection and Correction
void render(void); //Show frame on Screen

//Cleaning
void close(void); //Finish game

int main() {
    if(!init() || !loadCommonResources()) return  -1; //If is not possible to create window or load common resources, exit.

    initializePlayer(); //Set initial player values, not related to any level

    while (game_running)
    {
        startLevel(); //Start current level, make sure that it runs only once (due to dynamic allocation)
        inputHandler(); //Gather input data and change variables (booleans, set speed, etc)
        update(); //Simulate World, Move Player, Move Camera, Moves Animation forward...
        physicsUpdate(); //Deal with any collisions between objects, correcting and detecting
        //postUpdate() or ObjectUpdate(), deal with interactions
        render(); //Draw the frame
    }

    close(); //Finish the game. Unload Textures, set default values
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

void initializePlayer() {
    setPlayerHealth(&player, MAX_HEALTH);
    setPlayerPosition(&player, (Vector2){0, 0});
    setPlayerTexture(&player, &player_textures[0]);
    setPlayerVelocity(&player, (Vector2){0, 0});
    player.idle = true;
    player.walking = false;
    player.jumping = false;
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
    setPlayerHealth(&player, MAX_HEALTH);
    setPlayerPosition(&player, (Vector2){0, 0});
    UnloadFont(font);
    UnloadTexture(player_textures[0]);
    UnloadTexture(player_textures[1]);
    CloseWindow();
}

void render() {
    switch (currentLevel) {
        case LEVEL1: break;
        case LEVEL2: renderLevel2(); break;
        default: break;
    }
}