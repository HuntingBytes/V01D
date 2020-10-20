#include "includes/utils.h"
#include "includes/animation.h"
#include "includes/player.h"
#include "includes/bullet.h"

#define NUMBER_PLAYER_TEXTURES 5

//Variáveis do Jogo----------
const int screenWidth = 640;
const int screenHeight = 480;
Level currentLevel;
bool game_running;
//--------------------------

//Variáveis Globais----
Player player;
Camera2D camera;
Font font;
//---------------------

//Assets comuns ---------------------------------
Texture2D player_textures[NUMBER_PLAYER_TEXTURES];
Animation player_animations[NUMBER_PLAYER_TEXTURES];
Texture2D bullet_texture;
//------------------------------------------------

//Funções Gerais
bool init(void);
bool loadCommonResources(void);
void initializePlayer(void);
void close(void);
//---------------

int main() {
    if(!init() || !loadCommonResources()) return -1;

    initializePlayer();

    while (game_running) {
            switch (currentLevel) {
                case MENU:
                    //mainMenu();
                    break;
                case LEVEL1:
                    //mainLevel1();
                    break;
                case LEVEL2:
                    mainLevel2();
                    break;
                case LEVEL3:
                    //mainLevel3();
                    break;
                case ENDING:
                    //mainEnding();
                    break;
                default:
                    break;
            }
    }

    close();

    return 0;
}

bool init() {
    InitWindow(screenWidth, screenHeight, "Teste");
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
    player.climbing = false;
    player.onGround = false;
    player.bullet.active = false;
    player.dir = 1;
}

void close() {
    UnloadFont(font);
    UnloadTexture(bullet_texture);
    for(int i = 0; i < NUMBER_PLAYER_TEXTURES; i++) { UnloadTexture(player_textures[i]); }
    CloseWindow();
}