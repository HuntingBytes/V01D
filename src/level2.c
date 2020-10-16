#include "utils.h"

extern const int screenWidth;
extern const int screenHeight;
extern Font font;
extern Player player;
extern float deltaTime;

static Texture2D *bg;
static Collider2D *colliders;
static size_t *colliders_length;
static char *file_name;

bool signColliding = 0;

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

    //Set Player Position
    setPlayerPosition(&player, (Vector2){300, (float) (screenHeight - (BLOCK_SIZE + player.texture->height))});

}

static void setupPhase2(void) {
    //Free previous allocated memory and Unload Texture
    //clearLevel2();                                            //AAAAAAAAAAAAAAAAA

    //Dynamic Allocation - Phase 2
    bg = (Texture2D*) malloc(sizeof(Texture2D));
    colliders = (Collider2D*) malloc(17*sizeof(Collider2D));
    colliders_length = (size_t*) malloc(sizeof(size_t));
    *colliders_length = 17; //4 Ground 3 Triggers 9 Platform 1 Wall = 17
    *bg = LoadTexture(MAPS_DIR"/level2/phase2/final.png");


    //Ground Left
    colliders[0].colliderType = GROUND;
    colliders[0].collider.x = 0.0f;
    colliders[0].collider.height = (float) BLOCK_SIZE;
    colliders[0].collider.y = (float)screenHeight - colliders[0].collider.height;
    colliders[0].collider.width = (float)BLOCK_SIZE * 18.35f;

    //Ground Right 1
    colliders[1].colliderType = GROUND;
    colliders[1].collider.x = (float)BLOCK_SIZE * 23.67f;
    colliders[1].collider.height = (float) BLOCK_SIZE;
    colliders[1].collider.y = (float)screenHeight - colliders[1].collider.height;
    colliders[1].collider.width = (float)BLOCK_SIZE * 8.00f;

    //Ground Right 2
    colliders[2].colliderType = GROUND;
    colliders[2].collider.x = (float)BLOCK_SIZE * 32.38f;
    colliders[2].collider.height = (float) BLOCK_SIZE;
    colliders[2].collider.y = (float)screenHeight - colliders[0].collider.height;
    colliders[2].collider.width = (float)BLOCK_SIZE * 1.90f;

    //Ground Right 3
    colliders[3].colliderType = GROUND;
    colliders[3].collider.x = (float)BLOCK_SIZE * 35.00f;
    colliders[3].collider.height = (float) BLOCK_SIZE;
    colliders[3].collider.y = (float)screenHeight - colliders[3].collider.height;
    colliders[3].collider.width = (float)BLOCK_SIZE * 5.00f;



    //Plataform 1 (Small Rect)
    colliders[4].colliderType = PLATFORM;
    colliders[4].collider.x = (float)BLOCK_SIZE * 18.90f;
    colliders[4].collider.height = (float)BLOCK_SIZE;
    colliders[4].collider.y = (float)(screenHeight - (2.32 * colliders[4].collider.height));
    colliders[4].collider.width = (float)BLOCK_SIZE * 2.00f;

    //Plataform 2 (Square)
    colliders[5].colliderType = PLATFORM;
    colliders[5].collider.x = (float)BLOCK_SIZE * 21.90f;
    colliders[5].collider.height = (float)BLOCK_SIZE;
    colliders[5].collider.y = (float)(screenHeight - (3.23 * colliders[5].collider.height));
    colliders[5].collider.width = (float)BLOCK_SIZE;

    //Plataform 3 (Mid Rect)
    colliders[6].colliderType = PLATFORM;
    colliders[6].collider.x = (float)BLOCK_SIZE * 27.60f;
    colliders[6].collider.height = (float)BLOCK_SIZE;
    colliders[6].collider.y = (float)(screenHeight - (4.32 * colliders[6].collider.height));
    colliders[6].collider.width = (float)BLOCK_SIZE * 3.00f;

    //Plataform 4 (Square)
    colliders[7].colliderType = PLATFORM;
    colliders[7].collider.x = (float)BLOCK_SIZE * 30.65f;
    colliders[7].collider.height = (float)BLOCK_SIZE;
    colliders[7].collider.y = (float)(screenHeight - (5.28 * colliders[7].collider.height));
    colliders[7].collider.width = (float)BLOCK_SIZE;

    //Plataform 5 (Large Rect)
    colliders[8].colliderType = PLATFORM;
    colliders[8].collider.x = (float)BLOCK_SIZE * 31.73f;
    colliders[8].collider.height = (float)BLOCK_SIZE;
    colliders[8].collider.y = (float)(screenHeight - (6.25 * colliders[8].collider.height));
    colliders[8].collider.width = (float)BLOCK_SIZE * 4.00f;

    //Plataform 6 (Square "R-Symmetric")
    colliders[9].colliderType = PLATFORM;
    colliders[9].collider.x = (float)BLOCK_SIZE * 35.83f;
    colliders[9].collider.height = (float)BLOCK_SIZE;
    colliders[9].collider.y = (float)(screenHeight - (5.28 * colliders[9].collider.height));
    colliders[9].collider.width = (float)BLOCK_SIZE;

    //Plataform 7
    colliders[10].colliderType = PLATFORM;
    colliders[10].collider.x = (float)BLOCK_SIZE * 36.85f;
    colliders[10].collider.height = (float)BLOCK_SIZE;
    colliders[10].collider.y = (float)(screenHeight - (4.32 * colliders[10].collider.height));
    colliders[10].collider.width = (float)BLOCK_SIZE * 3.00f;
/*
     //Plataform 8
    colliders[11].colliderType = PLATFORM;
    colliders[11].collider.x = (float)BLOCK_SIZE * 18.90f;
    colliders[11].collider.height = (float)BLOCK_SIZE;
    colliders[11].collider.y = (float)(screenHeight - (2.32 * colliders[4].collider.height));
    colliders[11].collider.width = (float)BLOCK_SIZE * 2.00f;


     //Plataform 9
    colliders[11].colliderType = PLATFORM;
    colliders[11].collider.x = (float)BLOCK_SIZE * 18.90f;
    colliders[11].collider.height = (float)BLOCK_SIZE;
    colliders[11].collider.y = (float)(screenHeight - (2.32 * colliders[4].collider.height));
    colliders[11].collider.width = (float)BLOCK_SIZE * 2.00f;

*/
    //Stairs
    colliders[12].colliderType = STAIRS;
    colliders[12].collider.x = (float)BLOCK_SIZE * 26.84f;
    colliders[12].collider.height = (float)BLOCK_SIZE * 3.25f;
    colliders[12].collider.y = (float)screenHeight - (colliders[12].collider.height + colliders[2].collider.height);
    colliders[12].collider.width = (float)BLOCK_SIZE * 0.45f;

    //Set Player Position
    setPlayerPosition(&player, (Vector2){300, (float) (screenHeight - (BLOCK_SIZE + player.texture->height))});



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
    setupPhase2();                                   //AAAAAAAAAAAAAAAAAAAAAA
    done = true;
    printf("Level 2 - Phase 1: Loaded");
    fflush(stdout);
}

void inputHandlerLevel2() {
    //Store current player velocity
    float vel_x = player.velocity.x;
    float vel_y = player.velocity.y;

    if(IsKeyDown(KEY_D)) {
        vel_x = 100.0f*deltaTime;
    }

    if(IsKeyDown(KEY_A)) {
        vel_x = -100.0f*deltaTime;
    }

    if((IsKeyUp(KEY_D) && IsKeyUp(KEY_A)) ||(IsKeyDown(KEY_D) && IsKeyDown(KEY_A))) {
        vel_x = 0;
    }

    if(IsKeyPressed(KEY_SPACE) && player.onGround) {
        player.onGround = false;
        player.jumping = true;
        vel_y = -5.0f;
    }

    //After check input, updates player velocity
    setPlayerVelocity(&player, (Vector2){vel_x, vel_y});
}

void updateLevel2() {
    //Move player to next position := (position + velocity)
    movePlayer(&player);

    //Clamp map limits
    if(player.position.x < 0) setPlayerPosition(&player, (Vector2){0, player.position.y});
    if(player.position.x + player.collider_rect.width > (float)screenWidth) setPlayerPosition(&player, (Vector2){(float)screenWidth - player.collider_rect.width, player.position.y});

    //If player is not on ground, apply velocity downwards (gravity)
    if(!player.onGround) player.velocity.y += 10.0f*deltaTime;

    //Check if file has been deleted
    if(!FileExists(file_name)) {

        printf("File deleted :)\n");
        fflush(stdout);
    }
}

void physicsUpdateLevel2() {
    for(int i = 0; i < *colliders_length; i++) {
        if(CheckCollisionRecs(player.collider_rect, colliders[i].collider)) {
            Rectangle collision_rect = GetCollisionRec(player.collider_rect, colliders[i].collider);
            if(colliders[i].colliderType == WALL) {
                if(lastPositionPlayer(&player).x < colliders[i].collider.x) setPlayerPosition(&player, (Vector2) {player.position.x - collision_rect.width, player.position.y});
                else setPlayerPosition(&player, (Vector2) {player.position.x + collision_rect.width, player.position.y});
            }
            else if(colliders[i].colliderType == GROUND) {
                setPlayerPosition(&player, (Vector2) {player.position.x, player.position.y - collision_rect.height});
                setPlayerVelocity(&player, (Vector2){player.velocity.x, 0});
                player.onGround = true;
            }
            else if(colliders[i].colliderType == PLATFORM) {
                setPlayerPosition(&player, (Vector2) {player.position.x - collision_rect.width, player.position.y - collision_rect.height});
                setPlayerVelocity(&player, (Vector2){player.velocity.x, 0});
                player.onGround = true;
            }
            else if(colliders[i].colliderType == TRIGGER_SIGN) {
                signColliding = 1;

                printf("Action.\n");
                fflush(stdout);
            }

        }
        else signColliding = 0;
    }
}

void drawColliders() {
    for(int i = 0; i < *colliders_length; i++) {
        DrawRectangleLines((int)colliders[i].collider.x, (int)colliders[i].collider.y, (int)colliders[i].collider.width, (int)colliders[i].collider.height, RED);
    }
}


void showMessage()
{


        ClearBackground(WHITE);
        setPlayerVelocity(&player, (Vector2) {0.0f, 0.0f});

        Texture2D bgFaded = LoadTexture(MAPS_DIR"/level2/phase1/final.png");

        DrawTexture(bgFaded, 0, 0, Fade(BLACK, 0.6f));

        Rectangle signMessage = {120, 120, 300, 190};
        DrawRectangleLines((int) signMessage.x, (int) signMessage.y, (int) signMessage.width, (int) signMessage.height,
                           BLACK);
        DrawTextRec(font, "Maybe, just maybe, there is a suspicious file out there...", signMessage, 33.0f, 1.0f, 1,
                    BLACK);

}


// ALL DRAWING MUST BE HERE
void renderLevel2() {
    ClearBackground(WHITE);
    DrawTexture(*bg, 0, 0, WHITE);
    DrawTextureRec(*player.texture, player.src_rect, player.position, WHITE);
    DrawText(TextFormat("(Vx, Vy): %.2f %.2f", player.velocity.x, player.velocity.y), (int)player.position.x, (int)player.position.y - 20, 12, BLUE);
    DrawRectangleLines((int)player.collider_rect.x, (int)player.collider_rect.y, (int)player.collider_rect.width, (int)player.collider_rect.height, RED);
    drawColliders();
    DrawFPS(0, 0);

    if(signColliding) showMessage();

}