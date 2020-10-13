#include "utils.h"
extern const int screenWidth;
extern const int screenHeight;
extern Player player;

void inputHandlerLevel2() {

}

void updateLevel2() {

}

void physicsUpdateLevel2(void) {

}

void renderLevel2() {
    BeginDrawing();
    char str[80];
    sprintf(str, "W: %d, H: %d", screenWidth, screenHeight);
    ClearBackground(WHITE);
    DrawText(str, 5, 0, 36, BLUE);
    DrawTextureRec(*player.texture, player.src_rect, player.position, WHITE);
    DrawRectangleLines((int)player.position.x, (int)player.position.y, (int)player.src_rect.width, (int)player.src_rect.height, BLUE);
    EndDrawing();
}