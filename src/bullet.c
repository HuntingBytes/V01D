#include "includes/bullet.h"

//Define o dano que essa bala da em um inimigo
void setBulletDamage(Bullet *bullet, int damage) {
    bullet->damage = damage;
}

//Define a distancia maxima que a bala pode percorrer
void setBulletDistance(Bullet *bullet, float distance) {
    bullet->distance = distance;
    bullet->current_distance = 0.0f;
}

//Define a textura para a bala
void setBulletTexture(Bullet *bullet, Texture2D *texture) {
    bullet->texture = texture;
    bullet->collider.collider.height = (float) bullet->texture->height;
    bullet->collider.collider.width = (float) bullet->texture->width;
    bullet->collider.colliderType = TRIGGER_BULLET;
}

//Define a velocidade da bala
void setBulletVelocity(Bullet *bullet, Vector2 velocity) {
    bullet->velocity = velocity;
}

//Define a posicao atual da bala
void setBulletPosition(Bullet *bullet, Vector2 position) {
    bullet->collider.collider.x = position.x;
    bullet->collider.collider.y = position.y;
}

//Realiza alguns calculos para deixar a bala pronta para o proximo tiro
void setShoot(Player *player) {
    player->bullet.current_distance = 0.0f;
    player->bullet.active = false;

    if(player->dir < 0) {
        player->bullet.collider.collider.x = player->position.x - player->bullet.collider.collider.width;
    }
    else if(player->dir > 0) {
        player->bullet.collider.collider.x = player->position.x + player->collider_rect.width;
    }

    player->bullet.collider.collider.y = player->position.y + (player->collider_rect.height - player->bullet.collider.collider.height)/2.0f;
    setBulletVelocity(&player->bullet, (Vector2) {(player->dir)*fabsf(player->bullet.velocity.x), player->bullet.velocity.y});
}

//Faz a bala se mover uma vez que tenha sido atirada
void shoot(Bullet *bullet) {
    bullet->collider.collider.x += bullet->velocity.x;
    bullet->collider.collider.y += bullet->velocity.y;
    bullet->current_distance += sqrtf(powf(bullet->velocity.x, 2) + powf(bullet->velocity.y, 2));
    if(bullet->current_distance >= bullet->distance) {
        bullet->active = false;
        bullet->current_distance = 0.0f;
    }
}