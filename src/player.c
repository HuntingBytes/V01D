#include "utils.h"
extern Texture2D player_textures[];
extern Animation player_animations[];

//Attributes Related
void setPlayerHealth(Player *player, int value) {
    player->health = value;
}

void setPlayerPosition(Player *player, Vector2 position) {
    player->position = position;
    player->collider_rect.x = player->position.x;
    player->collider_rect.y = player->position.y;
}

void setPlayerTexture(Player *player, Texture2D *texture, Animation *animation) {
    player->texture = texture;
    player->src_rect.width = player->src_rect.height = (float)texture->height;
    player->collider_rect.width = player->collider_rect.height = (float)texture->height;
    player->current_animation = animation;
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
    player->jumping = false;
}

void playerOnCollisionWall(Player *player, Rectangle collider, Rectangle collision_rect) {
    if(lastPositionPlayer(player).x < collider.x) setPlayerPosition(player, (Vector2) {player->position.x - collision_rect.width, player->position.y});
    else setPlayerPosition(player, (Vector2) {player->position.x + collision_rect.width, player->position.y});
}

void playerOnCollisionPlatform(Player *player, Rectangle collider, Rectangle collision_rect) {
    if(collision_rect.width  > (0.6 * player->collider_rect.width ))
    {
        setPlayerPosition(player, (Vector2) {player->position.x, player->position.y - collision_rect.height + 0.1f});
        setPlayerVelocity(player, (Vector2){player->velocity.x, 0});
        player->onGround = true;
        player->jumping = false;
    }
    else
    {
        player->onGround = false;
        if (lastPositionPlayer(player).x < collider.x)
        {
            if(lastPositionPlayer(player).y > (collider.y + BLOCK_SIZE))  setPlayerPosition(player, (Vector2) {player->position.x - collision_rect.width, player->position.y});
            else setPlayerPosition(player, (Vector2){player->position.x - collision_rect.width, player->position.y});
        }
        else if((lastPositionPlayer(player).x + BLOCK_SIZE) > collider.x)
        {
            if(lastPositionPlayer(player).y > (collider.y + BLOCK_SIZE))  setPlayerPosition(player, (Vector2) {player->position.x + collision_rect.width, player->position.y});
            else setPlayerPosition(player, (Vector2) {player->position.x + collision_rect.width, player->position.y});
        }
    }
}

//Animation Related
void moveAnimation(Player *player, int *frame_counter) {
    if(*frame_counter >= (FPS/player->current_animation->frame_speed)) {
        *frame_counter = 0;
        player->current_animation->current_frame++;

        if(player->current_animation->type == JUMP) {
            if (player->current_animation->current_frame > player->current_animation->n_sprites) {
                player->current_animation->current_frame = player->current_animation->n_sprites - 1;
            }

            if(player->current_animation->current_frame >= player->current_animation->n_sprites/2 && player->velocity.y < 0.01f) {
                player->current_animation->current_frame = player->current_animation->n_sprites/2 - 1;
            }
        }
        else {
            if (player->current_animation->current_frame > player->current_animation->n_sprites) {
                player->current_animation->current_frame = 0;
            }
        }

        player->src_rect.x = (float) (player->current_animation->current_frame * player->current_animation->size_frame);
    }
}

void changeAnimationTo(Player *player, Animation *target) {
    Texture2D *texture;
    switch (target->type) {
        case IDLE: texture = &player_textures[IDLE]; break;
        case WALK: texture = &player_textures[WALK]; break;
        case JUMP: texture = &player_textures[JUMP]; break;
        case CLIMB: texture = &player_textures[CLIMB]; break;
        case DIE: texture = &player_textures[DIE]; break;
        default: texture = player->texture;
    }

    player->texture = texture;
    player->current_animation = target;
    player->current_animation->current_frame = 0;
}

void loadAnimation(Texture2D *texture, Animation *animation, AnimationType type) {
    animation->type = type;
    animation->size_frame = texture->height;
    animation->n_sprites = texture->width/animation->size_frame;
    animation->current_frame = 0;
    animation->frame_speed =  (int) ((float)animation->n_sprites*(1.5f));
}