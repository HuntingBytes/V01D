//
// Created by gabri on 10/22/2020.
//


#ifndef IP1_2VA_ENEMY_H
#define IP1_2VA_ENEMY_H
#include "utils.h"

typedef struct {

    Vector2 health_position;
    int current_health;
    Vector2 position;
    Rectangle src_rect, collider_rect;
    Texture2D *texture;
    bool is_dead;

}Enemy;

void setEnemyHealth(Enemy *enemy, Vector2 health_position);
void setEnemyPosition(Enemy *enemy, Vector2 position);
void setEnemyTexture(Enemy *enemy, Texture2D *texture);
void enemyAttack(Enemy *enemy, Player *player);

#endif //IP1_2VA_ENEMY_H
