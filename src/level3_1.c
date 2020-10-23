#include "includes/level3_1.h"

//Variaveis Externas ------------
extern const int screenWidth;
extern const int screenHeight;
extern Level currentLevel;
extern bool game_running;
extern Player player;
extern Camera2D camera;
extern Font font;
extern Texture2D player_textures[];
extern Animation player_animations[];
extern Texture2D bullet_texture;
//----------------------------------

static Level3_1 *level;

static Rectangle flippedRectangle(Rectangle rect) {
    Rectangle result;
    result.x = rect.x;
    result.y = rect.y;
    result.width = -rect.width;
    result.height = rect.height;
    return  result;
}

static void drawColliders() {
    for(int i = 0; i < *level->colliders_length; i++) {
        DrawRectangleLinesEx(level->colliders[i].collider, 2, RED);
    }
}

void mainLevel3_1() {
    initLevel();

    while (!level->levelFinished) {
        level->deltaTime = GetFrameTime();
        inputHandler();
        update();
        physicsUpdate();
        draw();

    }

    clearLevel();
}

static void initLevel() {
    level = (Level3_1*) malloc(sizeof(Level3_1));

    camera.target = (Vector2) {0, 0};
    camera.offset = (Vector2) {0, 0};
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;

    level->bg = (Texture2D*) malloc(sizeof(Texture2D));
    level->colliders = (Collider2D*) malloc(14*sizeof(Collider2D));
    level->colliders_length = (size_t*) malloc(sizeof(size_t));
    *level->colliders_length = 14;
    *level->bg = LoadTexture(MAPS_DIR"/level3/phase1/final.png");

    //Starting ground
    level->colliders[0].colliderType = GROUND;
    level->colliders[0].collider.x = 0.0f;
    level->colliders[0].collider.height = BLOCK_SIZE / 3.1f;
    level->colliders[0].collider.y = 193.0f;
    level->colliders[0].collider.width = BLOCK_SIZE * 1.9f;
    //Ladder
    level->colliders[1].colliderType = TRIGGER_LADDER;
    level->colliders[1].collider.x = 92.0f;
    level->colliders[1].collider.height = (float)BLOCK_SIZE * 2.1f;
    level->colliders[1].collider.y = 189.0f;
    level->colliders[1].collider.width = (float)BLOCK_SIZE / 3.8f;
    //Ground under platforms
    level->colliders[2].colliderType = GROUND;
    level->colliders[2].collider.x = 93.0f;
    level->colliders[2].collider.height = BLOCK_SIZE / 3.1f;
    level->colliders[2].collider.y = 289.0f;
    level->colliders[2].collider.width = (float)BLOCK_SIZE * 6.8f;
    //Wall left to the ladder
    level->colliders[3].colliderType = WALL;
    level->colliders[3].collider.x = 82.0f;
    level->colliders[3].collider.height = (float) BLOCK_SIZE * 1.7f;
    level->colliders[3].collider.y = 208.0f;
    level->colliders[3].collider.width =  BLOCK_SIZE / 5.0;
    //First platform (left to right)
    level->colliders[4].colliderType = PLATFORM;
    level->colliders[4].collider.x = 143.0f;
    level->colliders[4].collider.height = BLOCK_SIZE / 4.5f;
    level->colliders[4].collider.y = 184.0f;
    level->colliders[4].collider.width = (float)BLOCK_SIZE;
    //Second platform (left to right)
    level->colliders[5].colliderType = PLATFORM;
    level->colliders[5].collider.x = 223.0f;
    level->colliders[5].collider.height = BLOCK_SIZE / 4.5f;
    level->colliders[5].collider.y = 155.0f;
    level->colliders[5].collider.width = (float)BLOCK_SIZE;
    //Third platform (left to right)
    level->colliders[6].colliderType = PLATFORM;
    level->colliders[6].collider.x = 285.0f;
    level->colliders[6].collider.height = BLOCK_SIZE / 9.0f;
    level->colliders[6].collider.y = 210.0f;
    level->colliders[6].collider.width = (float)BLOCK_SIZE;
    //Fourth platform (left to right)
    level->colliders[7].colliderType = PLATFORM;
    level->colliders[7].collider.x = 344.0f;
    level->colliders[7].collider.height = BLOCK_SIZE / 5.0f;
    level->colliders[7].collider.y = 174.0f;
    level->colliders[7].collider.width = (float)BLOCK_SIZE;
    //Wall right to ladder
    level->colliders[8].colliderType = WALL;
    level->colliders[8].collider.x = 417.0f;
    level->colliders[8].collider.height = (float)BLOCK_SIZE * 2.7f;
    level->colliders[8].collider.y = 172.0f;
    level->colliders[8].collider.width = BLOCK_SIZE / 3.2f;
    //Ground on top of last wall
    level->colliders[9].colliderType = GROUND;
    level->colliders[9].collider.x = 418.0f;
    level-> colliders[9].collider.height = 4.0f;
    level->colliders[9].collider.y = 168.0f;
    level->colliders[9].collider.width = BLOCK_SIZE / 2.8f;
    //Right wall
    level->colliders[10].colliderType = WALL;
    level->colliders[10].collider.x = 592.0f;
    level->colliders[10].collider.height = (float)BLOCK_SIZE * 6.0f;
    level->colliders[10].collider.y = 145.0f;
    level->colliders[10].collider.width = BLOCK_SIZE / 3.0f;
    //Lower ground
    level->colliders[11].colliderType = GROUND;
    level->colliders[11].collider.x = 0.0f;
    level->colliders[11].collider.height = (float) BLOCK_SIZE;
    level->colliders[11].collider.y = (float)screenHeight - level->colliders[11].collider.height;
    level->colliders[11].collider.width = (float)BLOCK_SIZE * 12.4f;
    //Chest under platforms
    level->colliders[12].colliderType = TRIGGER_CHEST;
    level->colliders[12].collider.x = 383.0f;
    level->colliders[12].collider.height = BLOCK_SIZE / 4.0f;
    level->colliders[12].collider.y = 276.0f;
    level->colliders[12].collider.width = BLOCK_SIZE / 2.0f;
    //Door (triggers puzzle)
    level->colliders[13].colliderType = TRIGGER_DOOR;
    level->colliders[13].collider.x = 0.0f;
    level->colliders[13].collider.height = (float)BLOCK_SIZE * 2.0f;
    level->colliders[13].collider.y = 336.0f;
    level->colliders[13].collider.width = (float)BLOCK_SIZE * 2.0f;

    setPlayerPosition(&player, (Vector2) {30.0f, 170.0f});
    setShoot(&player);

    player.onGround = false;
    player.jumping = false;
    player.climbing = false;
    player.walking = false;
    player.idle = true;
    player.dir = 1.0f;

    level->current_ground = 0;
    level->isPuzzleOn = false;
    level->isNearChest = false;
    level->ladder_colliding = false;
    level->levelFinished = false;
    level->invert_factor = 1.0f;
    level->frame_counter = 0;

    //Sobrescrevendo o a largura do colisor
    player.collider_rect.width /= 1.5f;

    allocatePuzzle();
    random();
    loadTextures();
    initPieces();
}

static void inputHandler(){
    if(WindowShouldClose()) {
        level->levelFinished = true;
        game_running = false;
    }

    //Store current player velocity
    float vel_x = player.velocity.x;
    float vel_y = player.velocity.y;

    //Store current key states (Array?)
    bool left_down = IsKeyDown(KEY_A);
    bool right_down = IsKeyDown(KEY_D);
    bool jump_pressed = IsKeyPressed(KEY_SPACE);
    bool shoot_pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool upper_down = IsKeyDown(KEY_W);
    bool upper_pressed = IsKeyPressed(KEY_W);
    bool lower_down = IsKeyDown(KEY_S);

    //Set velocity of player
    if(right_down) {
        vel_x = 100.0f*level->deltaTime;
        player.dir = 1.0f;
    }
    if(left_down) {
        vel_x = -100.0f*level->deltaTime;
        player.dir = -1.0f;
    }
    if((!left_down && !right_down) ||(left_down && right_down)) {
        vel_x = 0;
        player.walking = false;
        if(!player.idle && !player.jumping && !player.climbing) {
            changeAnimationTo(&player, &player_animations[IDLE]);
            player.idle = true;
        }
    } else {
        player.idle = false;
        if(!player.walking && !player.jumping && !player.climbing) {
            changeAnimationTo(&player, &player_animations[WALK]);
            player.walking = true;
        }
    }

    //Player is climbing the ladder
    if(level->ladder_colliding)
    {
        if(upper_pressed && player.onGround) //on the floor, beginning to climb
        {
            player.onGround = false;
            if(upper_down) vel_y = -100*level->deltaTime;
        }
        if(!player.onGround) //on the ladder
        {
            if (upper_down) vel_y = -100*level->deltaTime;
            if (lower_down) vel_y = 100*level->deltaTime;
        }

        if((upper_down || lower_down) && !player.climbing) {
            changeAnimationTo(&player, &player_animations[CLIMB]);
            player.climbing = true;
            player.idle = false;
            player.walking = false;
        }

        if(player.onGround) {
            player.climbing = false;
        }
    } else {
        player.climbing = false;
    }

    //Player has jumped
    if(jump_pressed && player.onGround) {
        if(!player.jumping) {
            changeAnimationTo(&player, &player_animations[JUMP]);
            player.jumping = true;
            player.walking = false;
            player.idle = false;
        }
        player.onGround = false;
        vel_y = -225.0f*level->deltaTime;
    }

    //Bullet has been shot
    if(shoot_pressed && !player.bullet.active) {
        setShoot(&player);
        player.bullet.active = true;
    }

    //After check input, updates player velocity
    setPlayerVelocity(&player, (Vector2){vel_x, vel_y});
}

static void update() {
    static bool phase_done = false;

    //Move player to next position := (position + velocity)
    movePlayer(&player);

    //Move Animation to next step
    level->frame_counter++;
    moveAnimation(&player, &level->frame_counter);

    //If bullet has been shot, update its positions (i. e., shoot)
    if(player.bullet.active) {
        shoot(&player.bullet);
    }

    //If player is not on ground, apply velocity downwards (gravity)
    if(!player.onGround && !level->ladder_colliding) player.velocity.y += 10.0f*level->deltaTime;

    UpdatePlayerCamera(&camera, &player, (float)level->bg->width);
}

static void physicsUpdate() {
    //Clamp map limits - Player
    if(player.position.x < 0) setPlayerPosition(&player, (Vector2){0, player.position.y});
    if(player.position.x + player.collider_rect.width > (float)level->bg->width) setPlayerPosition(&player, (Vector2){(float)level->bg->width - player.collider_rect.width, player.position.y});

    //Clamp map limits - Bullet
    if(player.bullet.collider.collider.x < 0) {
        player.bullet.active = false;
    }
    if(player.bullet.collider.collider.x + player.bullet.collider.collider.width > (float)level->bg->width){
        player.bullet.active = false;
    }

    for(int i = 0; i < *level->colliders_length; i++) {
        //Player Collisions
        if(CheckCollisionRecs(player.collider_rect, level->colliders[i].collider)) {
            Rectangle collision_rect = GetCollisionRec(player.collider_rect, level->colliders[i].collider);
            if(level->colliders[i].colliderType == GROUND) {
                playerOnCollisionGround(&player, level->colliders[i].collider, collision_rect);
                level->current_ground = i;
            }
            else if(level->colliders[i].colliderType == WALL) {
                playerOnCollisionWall(&player, level->colliders[i].collider,collision_rect);
            }
            else if(level->colliders[i].colliderType == PLATFORM) {
                playerOnCollisionPlatform(&player, level->colliders[i].collider, collision_rect);
                level->current_ground = i;
            }
            else if(level->colliders[i].colliderType == TRIGGER_LADDER) {
                level->ladder_colliding = true;
            }
            else if(level->colliders[i].colliderType == TRIGGER_DOOR){
                level->isPuzzleOn = true;
            }else if(level->colliders[i].colliderType == TRIGGER_CHEST){
                level->isNearChest = true;
            }
        } else {
            if(level->colliders[i].colliderType == TRIGGER_LADDER) { level->ladder_colliding = false; }
        }
        //Bullet Collisions
        if(level->colliders[i].colliderType != TRIGGER_LADDER) {
            if (CheckCollisionRecs(player.bullet.collider.collider, level->colliders[i].collider)) {
                player.bullet.active = false;
            }
        }
        //Puzzle flag
        if(level->colliders[i].colliderType != TRIGGER_DOOR) {
            level->isPuzzleOn = false;
        }
    }

    if(level->colliders[level->current_ground].colliderType == GROUND) {
        if(player.position.x + player.collider_rect.width < level->colliders[level->current_ground].collider.x) {
            player.onGround = false;
        }
        if(player.position.x > level->colliders[level->current_ground].collider.x + level->colliders[level->current_ground].collider.width) {
            player.onGround = false;
        }
    }
}

void chestMessage(){
    Rectangle rec = {170, 140, 300, 200};
    if(level->isNearChest == true){
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));
        DrawRectangleRec(rec, Fade(WHITE, 0.55f));
        DrawRectangleLinesEx(rec, 3, BLACK);
        DrawText("Boa tentativa, ", 180, 165, 35, BLACK);
        DrawText("mas eu não sou ", 180, 205, 35, BLACK);
        DrawText("uma porta...", 180, 240, 35, BLACK);
        //Set chest flag to stop seeing text when far from it
        level->isNearChest = false;
    }
}

static void draw() {
    ClearBackground(WHITE);

    BeginDrawing();
    //Draw background
    DrawTexture(*level->bg, 0, 0, WHITE);

    //Draw player
    if(player.dir < 0) { DrawTextureRec(*player.texture, flippedRectangle(player.src_rect), player.position, WHITE); }
    else { DrawTextureRec(*player.texture, player.src_rect, player.position, WHITE); }

    //If bullet has been shot, draw
    if(player.bullet.active) {
        DrawTexture(*player.bullet.texture, (int)player.bullet.collider.collider.x, (int)player.bullet.collider.collider.y, WHITE);
    }

    //drawColliders();
    //DrawRectangleLinesEx(player.collider_rect, 2, LIME);
    //DrawFPS((int)(camera.target.x-camera.offset.x), (int)(camera.target.y-camera.offset.y));

    chestMessage();

    if(level->isPuzzleOn == true){
        callPuzzle();
        if(complete()){
            fim();
            level->isPuzzleOn = false;
            level->levelFinished = true;
            currentLevel = LEVEL3_2;
        }
    }
    EndDrawing();
}

static void clearLevel() {
    UnloadTexture(*level->bg);
    free(level);
    level = NULL;
}