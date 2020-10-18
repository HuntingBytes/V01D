#include "utils.h"

#define NUMBER_PLAYER_TEXTURES 5

//Player
Player player;
//-------------

//Common Resources
Font font;
Texture2D player_textures[NUMBER_PLAYER_TEXTURES];
Animation player_animations[NUMBER_PLAYER_TEXTURES];
Texture2D bullet_texture;
//---------------------------

//Game Variables
const int screenWidth = 640;
const int screenHeight = 480;
float deltaTime;
Level currentLevel;
bool game_running;
Camera2D camera;
//---------------------------

//Initialization
bool init(void); //Create Window; Set currentLevel; Game is now running;
bool loadCommonResources(void); //Resources available at all time
void startLevel(void); //Start a level once
void initializePlayer(void); //Initialize Player
//------------------------------------------------------------------------

//Update
void inputHandler(void);
void update(void); //Simulate World
void physicsUpdate(void); //Collision Detection and Correction
void render(void); //Show frame on Screen
void clearLevel(void); //Clear level
//---------------------------------------------------------------

//Cleaning
void close(void); //Finish game
//-------------------------------

int main() {
    if(!init() || !loadCommonResources()) return  -1; //If is not possible to create window or load common resources, exit.

    initializePlayer(); //Set initial player values, not related to any level

    while (game_running)
    {
        deltaTime = GetFrameTime();
        startLevel(); //Start current level, make sure that it runs only once (due to dynamic allocation)
        inputHandler(); //Gather input data and change variables (booleans, set speed, etc)
        update(); //Simulate World, Move Player, Move Camera, Moves Animation forward...
        physicsUpdate(); //Deal with any collisions between objects, correcting and detecting
        //postUpdate() or ObjectUpdate(), deal with interactions
        render(); //Draw the frame
        clearLevel();
    }

    close(); //Finish the game. Unload Textures, set default values
    return 0;
}

bool init() {
    InitWindow(screenWidth, screenHeight, "Game Name");
    SetTargetFPS(FPS);
    game_running = true;
    currentLevel = LEVEL2;
    camera.target = (Vector2) {0,0};
    camera.offset = (Vector2) {0,0};
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
    return IsWindowReady();
}

bool loadCommonResources() {
    font = LoadFont(FONT_DIR"/Unipix.ttf");

    player_textures[IDLE] = LoadTexture(PLAYER_DIR"/idle.png");
    player_textures[WALK] = LoadTexture(PLAYER_DIR"/walk.png");
    player_textures[JUMP] = LoadTexture(PLAYER_DIR"/jump.png");
    player_textures[CLIMB] = LoadTexture(PLAYER_DIR"/climb.png");
    player_textures[DIE] = LoadTexture(PLAYER_DIR"/death.png");
    bullet_texture = LoadTexture(PLAYER_DIR"/bullet.png");

    if(font.texture.id <= 0) return  false;
    if(bullet_texture.id <= 0) return false;
    for(int i = IDLE; i < NUMBER_PLAYER_TEXTURES; i++) {
        if(player_textures[i].id <= 0) {return false;}
        loadAnimation(&player_textures[i], &player_animations[i], i);
    }

    return true;
}

void initializePlayer() {
    setPlayerHealth(&player, MAX_HEALTH);
    setPlayerPosition(&player, (Vector2){0, 0});
    setPlayerTexture(&player, &player_textures[IDLE], &player_animations[IDLE]);
    setPlayerVelocity(&player, (Vector2){0, 0});

    setBulletDamage(&player.bullet, 1);
    setBulletDistance(&player.bullet, 400.0f);
    setBulletPosition(&player.bullet, (Vector2){0,0});
    setBulletTexture(&player.bullet, &bullet_texture);
    setBulletVelocity(&player.bullet, (Vector2){5.0f,0.0f});

    player.idle = true;
    player.walking = false;
    player.jumping = false;
    player.onGround = false;
    player.bullet.active = false;
    player.dir = 1;
}

void startLevel() {
    switch (currentLevel) {
        case LEVEL1: break;
        case LEVEL2: startLevel2(); break;
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

void render() {
    BeginDrawing();
    BeginMode2D(camera);
    switch (currentLevel) {
        case LEVEL1: break;
        case LEVEL2: renderLevel2(); break;
        default: break;
    }
    EndMode2D();
    EndDrawing();
}

void clearLevel() {
    if(!game_running) {
        switch (currentLevel) {
            case LEVEL1: break;
            case LEVEL2: clearLevel2(); break;
            default: break;
        }
    }
}

void close() {
    UnloadFont(font);
    UnloadTexture(bullet_texture);
    for(int i = 0; i < NUMBER_PLAYER_TEXTURES; i++) { UnloadTexture(player_textures[i]); }
    CloseWindow();
}