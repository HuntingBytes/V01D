#ifndef IP1_2VA_UTILS_H
#define IP1_2VA_UTILS_H

#include "raylib.h"
#include "player.h"
#include "level2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 48

#define FONT_DIR "assets/fonts"
#define PLAYER_DIR "assets/player"
#define AUDIO_DIR "assets/audio"
#define MAPS_DIR "assets/maps"

typedef enum {MENU = 0, LEVEL1, LEVEL2, LEVEL3, ENDING} Level;
typedef enum {GROUND = 0, WALL, PLATFORM, TRIGGER_SIGN} ColliderType;

typedef struct {
    Rectangle collider;
    ColliderType colliderType;
}Collider2D;

#endif //IP1_2VA_UTILS_H
