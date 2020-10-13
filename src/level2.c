#include "utils.h"
extern const int screenWidth;
extern const int screenHeight;

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
    EndDrawing();
}