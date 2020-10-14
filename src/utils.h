#ifndef IP1_2VA_UTILS_H
#define IP1_2VA_UTILS_H

#include "level2.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_HEALTH 4
#define BLOCK_SIZE 48

#define FONT_DIR "assets/fonts"
#define PLAYER_DIR "assets/player"
#define AUDIO_DIR "assets/audio"
#define MAPS_DIR "assets/maps"

typedef enum {MENU = 0, LEVEL1, LEVEL2, LEVEL3, ENDING} Level;
typedef enum {STATIC = 0, TRIGGER, DYNAMIC} ColliderType;

typedef struct {
    Rectangle collider;
    ColliderType colliderType;
}Collider2D;

typedef struct {
    bool idle, walking, jumping;
    int health;
    Vector2 position;
    Texture2D *texture;
    Rectangle src_rect;
}Player;

#endif //IP1_2VA_UTILS_H
