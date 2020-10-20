#include "level3_phase1.h"

extern const int screenWidth;
extern const int screenHeight;
extern int game_running;
extern float deltaTime;
extern Font font;
extern Player player;
extern Texture2D tile;
extern Texture2D player_textures[];
extern Camera2D camera;
extern Animation player_animations[];

static Collider2D colliders[15];
static int frame_counter = 0;
static bool transition = false;
static float invert_factor = -1.0f;
static bool ladder_colliding = false;
static int current_ground = 0;
static int colliders_length = 15;
static float duration = 3.0f;
static float alpha = 1.0f;
static Rectangle flippedRectangle(Rectangle rect) {
    Rectangle result;
    result.x = rect.x;
    result.y = rect.y;
    result.width = -rect.width;
    result.height = rect.height;
    return  result;
}

void initLevel(){
    camera.target = (Vector2) {0,0};
    camera.offset = (Vector2) {0,0};
    camera.zoom = 1.5f;
    camera.rotation = 0.0f;

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

    setPlayerPosition(&player, (Vector2){0, (float) (screenHeight - (BLOCK_SIZE + player.texture->height))});
    setShoot(&player);

    player.onGround = false;
    player.jumping = false;
    player.climbing = false;
    player.walking = false;
    player.idle = true;
    player.dir = 1.0f;
}

void inputHandler(){
    //If it is transitioning, return
    if(transition) return;

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
        vel_x = 100.0f*deltaTime*invert_factor;
        player.dir = 1.0f*invert_factor;
    }
    if(left_down) {
        vel_x = -100.0f*deltaTime*invert_factor;
        player.dir = -1.0f*invert_factor;
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
    if(ladder_colliding)
    {
        if(upper_pressed && player.onGround) //on the floor, beginning to climb
        {
            player.onGround = false;
            if(upper_down) vel_y = -100*deltaTime;
        }
        if(!player.onGround) //on the ladder
        {
            if (upper_down) vel_y = -100*deltaTime;
            if (lower_down) vel_y = 100*deltaTime;
        }

        if((upper_down || lower_down) && !player.climbing) {
            changeAnimationTo(&player, &player_animations[CLIMB]);
            player.climbing = true;
            player.idle = false;
            player.walking = false;
        }

        if(!upper_down && !lower_down) {
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
        vel_y = -300.0f*deltaTime;
    }

    //Bullet has been shot
    if(shoot_pressed && !player.bullet.active) {
        setShoot(&player);
        player.bullet.active = true;
    }

    //After check input, updates player velocity
    setPlayerVelocity(&player, (Vector2){vel_x, vel_y});
}

void playerPos(Player *player){
    player -> position.x += player -> velocity.x;
    player -> position.y += player -> velocity.y;
    player -> collider_rect.x += player -> velocity.x;
    player -> collider_rect.y += player -> velocity.y;
}

void update() {
    //If it is transitioning, return
    if(transition) return;

    static bool phase_done = false;

    //Move player to next position := (position + velocity)
    movePlayer(&player);

    //Move Animation to next step
    frame_counter++;
    moveAnimation(&player, &frame_counter);

    //If bullet has been shot, update its positions (i. e., shoot)
    if(player.bullet.active) {
        shoot(&player.bullet);
    }

    //If player is not on ground, apply velocity downwards (gravity)
    if(!player.onGround && !ladder_colliding) player.velocity.y += 10.0f*deltaTime;

    UpdatePlayerCamera(&camera, &player, (float)tile.width);
}

void physicsUpdate() {
    //If it is transitioning, return
    if(transition) return;

    //Clamp map limits - Player
    if(player.position.x < 0) setPlayerPosition(&player, (Vector2){0, player.position.y});
    if(player.position.x + player.collider_rect.width > (float)tile.width) setPlayerPosition(&player, (Vector2){(float)tile.width - player.collider_rect.width, player.position.y});

    //Clamp map limits - Bullet
    if(player.bullet.collider.collider.x < 0) {
        player.bullet.active = false;
    }
    if(player.bullet.collider.collider.x + player.bullet.collider.collider.width > (float)tile.width){
        player.bullet.active = false;
    }

    for(int i = 0; i < colliders_length; i++) {
        //Player Collisions
        if(CheckCollisionRecs(player.collider_rect, colliders[i].collider)) {
            Rectangle collision_rect = GetCollisionRec(player.collider_rect, colliders[i].collider);
            if(colliders[i].colliderType == GROUND) {
                playerOnCollisionGround(&player, colliders[i].collider, collision_rect);
                current_ground = i;
            }
            else if(colliders[i].colliderType == WALL) {
                playerOnCollisionWall(&player, colliders[i].collider,collision_rect);
            }
            else if(colliders[i].colliderType == PLATFORM) {
                playerOnCollisionPlatform(&player, colliders[i].collider, collision_rect);
                current_ground = i;
            }
            //else if(colliders[i].colliderType == TRIGGER_SIGN) {
            //    sign_colliding = true;
           //}
            else if(colliders[i].colliderType == TRIGGER_LADDER) {
                ladder_colliding = true;
            }
        } else {
            if(colliders[i].colliderType == TRIGGER_LADDER) { ladder_colliding = false; }
            //if(colliders[i].colliderType == TRIGGER_SIGN) { sign_colliding = false; }
        }
        //Bullet Collisions
        if(colliders[i].colliderType != TRIGGER_LADDER) {
            if (CheckCollisionRecs(player.bullet.collider.collider, colliders[i].collider)) {
                player.bullet.active = false;
            }
        }
    }

    if(colliders[current_ground].colliderType == GROUND) {
        if(player.position.x + player.collider_rect.width < colliders[current_ground].collider.x) {
            player.onGround = false;
        }
        if(player.position.x > colliders[current_ground].collider.x + colliders[current_ground].collider.width) {
            player.onGround = false;
        }
    }
}

void draw(){
    BeginDrawing();
    //BeginMode2D(camera);

    ClearBackground(WHITE);
    DrawTexture(tile, 0, 0, WHITE);
    //DrawTextureRec(*player.texture, player.src_rect, player.position, WHITE);
    //DrawRectangleLinesEx(player.texture, 2, GOLD);
    DrawRectangleLinesEx(colliders[1].collider, 2, MAGENTA);
    /*
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
     */
    //callPuzzle();
    //complete();

    //EndMode2D();
    EndDrawing();
}

void rendere (){
    ClearBackground(WHITE);

    //Draw background
    DrawTexture(tile, 0, 0, WHITE);

    //Draw player
    if(player.dir < 0) { DrawTextureRec(*player.texture, flippedRectangle(player.src_rect), player.position, WHITE); }
    else { DrawTextureRec(*player.texture, player.src_rect, player.position, WHITE); }

    //If bullet has been shot, draw
    if(player.bullet.active) {
        DrawTexture(*player.bullet.texture, (int)player.bullet.collider.collider.x, (int)player.bullet.collider.collider.y, WHITE);
    }

    //DrawText(TextFormat("(Vx, Vy): %.2f %.2f", player.velocity.x, player.velocity.y), (int)player.position.x, (int)player.position.y - 20, 12, BLUE);
    //DrawRectangleLinesEx(player.collider_rect, 2, RED);
    //drawColliders();
    //DrawRectangleLinesEx(player.bullet.collider.collider, 2, GREEN);
    //DrawFPS((int)(camera.target.x-camera.offset.x), (int)(camera.target.y-camera.offset.y));

    //Sign
    //if(sign_colliding) { showMessage(sign_text, 12.0f); }

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