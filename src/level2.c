#include "includes/level2.h"

//Variáveis Externas
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
//-------------------------------

static Level2 *level;

void mainLevel2() {
    startLevel2();
    while (!level->levelFinished) {
        level->deltaTime = GetFrameTime();
        inputHandlerLevel2();
        updateLevel2();
        physicsUpdateLevel2();
        renderLevel2();
        clearLevel2();
    }
}

static Rectangle flippedRectangle(Rectangle rect) {
    Rectangle result;
    result.x = rect.x;
    result.y = rect.y;
    result.width = -rect.width;
    result.height = rect.height;
    return  result;
}

static void setupPhase1(void) {
    //Creating File
    level->file_name = "load_textures.asm";
    char txt[100] = "\tglobal _game\n\textern _swap_textures\n_game:\n\tcall _swap_textures\nmessage:\t\ndb 'Textures Loaded'\n";
    SaveFileText(level->file_name, txt);

    //Dynamic Allocation - Phase 1
    level->bg = (Texture2D*) malloc(sizeof(Texture2D));
    level->colliders = (Collider2D*) malloc(3*sizeof(Collider2D));
    level->colliders_length = (size_t*) malloc(sizeof(size_t));
    *level->colliders_length = 3;
    *level->bg = LoadTexture(MAPS_DIR"/level2/phase1/final.png");

    //Ground
    level->colliders[0].colliderType = GROUND;
    level->colliders[0].collider.x = 0.0f;
    level->colliders[0].collider.height = (float) BLOCK_SIZE;
    level->colliders[0].collider.y = (float)screenHeight - level->colliders[0].collider.height;
    level->colliders[0].collider.width = (float)BLOCK_SIZE * 10.40f;

    //Wall
    level->colliders[1].colliderType = WALL;
    level->colliders[1].collider.x = level->colliders[0].collider.x + level->colliders[0].collider.width;
    level->colliders[1].collider.height = (float)BLOCK_SIZE * 8.0f;
    level->colliders[1].collider.y = (float)screenHeight - level->colliders[1].collider.height;
    level->colliders[1].collider.width = (float)BLOCK_SIZE * 4.5f;

    //Sign
    level->colliders[2].colliderType = TRIGGER_SIGN;
    level->colliders[2].collider.x = (float)BLOCK_SIZE * 5.15f;
    level->colliders[2].collider.height = (float)BLOCK_SIZE * 1.15f;
    level->colliders[2].collider.y = (float)screenHeight - (level->colliders[0].collider.height + level->colliders[2].collider.height);
    level->colliders[2].collider.width = (float)BLOCK_SIZE * 0.65f;

    //Set Player Position and Shoot
    setPlayerPosition(&player, (Vector2){0, (float) (screenHeight - (BLOCK_SIZE + player.texture->height))});
    setShoot(&player);

    player.onGround = false;
    player.jumping = false;
    player.climbing = false;
    player.walking = false;
    player.idle = true;
    player.dir = 1.0f;

    level->sign_text = "Hm... Eu nao sei muito bem o que esta acontecendo.\n"
                "Talvez tenha algo errado com o jogo.\n"
                "Sera que algo esta corrompendo as texturas?\n"
                "Talvez eu consiga acessar os modulos do jogo.";
}

static void setupPhase2(void) {
    //Free previous allocated memory and Unload Texture
    clearPhase1();

    //Dynamic Allocation - Phase 2
    level->bg = (Texture2D*) malloc(sizeof(Texture2D));
    level->colliders = (Collider2D*) malloc(13 * sizeof(Collider2D));
    level->colliders_length = (size_t*) malloc(sizeof(size_t));
    *level->colliders_length = 13; //4 Ground 2 Triggers 7 Platform = 13
    *level->bg = LoadTexture(MAPS_DIR"/level2/phase2/final.png");

    //Ground Left
    level->colliders[0].colliderType = GROUND;
    level->colliders[0].collider.x = 0.0f;
    level->colliders[0].collider.height = (float) BLOCK_SIZE;
    level->colliders[0].collider.y = (float)screenHeight - level->colliders[0].collider.height;
    level->colliders[0].collider.width = (float)BLOCK_SIZE * 18.35f;

    //Ground Right 1
    level->colliders[1].colliderType = GROUND;
    level->colliders[1].collider.x = (float)BLOCK_SIZE * 23.67f;
    level->colliders[1].collider.height = (float) BLOCK_SIZE;
    level->colliders[1].collider.y = (float)screenHeight - level->colliders[1].collider.height;
    level->colliders[1].collider.width = (float)BLOCK_SIZE * 8.00f;

    //Ground Right 2
    level->colliders[2].colliderType = GROUND;
    level->colliders[2].collider.x = (float)BLOCK_SIZE * 32.38f;
    level->colliders[2].collider.height = (float) BLOCK_SIZE;
    level->colliders[2].collider.y = (float)screenHeight - level->colliders[0].collider.height;
    level->colliders[2].collider.width = (float)BLOCK_SIZE * 1.90f;

    //Ground Right 3
    level->colliders[3].colliderType = GROUND;
    level->colliders[3].collider.x = (float)BLOCK_SIZE * 35.00f;
    level->colliders[3].collider.height = (float) BLOCK_SIZE;
    level->colliders[3].collider.y = (float)screenHeight - level->colliders[3].collider.height;
    level->colliders[3].collider.width = (float)BLOCK_SIZE * 5.00f;

    //Platform 1 (Small Rect)
    level->colliders[4].colliderType = PLATFORM;
    level->colliders[4].collider.x = (float)BLOCK_SIZE * 18.90f;
    level->colliders[4].collider.height = (float)BLOCK_SIZE;
    level->colliders[4].collider.y = (float)(screenHeight - (2.32 * level->colliders[4].collider.height));
    level->colliders[4].collider.width = (float)BLOCK_SIZE * 2.00f;

    //Platform 2 (Square)
    level->colliders[5].colliderType = PLATFORM;
    level->colliders[5].collider.x = (float)BLOCK_SIZE * 21.90f;
    level->colliders[5].collider.height = (float)BLOCK_SIZE;
    level->colliders[5].collider.y = (float)(screenHeight - (3.23 * level->colliders[5].collider.height));
    level->colliders[5].collider.width = (float)BLOCK_SIZE;

    //Platform 3 (Mid Rect)
    level->colliders[6].colliderType = PLATFORM;
    level->colliders[6].collider.x = (float)BLOCK_SIZE * 27.60f;
    level->colliders[6].collider.height = (float)BLOCK_SIZE;
    level->colliders[6].collider.y = (float)(screenHeight - (4.32 * level->colliders[6].collider.height));
    level->colliders[6].collider.width = (float)BLOCK_SIZE * 3.00f;

    //Platform 4 (Square)
    level->colliders[7].colliderType = PLATFORM;
    level->colliders[7].collider.x = (float)BLOCK_SIZE * 30.65f;
    level->colliders[7].collider.height = (float)BLOCK_SIZE;
    level->colliders[7].collider.y = (float)(screenHeight - (5.28 * level->colliders[7].collider.height));
    level->colliders[7].collider.width = (float)BLOCK_SIZE;

    //Platform 5 (Large Rect)
    level->colliders[8].colliderType = PLATFORM;
    level->colliders[8].collider.x = (float)BLOCK_SIZE * 31.73f;
    level->colliders[8].collider.height = (float)BLOCK_SIZE;
    level->colliders[8].collider.y = (float)(screenHeight - (6.25 * level->colliders[8].collider.height));
    level->colliders[8].collider.width = (float)BLOCK_SIZE * 4.00f;

    //Platform 6 (Square)
    level->colliders[9].colliderType = PLATFORM;
    level->colliders[9].collider.x = (float)BLOCK_SIZE * 35.83f;
    level->colliders[9].collider.height = (float)BLOCK_SIZE;
    level->colliders[9].collider.y = (float)(screenHeight - (5.28 * level->colliders[9].collider.height));
    level->colliders[9].collider.width = (float)BLOCK_SIZE;

    //Platform 7
    level->colliders[10].colliderType = PLATFORM;
    level->colliders[10].collider.x = (float)BLOCK_SIZE * 36.85f;
    level->colliders[10].collider.height = (float)BLOCK_SIZE;
    level->colliders[10].collider.y = (float)(screenHeight - (4.32 * level->colliders[10].collider.height));
    level->colliders[10].collider.width = (float)BLOCK_SIZE * 3.00f;

    //Stairs
    level->colliders[11].colliderType = TRIGGER_LADDER;
    level->colliders[11].collider.x = (float)BLOCK_SIZE * 26.84f;
    level->colliders[11].collider.height = (float)BLOCK_SIZE * 2.85f;
    level->colliders[11].collider.y = (float)(screenHeight - (1.55 * level->colliders[11].collider.height));
    level->colliders[11].collider.width = (float)BLOCK_SIZE * 0.6f;

    //Sign
    level->colliders[12].colliderType = TRIGGER_SIGN;
    level->colliders[12].collider.x = (float)BLOCK_SIZE * 7.35f;
    level->colliders[12].collider.height = (float)BLOCK_SIZE * 1.15f;
    level->colliders[12].collider.y = (float)screenHeight - (level->colliders[0].collider.height + level->colliders[12].collider.height);
    level->colliders[12].collider.width = (float)BLOCK_SIZE * 0.65f;

    //Set Player Position and Shoot
    player.onGround = false;
    player.jumping = false;
    player.climbing = false;
    player.walking = false;
    player.idle = true;
    player.dir = 1.0f;
    setPlayerPosition(&player, (Vector2){0, (float) (screenHeight - (BLOCK_SIZE + player.texture->height))});
    changeAnimationTo(&player, &player_animations[IDLE]);
    setShoot(&player);
    level->sign_colliding = false;
    level->invert_factor = 1.0f;

    level->sign_text = "As coisas voltaram ao normal...\n"
                "Aquele arquivo devia estar trocando as texturas e a movimentacao.\n"
                "Talvez seja uma boa ideia explorar, talvez eu encontre uma saida.\n"
                "Eu preciso sair daqui...";
}

static void drawColliders(void) {
    for(int i = 0; i < *level->colliders_length; i++) {
        DrawRectangleLinesEx(level->colliders[i].collider, 2, RED);
    }
}

static void showMessage(char *txt, float offset) {
    DrawTexture(*level->bg, 0, 0, Fade(BLACK, 0.6f));
    Rectangle signMessage = {0};
    signMessage.width = (float)(screenWidth)*0.75f;
    signMessage.height = (float)(screenHeight)*0.5f;
    signMessage.x = (camera.target.x - camera.offset.x) + ((float)screenWidth - signMessage.width)/2.0f;
    signMessage.y = ((float)screenHeight - signMessage.height)/2.0f;
    DrawRectangle((int) signMessage.x, (int) signMessage.y, (int) signMessage.width, (int) signMessage.height, Fade(GRAY, 0.8f));
    Rectangle txtRect = {0};
    txtRect.width = signMessage.width - 2.0f*offset;
    txtRect.height = signMessage.height - 2.0f*offset;
    txtRect.x = signMessage.x + offset;
    txtRect.y = signMessage.y + offset;
    DrawTextRec(font, txt, txtRect, 20.0f, 1.0f, true, WHITE);
}

static void startLevel2() {
    level = malloc(sizeof(Level2));
    level->levelFinished = false;
    level->transition = false;
    level->sign_colliding = false;
    level->ladder_colliding = false;
    level->invert_factor = -1.0f;
    level->duration = 3.0f;
    level->alpha = 1.0f;
    level->frame_counter = 0;
    level->current_ground = 0;
    setupPhase1();
}

static void inputHandlerLevel2() {
    if(WindowShouldClose()) {
        level->levelFinished = true;
        game_running = false;
    }

    //If it is transitioning, return
    if(level->transition) return;

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
    bool lower_pressed = IsKeyPressed(KEY_S);

    //Set velocity of player
    if(right_down) {
        vel_x = 100.0f*level->deltaTime*level->invert_factor;
        player.dir = 1.0f*level->invert_factor;
    }
    if(left_down) {
        vel_x = -100.0f*level->deltaTime*level->invert_factor;
        player.dir = -1.0f*level->invert_factor;
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
        vel_y = -300.0f*level->deltaTime;
    }

    //Bullet has been shot
    if(shoot_pressed && !player.bullet.active) {
        setShoot(&player);
        player.bullet.active = true;
    }

    //After check input, updates player velocity
    setPlayerVelocity(&player, (Vector2){vel_x, vel_y});
}

static void updateLevel2() {
    //If it is transitioning, return
    if(level->transition) return;

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

    //Check if file has been deleted and change phase
    if(!phase_done && !FileExists(level->file_name)) {
        phase_done = true;
        level->transition = true;
        setupPhase2();
    }

    UpdatePlayerCamera(&camera, &player, (float)level->bg->width);
}

static void physicsUpdateLevel2() {
    //If it is transitioning, return
    if(level->transition) return;

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
            else if(level->colliders[i].colliderType == TRIGGER_SIGN) {
                level->sign_colliding = true;
            }
            else if(level->colliders[i].colliderType == TRIGGER_LADDER) {
                level->ladder_colliding = true;
            }
        } else {
            if(level->colliders[i].colliderType == TRIGGER_LADDER) { level->ladder_colliding = false; }
            if(level->colliders[i].colliderType == TRIGGER_SIGN) { level->sign_colliding = false; }
        }
        //Bullet Collisions
        if(level->colliders[i].colliderType != TRIGGER_SIGN && level->colliders[i].colliderType != TRIGGER_LADDER) {
            if (CheckCollisionRecs(player.bullet.collider.collider, level->colliders[i].collider)) {
                player.bullet.active = false;
            }
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

static void renderLevel2() {
    BeginDrawing();
    BeginMode2D(camera);

    ClearBackground(WHITE);

    //Draw background
    DrawTexture(*level->bg, 0, 0, WHITE);

    //Draw player
    if(player.dir < 0) { DrawTextureRec(*player.texture, flippedRectangle(player.src_rect), player.position, WHITE); }
    else { DrawTextureRec(*player.texture, player.src_rect, player.position, WHITE); }

    //If bullet has been shot, draw
    if(player.bullet.active) {
        DrawTexture(*player.bullet.texture, (int)player.bullet.collider.collider.x, (int)player.bullet.collider.collider.y, WHITE);
    }

    //DrawText(TextFormat("(Vx, Vy): %.2f %.2f", player.velocity.x, player.velocity.y), (int)player.position.x, (int)player.position.y - 20, 12, BLUE);
    //DrawRectangleLinesEx(player.collider_rect, 2, RED);
    drawColliders();
    //DrawRectangleLinesEx(player.bullet.collider.collider, 2, GREEN);
    //DrawFPS((int)(camera.target.x-camera.offset.x), (int)(camera.target.y-camera.offset.y));

    //Sign
    if(level->sign_colliding) { showMessage(level->sign_text, 12.0f); }

    //Transition (Maybe global variables instead?)
    if(level->transition) {
        DrawRectangle(0,0, screenWidth, screenHeight, Fade(WHITE, level->alpha));
        level->duration -= 0.1f;
        if(level->duration < 0.01f) {
            level->alpha -= 0.01f;
            if(level->alpha < 0.01f) {
                level->transition = false;
            }
        }
    }

    EndMode2D();
    EndDrawing();
}

static void clearLevel2() {
    if(level->levelFinished) {
        UnloadTexture(*level->bg);
        free(level);
    }
}

static void clearPhase1() {
    UnloadTexture(*level->bg);
    free(level->bg);
    free(level->colliders);
    free(level->colliders_length);
    level->bg = NULL;
    level->colliders = NULL;
    level->colliders_length = NULL;
}