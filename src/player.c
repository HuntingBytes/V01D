#include "includes/player.h"

//Define a vida atual do jogador
void setPlayerHealth(Player *player, int value) {
    player->health = value;
}

//Define a posicao do jogador
void setPlayerPosition(Player *player, Vector2 position) {
    player->position = position;
    player->collider_rect.x = player->position.x;
    player->collider_rect.y = player->position.y;
}

//Define a textura do jogador
void setPlayerTexture(Player *player, Texture2D *texture, Animation *animation) {
    player->texture = texture;
    player->src_rect.width = player->src_rect.height = (float)texture->height;
    player->collider_rect.width = (float) texture->height / 1.5f;
    player->collider_rect.height = (float)texture->height;
    player->current_animation = animation;
}

//Define a velocidade do jogador
void setPlayerVelocity(Player *player, Vector2 velocity) {
    player->velocity = velocity;
}

//Faz o jogador se mover (alterar sua posicao)
void movePlayer(Player *player) {
    player->position.x += player->velocity.x;
    player->position.y += player->velocity.y;
    player->collider_rect.x = player->position.x;
    player->collider_rect.y = player->position.y;
}

//Obtém a ultima posicao do jogador antes da ultima movimentacao
Vector2 lastPositionPlayer(Player *player) {
    return (Vector2) {player->position.x - player->velocity.x, player->position.y - player->velocity.y};
}

//Determina o que acontece se o jogador colidir com um chao
void playerOnCollisionGround(Player *player, Rectangle collider, Rectangle collision_rect) {
    if(player->position.y + player->collider_rect.height - collision_rect.height > collider.y) {
        setPlayerPosition(player, (Vector2) {player->position.x - collision_rect.width, player->position.y});
        player->onGround = false;
        return;
    }
    setPlayerPosition(player, (Vector2) {player->position.x, player->position.y - collision_rect.height});
    setPlayerVelocity(player, (Vector2){player->velocity.x, 0});
    player->onGround = true;
    player->jumping = false;
}

//Determina o que acontece se o jogador colidir com uma parede
void playerOnCollisionWall(Player *player, Rectangle collider, Rectangle collision_rect) {
    if(player->position.x - collision_rect.width < collider.x) setPlayerPosition(player, (Vector2) {player->position.x - collision_rect.width, player->position.y});
    else setPlayerPosition(player, (Vector2) {player->position.x + collision_rect.width, player->position.y});
}

//Determina o que acontece se o jogador colidar com uma plataforma
void playerOnCollisionPlatform(Player *player, Rectangle collider, Rectangle collision_rect) {
    if(collision_rect.width  > (0.1 * player->collider_rect.width )){
        setPlayerPosition(player, (Vector2) {player->position.x, player->position.y - collision_rect.height + 0.1f});
        setPlayerVelocity(player, (Vector2){player->velocity.x, 0});
        player->onGround = true;
        player->jumping = false;
    }
    else{
        player->onGround = false;
        if (lastPositionPlayer(player).x < collider.x) {
            if(lastPositionPlayer(player).y > (collider.y + BLOCK_SIZE))  setPlayerPosition(player, (Vector2) {player->position.x - collision_rect.width, player->position.y});
            else setPlayerPosition(player, (Vector2){player->position.x - collision_rect.width, player->position.y});
        }
        else if((lastPositionPlayer(player).x + BLOCK_SIZE) > collider.x) {
            if(lastPositionPlayer(player).y > (collider.y + BLOCK_SIZE))  setPlayerPosition(player, (Vector2) {player->position.x + collision_rect.width, player->position.y});
            else setPlayerPosition(player, (Vector2) {player->position.x + collision_rect.width, player->position.y});
        }
    }
}

