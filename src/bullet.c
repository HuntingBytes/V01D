#include "utils.h"

void setBulletDamage(Bullet *bullet, int damage) {
    bullet->damage = damage;
}

void setBulletTexture(Bullet *bullet, Texture2D *texture) {
    bullet->texture = texture;
    bullet->collider.collider.height = (float) bullet->texture->height;
    bullet->collider.collider.width = (float) bullet->texture->width;
    bullet->collider.colliderType = TRIGGER_BULLET;
}

void setBulletVelocity(Bullet *bullet, Vector2 velocity) {
    bullet->velocity = velocity;
}

void setBulletPosition(Bullet *bullet, Vector2 position) {
    bullet->collider.collider.x = position.x;
    bullet->collider.collider.y = position.y;
}

void setShoot(Player *player) {
    player->bullet.active = false;
    player->bullet.collider.collider.x = player->position.x + player->collider_rect.width + player->bullet.collider.collider.width/2.0f;
    player->bullet.collider.collider.y = player->position.y + (player->collider_rect.height - player->bullet.collider.collider.height)/2.0f;
}

void shoot(Bullet *bullet) {
    bullet->collider.collider.x += bullet->velocity.x;
    bullet->collider.collider.y += bullet->velocity.y;
}


