#include "level3_phase1.h"

extern const int screenWidth;
extern const int screenHeight;
extern Player player;
extern int game_running;
extern Texture2D tile;
extern Texture2D playerTextures[];
extern Camera2D camera;
static Collider2D *colliders;

void level3 (){
    initPlayer();

}

void initLevel(){
    camera.target = (Vector2) {0,0};
    camera.offset = (Vector2) {0,0};
    camera.zoom = 1.5f;
    camera.rotation = 0.0f;

    colliders = (Collider2D*) malloc(15 * sizeof(Collider2D));

    //Starting ground
    colliders[0].colliderType = GROUND;
    colliders[0].collider.x = 0.0f;
    colliders[0].collider.height = BLOCK_SIZE/3.1;
    colliders[0].collider.y = 193;
    colliders[0].collider.width = BLOCK_SIZE*1.9;
    //Ladder
    colliders[1].colliderType = TRIGGER_LADDER;
    colliders[1].collider.x = 92;
    colliders[1].collider.height = (float)BLOCK_SIZE * 2.1f;
    colliders[1].collider.y = 189;
    colliders[1].collider.width = (float)BLOCK_SIZE * 0.5f;
    //Ground under platforms
    colliders[2].colliderType = GROUND;
    colliders[2].collider.x = 93;
    colliders[2].collider.height = BLOCK_SIZE/3.1;
    colliders[2].collider.y = 289;
    colliders[2].collider.width = (float)BLOCK_SIZE * 6.8f;
    //Wall left to the ladder
    colliders[3].colliderType = WALL;
    colliders[3].collider.x = 82;
    colliders[3].collider.height = (float) BLOCK_SIZE * 1.7f;
    colliders[3].collider.y = 208;
    colliders[3].collider.width =  BLOCK_SIZE / 5.0;
    //First platform (left to right)
    colliders[4].colliderType = PLATFORM;
    colliders[4].collider.x = 143;
    colliders[4].collider.height = BLOCK_SIZE / 3.1;
    colliders[4].collider.y = 184;
    colliders[4].collider.width = (float)BLOCK_SIZE;
    //Second platform (left to right)
    colliders[5].colliderType = PLATFORM;
    colliders[5].collider.x = 223;
    colliders[5].collider.height = BLOCK_SIZE / 3.1;
    colliders[5].collider.y = 155;
    colliders[5].collider.width = (float)BLOCK_SIZE;
    //Third platform (left to right)
    colliders[6].colliderType = PLATFORM;
    colliders[6].collider.x = 285;
    colliders[6].collider.height = BLOCK_SIZE / 3.1;
    colliders[6].collider.y = 210;
    colliders[6].collider.width = (float)BLOCK_SIZE;
    //Fourth platform (left to right)
    colliders[7].colliderType = PLATFORM;
    colliders[7].collider.x = 344;
    colliders[7].collider.height = BLOCK_SIZE / 3.1;
    colliders[7].collider.y = 174;
    colliders[7].collider.width = (float)BLOCK_SIZE;
    //Wall right to ladder
    colliders[8].colliderType = WALL;
    colliders[8].collider.x = 417;
    colliders[8].collider.height = (float)BLOCK_SIZE * 2.7f;
    colliders[8].collider.y = 172;
    colliders[8].collider.width = BLOCK_SIZE / 3.0;
    //Ground on top of last wall
    colliders[9].colliderType = GROUND;
    colliders[9].collider.x = 415;
    colliders[9].collider.height = 4;
    colliders[9].collider.y = 168;
    colliders[9].collider.width = BLOCK_SIZE / 2.4;
    //Right wall
    colliders[10].colliderType = WALL;
    colliders[10].collider.x = 592;
    colliders[10].collider.height = (float)BLOCK_SIZE * 6.0f;
    colliders[10].collider.y = 145;
    colliders[10].collider.width = BLOCK_SIZE / 3.0;
    //Lower ground
    colliders[11].colliderType = GROUND;
    colliders[11].collider.x = 0.0f;
    colliders[11].collider.height = (float) BLOCK_SIZE;
    colliders[11].collider.y = (float)screenHeight - colliders[11].collider.height;
    colliders[11].collider.width = (float)BLOCK_SIZE * 12.4f;
    //Right spikes
    colliders[12].colliderType = TRIGGER_SPIKE;
    colliders[12].collider.x = 361;
    colliders[12].collider.height = BLOCK_SIZE / 3.1;
    colliders[12].collider.y = 418;
    colliders[12].collider.width = (float)BLOCK_SIZE;
    //Left spikes
    colliders[13].colliderType = TRIGGER_SPIKE;
    colliders[13].collider.x = 223;
    colliders[13].collider.height = BLOCK_SIZE / 3.1;
    colliders[13].collider.y = 418;
    colliders[13].collider.width = (float)BLOCK_SIZE;
    //Door (triggers puzzle)
    colliders[14].colliderType = TRIGGER_DOOR;
    colliders[14].collider.x = 0;
    colliders[14].collider.height = (float)BLOCK_SIZE * 2.0f;
    colliders[14].collider.y = 336;
    colliders[14].collider.width = (float)BLOCK_SIZE * 2.0f;
}

void initPlayer(){
    player.idle = true;
    player.onGround = false;
    player.walking = false;
    player.jumping = false;
    player.health = MAX_HEALTH;
    player.dir = 1;
    player.position = (Vector2) {0,0};
    player.velocity = (Vector2) {0, 0};

}

void inputHandler(){
    if(WindowShouldClose()){
        game_running = 0;
        return;
    }

    if(IsKeyDown(KEY_A)){
        player.velocity.x = -3.0f;
    }
    if(IsKeyDown(KEY_D)){
        player.velocity.x = 3.0f;
    }
    if((IsKeyDown(KEY_A) && IsKeyDown(KEY_D)) || (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))){
        player.velocity.x = 0;
        player.walking = false;
    }else{
        player.idle = false;
        if(!player.walking && !player.jumping){
            player.walking = true;
        }

    }

    if(IsKeyDown(KEY_SPACE)){
        player.velocity.y = -3.0f;
    }
    if(IsKeyDown(KEY_S)){
        player.velocity.y = 3.0f;
    }
    if((IsKeyDown(KEY_S) && IsKeyDown(KEY_SPACE)) || (!IsKeyDown(KEY_S) && !IsKeyDown(KEY_SPACE))){
        player.velocity.y = 0;
        player.jumping = false;
        if(!player.walking && !player.idle){
            player.jumping = true;
            player.onGround = false;
        }
    }
    playerPos(&player);
}

void playerPos(Player *player){
    player -> position.x += player -> velocity.x;
    player -> position.y += player -> velocity.y;
}

void update() {
    //UpdatePlayerCamera(&camera, &player, (float) tile.width);

    BeginDrawing();
    //BeginMode2D(camera);

    ClearBackground(WHITE);
    DrawTexture(tile, 0, 0, WHITE);
    DrawTexture(playerTextures[IDLE], player.position.x, player.position.y, WHITE);
    DrawRectangleLinesEx(colliders[0].collider, 2, LIME);
    DrawRectangleLinesEx(colliders[1].collider, 2, MAGENTA);
    DrawRectangleLinesEx(colliders[2].collider, 2, LIME);
    DrawRectangleLinesEx(colliders[3].collider, 2, LIME);
    DrawRectangleLinesEx(colliders[4].collider, 2, LIME);
    DrawRectangleLinesEx(colliders[5].collider, 2, LIME);
    DrawRectangleLinesEx(colliders[6].collider, 2, LIME);
    DrawRectangleLinesEx(colliders[7].collider, 2, LIME);
    DrawRectangleLinesEx(colliders[8].collider, 2, LIME);
    DrawRectangleLinesEx(colliders[9].collider, 2, DARKGREEN);
    DrawRectangleLinesEx(colliders[10].collider, 2, LIME);
    DrawRectangleLinesEx(colliders[11].collider, 2, LIME);
    DrawRectangleLinesEx(colliders[12].collider, 2, RED);
    DrawRectangleLinesEx(colliders[13].collider, 2, RED);
    DrawRectangleLinesEx(colliders[14].collider, 2, GOLD);
    //callPuzzle();
    //complete();

    //EndMode2D();
    EndDrawing();
}



bool loadAssets() {

    playerTextures[IDLE] = LoadTexture(PLAYER_DIR"/idle.png");
    playerTextures[WALK] = LoadTexture(PLAYER_DIR"/walk.png");
    playerTextures[JUMP] = LoadTexture(PLAYER_DIR"/jump.png");
    playerTextures[CLIMB] = LoadTexture(PLAYER_DIR"/climb.png");
    playerTextures[DIE] = LoadTexture(PLAYER_DIR"/death.png");

    tile = LoadTexture(MAPS_DIR"/level3/phase1/final.png");

    //virado.height = (int)(virado.height*1.5);
    //virado.width = (int)(virado.width*1.5);

    return  true;
}

void UpdatePlayerCamera(Camera2D *camera, Player *player, float screen_edge) {
    camera->target.x = player->position.x;
    camera->offset = (Vector2) {0.5f*(float)screenWidth, 0};
    clampCameraToLimits(camera, screen_edge);
}

void clampCameraToLimits(Camera2D *camera, float screen_edge) {
    if (camera->target.x - camera->offset.x < 0) {
        camera->target.x = camera->offset.x;
    }

    if ((camera->target.x - camera->offset.x) + (float) screenWidth > screen_edge) {
        camera->target.x = screen_edge - (float) screenWidth + camera->offset.x;
    }
}