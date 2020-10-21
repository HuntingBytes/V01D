#ifndef IP1_2VA_UTILS_H
#define IP1_2VA_UTILS_H

#include "raylib.h"
#include "level2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define FPS 60


#define BLOCK_SIZE 48
#define MAX_HEALTH 4

#define FONT_DIR "assets/fonts"
#define PLAYER_DIR "assets/player"
#define AUDIO_DIR "assets/audio"
#define MAPS_DIR "assets/maps"
#define ENEMY_DIR "assets/enemies"
#define NPC_DIR "assets/npc"

typedef enum {MENU = 0, LEVEL1, LEVEL2, LEVEL3, ENDING} Level;
typedef enum {GROUND = 0, WALL, PLATFORM, TRIGGER_SIGN, TRIGGER_LADDER, TRIGGER_BULLET} ColliderType;
typedef enum {IDLE = 0, WALK, JUMP, CLIMB, DIE} AnimationType;



typedef struct
{
    Rectangle bar_rect;
    Vector2 position;
    Texture2D *texture;
}Bar;


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
    bool idle, walking, jumping, onGround;
    int health;
    float dir; //-1 or 1 : Direction (1: Right, -1: Left)

    Vector2 position, velocity;
    Texture2D *texture;
    Rectangle src_rect, collider_rect;
    Bullet bullet;

    Animation *current_animation;

}Player;


typedef struct {

    Vector2 health_position;
    int current_health;
    Vector2 position;
    Rectangle src_rect, collider_rect;
    Texture2D *texture;
    bool is_dead;

}Enemy;

typedef struct
{
    Texture2D* texture;
    Vector2 position;
    Rectangle collider_rect;

}NPC;

//-----------------Player related functions----------------
void setPlayerHealth(Player *player, int value);
void setPlayerPosition(Player *player, Vector2 position);
void setPlayerTexture(Player *player, Texture2D *texture, Animation *animation);
void setPlayerVelocity(Player *player, Vector2 velocity);
void movePlayer(Player *player);
Vector2 lastPositionPlayer(Player *player);
void playerOnCollisionGround(Player *player, Rectangle collider, Rectangle collision_rect);
void playerOnCollisionWall(Player *player, Rectangle collider, Rectangle collision_rect);
void playerOnCollisionPlatform(Player *player, Rectangle collider, Rectangle collision_rect);
void loadAnimation(Texture2D *texture, Animation *animation, AnimationType type);
void moveAnimation(Player *player, int *frame_counter);
void changeAnimationTo(Player *player, Animation *target);
//----------------

//----------------Enemy related functions
void setEnemyHealth(Enemy *enemy, Vector2 health_position);
void setEnemyPosition(Enemy *enemy, Vector2 position);
void setEnemyTexture(Enemy *enemy, Texture2D *texture);
void enemyAttack(Enemy *enemy, Player *player);

//NPC related functions
void setNPCPosition(NPC *npc, Vector2 position);
void setNPCTexture(NPC *npc, Texture2D *texture);



//-----------------Bullet related functions
void setBulletDamage(Bullet *bullet, int damage);
void setBulletDistance(Bullet *bullet, float distance);
void setBulletTexture(Bullet *bullet, Texture2D *texture);
void setBulletVelocity(Bullet *bullet, Vector2 velocity);
void setBulletPosition(Bullet *bullet, Vector2 position);
void setShoot(Player *player);
void shoot(Bullet *bullet);
//--------------------

//-----------------Camera related functions
void UpdatePlayerCamera(Camera2D *camera, Player *player, float screen_edge);
void clampCameraToLimits(Camera2D *camera, float screen_edge);
#endif //IP1_2VA_UTILS_H