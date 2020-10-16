#ifndef IP1_2VA_UTILS_H
#define IP1_2VA_UTILS_H

#include "raylib.h"
#include "level2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BLOCK_SIZE 48
#define MAX_HEALTH 4

#define FONT_DIR "assets/fonts"
#define PLAYER_DIR "assets/player"
#define AUDIO_DIR "assets/audio"
#define MAPS_DIR "assets/maps"

typedef enum {MENU = 0, LEVEL1, LEVEL2, LEVEL3, ENDING} Level;
typedef enum {GROUND = 0, WALL, PLATFORM, TRIGGER_SIGN, TRIGGER_LADDER, TRIGGER_BULLET} ColliderType;

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
    Vector2 velocity, buffer_velocity;
}Bullet;

typedef struct {
    bool idle, walking, jumping, onGround;
    int health;
    Vector2 position, velocity;
    Texture2D *texture;
    Rectangle src_rect, collider_rect;
    Bullet bullet;
}Player;

void setPlayerHealth(Player *player, int value);
void setPlayerPosition(Player *player, Vector2 position);
void setPlayerTexture(Player *player, Texture2D *texture);
void setPlayerVelocity(Player *player, Vector2 velocity);
void movePlayer(Player *player);
Vector2 lastPositionPlayer(Player *player);
void playerOnCollisionGround(Player *player, Rectangle collider, Rectangle collision_rect);
void playerOnCollisionWall(Player *player, Rectangle collider, Rectangle collision_rect);
void playerOnCollisionPlatform(Player *player, Rectangle collider, Rectangle collision_rect);
void playerOnCollisionLadder(Player *player, Rectangle collider); //TODO
void playerOnCollisionSign(); //TODO

void setBulletDamage(Bullet *bullet, int damage);
void setBulletDistance(Bullet *bullet, float distance);
void setBulletTexture(Bullet *bullet, Texture2D *texture);
void setBulletVelocity(Bullet *bullet, Vector2 velocity);
void updateBulletVelocityFromBuffer(Bullet *bullet);
void setBulletPosition(Bullet *bullet, Vector2 position);
void setShoot(Player *player);
void shoot(Bullet *bullet);

void UpdatePlayerCamera(Camera2D *camera, Player *player, float screen_edge);
void clampCameraToLimits(Camera2D *camera, float screen_edge);
#endif //IP1_2VA_UTILS_H
