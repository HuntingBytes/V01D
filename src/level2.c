#include "includes/level2.h"
#include "includes/npc.h"
#include "includes/enemy.h"
#include "includes/icon.h"

//Variaveis Externas ------------ Essas variaveis ja foram declaradas e definidas na main.c, agora iremos utilizar elas sem precisar definir novamente
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
//-------------------------COISAS ------
Enemy enemy;
NPC npc;
Icon health_icon;
Icon bullet_icon;

static Texture2D enemy_texture;
static Texture2D npc_texture;

static Texture2D health_icon_tex;
static Texture2D bullet_icon_tex;

static bool enemy_initialized = false;
static bool release_icons = false;

//------------------------
static Level2 *level; //Ponteiro para uma struct que possui diversas variaveis utilizadas nesse nivel

//Funcao que vai ser chamada pela main.c quando estiver na fase 2
void mainLevel2() {
    startLevel2();
    while (!level->levelFinished) {
        level->deltaTime = GetFrameTime();
        inputHandlerLevel2();
        updateLevel2();
        physicsUpdateLevel2();
        renderLevel2();
    }
    clearLevel2();
}

static void resetPhase2(void) {
    release_icons = true;
    enemy_initialized = true;

    setEnemyHealth(&enemy, (Vector2){1650.53f, 96.77f});
    setEnemyPosition(&enemy, (Vector2){1610.38f, 108.10f});

    player.onGround = false;
    player.jumping = false;
    player.climbing = false;
    player.walking = false;
    player.idle = true;
    player.dir = 1.0f;

    setPlayerPosition(&player, (Vector2){0, (float) (screenHeight - (BLOCK_SIZE + player.texture->height))});
    changeAnimationTo(&player, &player_animations[IDLE]);
    setShoot(&player);
    setPlayerHealth(&player, MAX_HEALTH);

    setIcon(&bullet_icon, bullet_icon.texture, (Vector2){5.0f, 90.0f});
    setIcon(&health_icon, health_icon.texture, (Vector2){5.0f, 50.0f});

    level->sign_colliding = false;
    level->invert_factor = 1.0f;
}

//Retorna um retangulo flipado no eixo x (Usado para desenha a textura olhando para outro sentido)
static Rectangle flippedRectangle(Rectangle rect) {
    Rectangle result;
    result.x = rect.x;
    result.y = rect.y;
    result.width = -rect.width;
    result.height = rect.height;
    return  result;
}

//Inicia a parte 1
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

//Inicia a parte 2
static void setupPhase2(void) {
    //Free previous allocated memory and Unload Texture
    clearPhase1();

    //Release
    release_icons = true;

    //Setup Player Health and Bullets Icons
    health_icon_tex = LoadTexture(PLAYER_DIR"/heart.png");
    bullet_icon_tex = LoadTexture(PLAYER_DIR"/bullet.png");

    //Setup Icon Attributes
    Vector2 init_health_pos = {5.0f, 50.0f};
    Vector2 init_bullet_pos = {5.0f, 90.0f};
    setIcon(&health_icon, &health_icon_tex, init_health_pos);
    setIcon(&bullet_icon, &bullet_icon_tex, init_bullet_pos);

    //Setup Enemy
    enemy_texture = LoadTexture(ENEMY_DIR"/idle.png");
    setEnemyHealth(&enemy, (Vector2){1650.53f, 96.77f});
    setEnemyPosition(&enemy, (Vector2){1610.38f, 108.10f});
    setEnemyTexture(&enemy, &enemy_texture);
    enemy_initialized = true;


    //Setup NPC
    npc_texture = LoadTexture(NPC_DIR"/oldwoman/Old_woman.png");
    setNPCPosition(&npc, (Vector2) {1780.00f, ((float)screenHeight - (float)(BLOCK_SIZE + npc_texture.height))});
    setNPCTexture(&npc, &npc_texture);

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
    level->npc_colliding = false;
    level->sign_text = "As coisas voltaram ao normal...\n"
                "Aquele arquivo devia estar trocando as texturas e a movimentacao.\n"
                "Talvez seja uma boa ideia explorar, talvez eu encontre uma saida.\n"
                "Eu preciso sair daqui...";
    level->npc_text = "Nao se preocupe, voce esta perto do fim. \n"
                      "No entanto, ainda lhe resta uma missao a ser feita.\n"
                      "Siga em frente (Pressione o enter)";
}

//Desenha os colisores na tela (debug-only)
static void drawColliders(void) {
    for(int i = 0; i < *level->colliders_length; i++) {
        DrawRectangleLinesEx(level->colliders[i].collider, 2, RED);
    }
}

//Mostra uma mensagem na tela dentro de um retangulo
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

//Inicia o nivel 2
static void startLevel2() {
    level = (Level2 *) malloc(sizeof(Level2));
    level->levelFinished = false;
    level->transition = false;
    level->sign_colliding = false;
    level->npc_colliding = false;
    level->ladder_colliding = false;
    level->invert_factor = -1.0f;
    level->duration = 3.0f;
    level->alpha = 1.0f;
    level->frame_counter = 0;
    level->current_ground = 0;
    setupPhase1();
}

//Lida com os dados de entrada
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

//Atualiza o que for necessario de acordo com os dados de entrada
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

    if(player.health <= 0 || player.position.y > (float) screenHeight) {
        resetPhase2();
    }

    UpdatePlayerCamera(&camera, &player, (float)level->bg->width);
    UpdateIconPosition(&health_icon, &camera, &player);
    UpdateIconPosition(&bullet_icon, &camera, &player);
}

//Realiza a checagem de colisao e corrige essas colisoes
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

    //Player Collision NPC
    if(enemy.is_dead && CheckCollisionRecs(player.collider_rect, npc.collider_rect))
    {
        level->npc_colliding = true;
        if (IsKeyPressed(KEY_ENTER))
        {
            level->levelFinished = true;
            currentLevel = LEVEL3_2;
        }
    }
    else level->npc_colliding = false;

    //Player Collision Enemy
    if(CheckCollisionRecs(player.collider_rect, enemy.collider_rect))
    {
        enemyAttack(&enemy, &player);
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
            //Collision between Bullet and Enemy
            if(CheckCollisionRecs(player.bullet.collider.collider, enemy.collider_rect)){
                player.bullet.active = false;
                player.bullet.collider.collider.x = 0.0f;
                player.bullet.collider.collider.y = 0.0f;
                enemy.current_health--;
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

//Desenha o frame atual na tela
static void renderLevel2() {
    BeginDrawing();
    BeginMode2D(camera);

    ClearBackground(WHITE);

    //Draw background
    DrawTexture(*level->bg, 0, 0, WHITE);

    //Draw player
    if(player.dir < 0) { DrawTextureRec(*player.texture, flippedRectangle(player.src_rect), player.position, WHITE); }
    else { DrawTextureRec(*player.texture, player.src_rect, player.position, WHITE); }

    //Draw enemy
    if(enemy_initialized && enemy.current_health > 0)
    {
        DrawTextureRec(*enemy.texture, enemy.src_rect, enemy.position, WHITE);
    }

    //If bullet has been shot, draw
    if(player.bullet.active) {
        DrawTexture(*player.bullet.texture, (int)player.bullet.collider.collider.x, (int)player.bullet.collider.collider.y, WHITE);
    }


//DRAW PLAYER'S HEALTH AND BULLETS
    if(release_icons)
    {
        if(player.health >= 1)  DrawTextureRec(health_icon_tex, health_icon.icon_rect, health_icon.position,WHITE);
        if(player.health >= 2)  DrawTextureRec(health_icon_tex, health_icon.icon_rect, (Vector2){health_icon.position.x + 3.0f, health_icon.position.y},WHITE);
        if(player.health >= 3)  DrawTextureRec(health_icon_tex, health_icon.icon_rect, (Vector2){health_icon.position.x + 6.0f, health_icon.position.y},WHITE);
        if(player.health == 4)  DrawTextureRec(health_icon_tex, health_icon.icon_rect, (Vector2){health_icon.position.x + 9.0f, health_icon.position.y} ,WHITE);
        if(!player.bullet.active)   DrawTextureRec(bullet_icon_tex, bullet_icon.icon_rect, bullet_icon.position,WHITE);
    }

    //DRAW ENEMY HEALTH
    if(enemy.current_health == 5)   DrawCircle((int)enemy.health_position.x, (int)enemy.health_position.y, 25.0f, DARKGREEN);
    if(enemy.current_health == 4)   DrawCircle((int)enemy.health_position.x, (int)enemy.health_position.y, 25.0f, GREEN);
    if(enemy.current_health == 3)   DrawCircle((int)enemy.health_position.x, (int)enemy.health_position.y, 25.0f, ORANGE);
    if(enemy.current_health == 2)   DrawCircle((int)enemy.health_position.x, (int)enemy.health_position.y, 25.0f, YELLOW);
    if(enemy.current_health == 1)   DrawCircle((int)enemy.health_position.x, (int)enemy.health_position.y, 25.0f, RED);
    //Draw NPC, remove enemy
    if(enemy.current_health == 0 && enemy_initialized)
    {
        enemy.collider_rect.x = 0;
        enemy.collider_rect.y = 0;
        enemy.is_dead = true;
        enemy_initialized = false;
    }

    if(enemy.is_dead)   DrawTexture(*npc.texture, (int)npc.position.x, (int)npc.position.y, WHITE);

    //DrawText(TextFormat("(Vx, Vy): %.2f %.2f", player.velocity.x, player.velocity.y), (int)player.position.x, (int)player.position.y - 20, 12, BLUE);
    //DrawRectangleLinesEx(player.collider_rect, 2, RED);
    //drawColliders();
    //DrawRectangleLinesEx(player.bullet.collider.collider, 2, GREEN);
    //DrawFPS((int)(camera.target.x-camera.offset.x), (int)(camera.target.y-camera.offset.y));

    //Sign
    if(level->sign_colliding) { showMessage(level->sign_text, 12.0f); }
    if(level->npc_colliding) { showMessage(level->npc_text, 12.0f); }

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

//Limpa o nivel 2 (Descarrega texturas, libera memoria, etc)
static void clearLevel2() {
    UnloadTexture(*level->bg);
    free(level);
    level = NULL;
}

//Limpa a parte 1 (Usada antes de iniciar a parte 2)
static void clearPhase1() {
    UnloadTexture(*level->bg);
    free(level->bg);
    free(level->colliders);
    free(level->colliders_length);
    level->bg = NULL;
    level->colliders = NULL;
    level->colliders_length = NULL;
}