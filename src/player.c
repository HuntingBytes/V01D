#include "utils.h"

void setPlayerHealth(Player *player, int value) {
    player->health = value;
}

void setPlayerPosition(Player *player, Vector2 position) {
    player->collider_rect.x = player->position.x = position.x;
    player->collider_rect.y = player->position.y = position.y;
}

void setPlayerTexture(Player *player, Texture2D *texture) {
    player->texture = texture;
    player->src_rect.width = player->src_rect.height = (float)texture->height;
    player->collider_rect.width = player->collider_rect.height = (float)texture->height;
}

void setPlayerVelocity(Player *player, Vector2 velocity) {
    player->velocity.x = velocity.x;
    player->velocity.y = velocity.y;
}

void movePlayer(Player *player) {
    player->position.x += player->velocity.x;
    player->position.y += player->velocity.y;
    player->collider_rect.x = player->position.x;
    player->collider_rect.y = player->position.y;
}

Vector2 lastPositionPlayer(Player *player) {
    return (Vector2) {player->position.x - player->velocity.x, player->position.y - player->velocity.y};
}