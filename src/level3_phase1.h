#ifndef IP1_2VA_LEVEL3_PHASE1_H
#define IP1_2VA_LEVEL3_PHASE1_H

#include "raylib.h"
#include "startPuzzle.h"

#define BLOCK_SIZE 48
#define MAX_HEALTH 4

#define FPS 60

#define FONT_DIR "assets/fonts"
#define PLAYER_DIR "assets/player"
#define MAPS_DIR "assets/maps"

typedef enum {GROUND = 0, WALL, PLATFORM, TRIGGER_SPIKE, TRIGGER_LADDER, TRIGGER_BULLET, TRIGGER_DOOR} ColliderType;
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

void initLevel(void); //Start level2. Set initial position, load textures, etc
void inputHandler(void); //Handle the input data according to the phase
void update(void); //Move player and check limits of the world**(To do)
void physicsUpdate(void); //Detect and correct collisions according to its type
void draw(void); //Draw frame
void clearLevel(void); //Clear level

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

void setBulletDamage(Bullet *bullet, int damage);
void setBulletDistance(Bullet *bullet, float distance);
void setBulletTexture(Bullet *bullet, Texture2D *texture);
void setBulletVelocity(Bullet *bullet, Vector2 velocity);
void setBulletPosition(Bullet *bullet, Vector2 position);
void setShoot(Player *player);
void shoot(Bullet *bullet);

void UpdatePlayerCamera(Camera2D *camera, Player *player, float screen_edge);
void clampCameraToLimits(Camera2D *camera, float screen_edge);
#endif