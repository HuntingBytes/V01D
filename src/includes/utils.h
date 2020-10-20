#ifndef IP1_2VA_UTILS_H
#define IP1_2VA_UTILS_H

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FPS 60

#define BLOCK_SIZE 48
#define MAX_HEALTH 4

#define FONT_DIR "assets/fonts"
#define PLAYER_DIR "assets/player"
#define AUDIO_DIR "assets/audio"
#define MAPS_DIR "assets/maps"

typedef enum {MENU = 0, LEVEL1, LEVEL2, LEVEL3, ENDING} Level;
typedef enum {GROUND = 0, WALL, PLATFORM, TRIGGER_SIGN, TRIGGER_LADDER, TRIGGER_BULLET} ColliderType;
typedef enum {IDLE = 0, WALK, JUMP, CLIMB, DIE} AnimationType;

typedef struct {
    AnimationType type;
    int size_frame;
    int n_sprites;
    int current_frame;
    int frame_speed;
}Animation;

typedef struct {
    Rectangle collider;
    ColliderType colliderType;
}Collider2D;

typedef struct {
    bool active;
    int damage;
    float distance, current_distance;
    Texture2D *texture;
    Collider2D collider;
    Vector2 velocity;
}Bullet;

typedef struct {
    bool idle, walking, jumping, climbing, onGround;
    int health;
    float dir; //-1 or 1 : Direction (1: Right, -1: Left)
    Vector2 position, velocity;
    Texture2D *texture;
    Rectangle src_rect, collider_rect;
    Bullet bullet;
    Animation *current_animation;
}Player;

//Main Fases -----------
void mainMenu(void);
void mainLevel1(void);
void mainLevel2(void);
void mainLevel3(void);
void mainEnding(void);
//----------------------

#endif //IP1_2VA_UTILS_H
