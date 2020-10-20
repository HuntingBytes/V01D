#ifndef IP1_2VA_BULLET_H
#define IP1_2VA_BULLET_H

#include "utils.h"

//Funcoes Bala ------------------------------------------
void setBulletDamage(Bullet *bullet, int damage);
void setBulletDistance(Bullet *bullet, float distance);
void setBulletTexture(Bullet *bullet, Texture2D *texture);
void setBulletVelocity(Bullet *bullet, Vector2 velocity);
void setBulletPosition(Bullet *bullet, Vector2 position);
void setShoot(Player *player);
void shoot(Bullet *bullet);
//------------------------------------------------------

#endif //IP1_2VA_BULLET_H
