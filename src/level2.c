#include "utils.h"

extern const int screenWidth;
extern const int screenHeight;
extern Player player;

static Texture2D *bg;
static Collider2D *colliders;

void startLevel2() {
    static bool done = false;
    if(done) return;
    //Dynamic Allocation - Phase 1
    bg = (Texture2D*) malloc(sizeof(Texture2D));
    colliders = (Collider2D*) malloc(3*sizeof(Collider2D));

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
    player.position.x = 0;
    player.position.y = (float) (screenHeight - (BLOCK_SIZE + player.texture->height));

    done = true;
    printf("Fase 2 - Parte 1: Carregado");
    fflush(stdout);
}

void clearLevel2() {
    free(bg);
    free(colliders);
}

void inputHandlerLevel2() {

}

void updateLevel2() {

}

void physicsUpdateLevel2(void) {

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
    DrawRectangleLines((int)player.position.x, (int)player.position.y, (int)player.src_rect.width, (int)player.src_rect.height, RED);
    drawColliders();
    EndDrawing();
}