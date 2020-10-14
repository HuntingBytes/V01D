#include "utils.h"

extern const int screenWidth;
extern const int screenHeight;
extern Player player;

static Texture2D *bg;
static Collider2D *colliders;
static size_t *colliders_length;

void startLevel2() {
    static bool done = false;
    if(done) return;
    //Dynamic Allocation - Phase 1
    bg = (Texture2D*) malloc(sizeof(Texture2D));
    colliders = (Collider2D*) malloc(3*sizeof(Collider2D));
    colliders_length = (size_t*) malloc(sizeof(size_t));
    *colliders_length = 3;

    *bg = LoadTexture(MAPS_DIR"/level2/phase1/final.png");

    //Floor
    colliders[0].colliderType = STATIC;
    colliders[0].collider.x = 0.0f;
    colliders[0].collider.height = (float) BLOCK_SIZE;
    colliders[0].collider.y = (float)screenHeight - colliders[0].collider.height;
    colliders[0].collider.width = (float)BLOCK_SIZE * 10.40f;

    //Wall
    colliders[1].colliderType = STATIC;
    colliders[1].collider.x = colliders[0].collider.x + colliders[0].collider.width;
    colliders[1].collider.height = (float)BLOCK_SIZE * 8.0f;
    colliders[1].collider.y = (float)screenHeight - colliders[1].collider.height;
    colliders[1].collider.width = (float)BLOCK_SIZE * 4.5f;

    //Sign
    colliders[2].colliderType = TRIGGER;
    colliders[2].collider.x = (float)BLOCK_SIZE * 5.15f;
    colliders[2].collider.height = (float)BLOCK_SIZE * 1.15f;
    colliders[2].collider.y = (float)screenHeight - (colliders[0].collider.height + colliders[2].collider.height);
    colliders[2].collider.width = (float)BLOCK_SIZE * 0.65f;

    //Set Player Position
    setPlayerPosition(&player, (Vector2){300, (float) (screenHeight - (BLOCK_SIZE + player.texture->height))});

    done = true;
    printf("Fase 2 - Parte 1: Carregado");
    fflush(stdout);
}

void clearLevel2() {
    UnloadTexture(*bg);
    free(bg);
    free(colliders);
    free(colliders_length);
}

void inputHandlerLevel2() {
    if(IsKeyDown(KEY_D)) {
        player.velocity.x = 2.0f;
    }

    if(IsKeyDown(KEY_A)) {
        player.velocity.x = -2.0f;
    }

    if(IsKeyUp(KEY_D) && IsKeyUp(KEY_A)) {
        player.velocity.x = 0;
    }
}

void updateLevel2() {
    movePlayer(&player);
    if(player.position.x < 0) setPlayerPosition(&player, (Vector2){0, player.position.y});
    if(player.position.x + player.collider_rect.width > (float)screenWidth) setPlayerPosition(&player, (Vector2){(float)screenWidth - player.collider_rect.width, player.position.y});
}

void physicsUpdateLevel2() {
    for(int i = 0; i < *colliders_length; i++) {
        if(CheckCollisionRecs(player.collider_rect, colliders[i].collider)) {
            if(colliders[i].colliderType == STATIC) {
                Rectangle collision_rect = GetCollisionRec(player.collider_rect, colliders[i].collider);
                if(lastPositionPlayer(&player).x < colliders[i].collider.x) setPlayerPosition(&player, (Vector2) {player.position.x - collision_rect.width, player.position.y});
                else setPlayerPosition(&player, (Vector2) {player.position.x + collision_rect.width, player.position.y});
            }
        }
    }
}

void drawColliders() {
    DrawRectangleLines((int)colliders[0].collider.x, (int)colliders[0].collider.y, (int)colliders[0].collider.width, (int)colliders[0].collider.height, RED);
    DrawRectangleLines((int)colliders[1].collider.x, (int)colliders[1].collider.y, (int)colliders[1].collider.width, (int)colliders[1].collider.height, RED);
    DrawRectangleLines((int)colliders[2].collider.x, (int)colliders[2].collider.y, (int)colliders[2].collider.width, (int)colliders[2].collider.height, RED);

}

void renderLevel2() {
    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexture(*bg, 0, 0, WHITE);
    DrawTextureRec(*player.texture, player.src_rect, player.position, WHITE);
    DrawRectangleLines((int)player.collider_rect.x, (int)player.collider_rect.y, (int)player.collider_rect.width, (int)player.collider_rect.height, RED);
    drawColliders();
    EndDrawing();
}