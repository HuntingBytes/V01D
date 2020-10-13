#ifndef IP1_2VA_UTILS_H
#define IP1_2VA_UTILS_H

#define MAX_HEALTH 4
#define FONT_DIR "assets/fonts"
#define PLAYER_DIR "assets/player"
#define AUDIO_DIR "assets/audio"

#include "level2.h"
#include "raylib.h"
#include <stdio.h>

typedef enum {MENU = 0, LEVEL1, LEVEL2, LEVEL3, ENDING} Level;

typedef struct {
    bool idle, walking, jumping;
    int health;
    Vector2 position;
    Rectangle collider;
    Texture2D *texture;
    Rectangle src_rect;
}Player;

#endif //IP1_2VA_UTILS_H
