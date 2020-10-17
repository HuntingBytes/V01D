#include "utils.h"

//Attributes Related
void setPlayerHealth(Player *player, int value) {
    player->health = value;
}

void setPlayerPosition(Player *player, Vector2 position) {
    player->position = position;
    player->collider_rect.x = player->position.x;
    player->collider_rect.y = player->position.y;
}

void setPlayerTexture(Player *player, Texture2D *texture) {
    player->texture = texture;
    player->src_rect.width = player->src_rect.height = (float)texture->height;
    player->collider_rect.width = player->collider_rect.height = (float)texture->height;
}

void setPlayerVelocity(Player *player, Vector2 velocity) {
    player->velocity = velocity;
}

//Collision Related
void movePlayer(Player *player) {
    player->position.x += player->velocity.x;
    player->position.y += player->velocity.y;
    player->collider_rect.x = player->position.x;
    player->collider_rect.y = player->position.y;
}

Vector2 lastPositionPlayer(Player *player) {
    return (Vector2) {player->position.x - player->velocity.x, player->position.y - player->velocity.y};
}

void playerOnCollisionGround(Player *player, Rectangle collider, Rectangle collision_rect) {
    setPlayerPosition(player, (Vector2) {player->position.x, player->position.y - collision_rect.height});
    setPlayerVelocity(player, (Vector2){player->velocity.x, 0});
    player->onGround = true;
}

void playerOnCollisionWall(Player *player, Rectangle collider, Rectangle collision_rect) {
    if(lastPositionPlayer(player).x < collider.x) setPlayerPosition(player, (Vector2) {player->position.x - collision_rect.width, player->position.y});
    else setPlayerPosition(player, (Vector2) {player->position.x + collision_rect.width, player->position.y});
}

void playerOnCollisionPlatform(Player *player, Rectangle collider, Rectangle collision_rect) {
    if(lastPositionPlayer(player).x < collider.x) setPlayerPosition(player, (Vector2) {player->position.x - collision_rect.width, player->position.y});
    else setPlayerPosition(player, (Vector2) {player->position.x + collision_rect.width, player->position.y});
    player->onGround = true;
}

void playerOnCollisionLadder(Player *player, Rectangle collider) {} //TODO

//Animation Related