#ifndef IP1_2VA_PLAYER_H
#define IP1_2VA_PLAYER_H

#include "utils.h"

//Funções Jogador ------------------------------
void setPlayerHealth(Player *player, int value);
void setPlayerPosition(Player *player, Vector2 position);
void setPlayerTexture(Player *player, Texture2D *texture, Animation *animation);
void setPlayerVelocity(Player *player, Vector2 velocity);
void movePlayer(Player *player);
Vector2 lastPositionPlayer(Player *player);
void playerOnCollisionGround(Player *player, Rectangle collider, Rectangle collision_rect);
void playerOnCollisionWall(Player *player, Rectangle collider, Rectangle collision_rect);
void playerOnCollisionPlatform(Player *player, Rectangle collider, Rectangle collision_rect);
//--------------------------------------------------------

#endif //IP1_2VA_PLAYER_H
