#include "utils.h"

extern const int screenWidth;
extern const int screenHeight;
extern Player player;
extern float deltaTime;

static Texture2D *bg;
static Collider2D *colliders;
static size_t *colliders_length;
static char *file_name;
static bool transition;
static float duration = 3.0f;
static float alpha = 1.0f;

static void setupPhase1(void) {
    //Creating File
    file_name = "load_textures.asm";
    char txt[100] = "\tglobal _game\n\textern _swap_textures\n_game:\n\tcall _swap_textures\nmessage:\t\ndb 'Textures Loaded'\n";
    SaveFileText(file_name, txt);

    //Dynamic Allocation - Phase 1
    bg = (Texture2D*) malloc(sizeof(Texture2D));
    colliders = (Collider2D*) malloc(3*sizeof(Collider2D));
    colliders_length = (size_t*) malloc(sizeof(size_t));
    *colliders_length = 3;
    *bg = LoadTexture(MAPS_DIR"/level2/phase1/final.png");

    //Ground
    colliders[0].colliderType = GROUND;
    colliders[0].collider.x = 0.0f;
    colliders[0].collider.height = (float) BLOCK_SIZE;
    colliders[0].collider.y = (float)screenHeight - colliders[0].collider.height;
    colliders[0].collider.width = (float)BLOCK_SIZE * 10.40f;

    //Wall
    colliders[1].colliderType = WALL;
    colliders[1].collider.x = colliders[0].collider.x + colliders[0].collider.width;
    colliders[1].collider.height = (float)BLOCK_SIZE * 8.0f;
    colliders[1].collider.y = (float)screenHeight - colliders[1].collider.height;
    colliders[1].collider.width = (float)BLOCK_SIZE * 4.5f;

    //Sign
    colliders[2].colliderType = TRIGGER_SIGN;
    colliders[2].collider.x = (float)BLOCK_SIZE * 5.15f;
    colliders[2].collider.height = (float)BLOCK_SIZE * 1.15f;
    colliders[2].collider.y = (float)screenHeight - (colliders[0].collider.height + colliders[2].collider.height);
    colliders[2].collider.width = (float)BLOCK_SIZE * 0.65f;

    //Set Player Position and Shoot
    setPlayerPosition(&player, (Vector2){0, (float) (screenHeight - (BLOCK_SIZE + player.texture->height))});
    setShoot(&player);
    player.bullet.buffer_velocity = player.bullet.velocity;
}

static void setupPhase2(void) {
    //Free previous allocated memory and Unload Texture
    clearLevel2();

    //Dynamic Allocation - Phase 2
    bg = (Texture2D*) malloc(sizeof(Texture2D));
    colliders = (Collider2D*) malloc(17*sizeof(Collider2D));
    colliders_length = (size_t*) malloc(sizeof(size_t));
    *colliders_length = 17; //4 Ground 3 Triggers 9 Platform 1 Wall = 17
    *bg = LoadTexture(MAPS_DIR"/level2/phase2/final.png");
}

void clearLevel2() {
    UnloadTexture(*bg);
    free(bg);
    free(colliders);
    free(colliders_length);
    bg = NULL;
    colliders = NULL;
    colliders_length = NULL;
}

void startLevel2() {
    //Checking whether has already started
    static bool done = false;
    if(done) return;
    setupPhase1();
    done = true;
}

void inputHandlerLevel2() {
    //If it is transitioning, return
    if(transition) return;

    //Store current player velocity
    float vel_x = player.velocity.x;
    float vel_y = player.velocity.y;

    //Store current bullet velocity
    float bullet_vel_x = player.bullet.velocity.x;
    float bullet_vel_y = player.bullet.velocity.y;

    //Store current key states (Array?)
    bool left_down = IsKeyDown(KEY_A);
    bool left_pressed = IsKeyPressed(KEY_A);
    bool right_down = IsKeyDown(KEY_D);
    bool right_pressed = IsKeyPressed(KEY_D);
    bool jump_pressed = IsKeyPressed(KEY_SPACE);
    bool shoot_pressed = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    //Set velocity of player
    if(right_down) { vel_x = 100.0f*deltaTime; }
    if(left_down) { vel_x = -100.0f*deltaTime; }
    if((!left_down && !right_down) ||(left_down && right_down)) { vel_x = 0; }

    //Player has jumped
    if(jump_pressed && player.onGround) {
        player.onGround = false;
        player.jumping = true;
        vel_y = -250.0f*deltaTime;
    }

    //Set bullet velocity
    if(left_down || left_pressed) {
        if(!player.bullet.active) { bullet_vel_x = -fabsf(bullet_vel_x); }
        player.bullet.buffer_velocity = (Vector2){-fabsf(bullet_vel_x), bullet_vel_y};
    }
    if(right_down || right_pressed) {
        if(!player.bullet.active) { bullet_vel_x = fabsf(bullet_vel_x); }
        player.bullet.buffer_velocity = (Vector2){fabsf(bullet_vel_x), bullet_vel_y};
    }

    //Bullet has been shot
    if(shoot_pressed && !player.bullet.active) { player.bullet.active = true; }

    //After check input, updates player velocity
    setPlayerVelocity(&player, (Vector2){vel_x, vel_y});

    //After check input, updates bullet velocity (Create buffer?)
    setBulletVelocity(&player.bullet, (Vector2){bullet_vel_x, bullet_vel_y});
}

void updateLevel2() {
    //If it is transitioning, return
    if(transition) return;

    static bool phase_done = false;

    //Move player to next position := (position + velocity)
    movePlayer(&player);

    //If bullet has been shot, update its positions (i. e., shoot)
    if(player.bullet.active) {
        shoot(&player.bullet);
    } else {
        setShoot(&player);
    }

    //If player is not on ground, apply velocity downwards (gravity)
    if(!player.onGround) player.velocity.y += 10.0f*deltaTime;

    //Check if file has been deleted and change phase
    if(!phase_done && !FileExists(file_name)) {
        phase_done = true;
        transition = true;
        setupPhase2();
    }
}

void physicsUpdateLevel2() {
    //If it is transitioning, return
    if(transition) return;

    //Clamp map limits - Player
    if(player.position.x < 0) setPlayerPosition(&player, (Vector2){0, player.position.y});
    if(player.position.x + player.collider_rect.width > (float)screenWidth) setPlayerPosition(&player, (Vector2){(float)screenWidth - player.collider_rect.width, player.position.y});

    //Clamp map limits - Bullet
    if(player.bullet.collider.collider.x < 0) {
        setShoot(&player);
        updateBulletVelocityFromBuffer(&player.bullet);
    }
    if(player.bullet.collider.collider.x + player.bullet.collider.collider.width > (float) screenWidth){
        setShoot(&player);
        updateBulletVelocityFromBuffer(&player.bullet);
    }

    for(int i = 0; i < *colliders_length; i++) {
        //Player Collisions
        if(CheckCollisionRecs(player.collider_rect, colliders[i].collider)) {
            Rectangle collision_rect = GetCollisionRec(player.collider_rect, colliders[i].collider);
            if(colliders[i].colliderType == GROUND) {
                playerOnCollisionGround(&player, colliders[i].collider, collision_rect);
            }
            else if(colliders[i].colliderType == WALL) {
                playerOnCollisionWall(&player, colliders[i].collider,collision_rect);
            }
            else if(colliders[i].colliderType == PLATFORM) {
                playerOnCollisionPlatform(&player, colliders[i].collider, collision_rect);
            }
            else if(colliders[i].colliderType == TRIGGER_SIGN) {
                playerOnCollisionSign();
            }
            else if(colliders[i].colliderType == TRIGGER_LADDER) {
                playerOnCollisionLadder(&player, colliders[i].collider);
            }
        }

        //Bullet Collisions
        if(colliders[i].colliderType != TRIGGER_SIGN && colliders[i].colliderType != TRIGGER_LADDER) {
            if (CheckCollisionRecs(player.bullet.collider.collider, colliders[i].collider)) {
                player.bullet.active = false;
                updateBulletVelocityFromBuffer(&player.bullet);
            }
        }
    }
}

void drawColliders() {
    for(int i = 0; i < *colliders_length; i++) {
        DrawRectangleLinesEx(colliders[i].collider, 2, RED);
    }
}

void renderLevel2() {
    ClearBackground(WHITE);

    //Draw background
    DrawTexture(*bg, 0, 0, WHITE);

    //Draw player
    DrawTextureRec(*player.texture, player.src_rect, player.position, WHITE);

    //If bullet has been shot, draw
    if(player.bullet.active) {
        DrawTexture(*player.bullet.texture, (int)player.bullet.collider.collider.x, (int)player.bullet.collider.collider.y, WHITE);
    }

    //DrawText(TextFormat("(Vx, Vy): %.2f %.2f", player.velocity.x, player.velocity.y), (int)player.position.x, (int)player.position.y - 20, 12, BLUE);
    //DrawRectangleLinesEx(player.collider_rect, 2, RED);
    //drawColliders();
    //DrawRectangleLinesEx(player.bullet.collider.collider, 2, GREEN);
    DrawFPS(0, 0);

    //Transition (Maybe global variables instead?)
    if(transition) {
        DrawRectangle(0,0, screenWidth, screenHeight, Fade(WHITE, alpha));
        duration -= 0.1f;
        if(duration < 0.01f) {
            alpha -= 0.01f;
            if(alpha < 0.01f) {
                transition = false;
            }
        }
    }
}