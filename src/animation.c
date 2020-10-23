#include "includes/animation.h"

extern Texture2D player_textures[];
extern Animation player_animations[];

//Faz a animaçao ir para o proximo frame/"imagem"
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

//Altera a animacao atual do jogador
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

//Carrega/inicializa uma animacao (Define o valor de cada um dos mebros de sua struct)
void loadAnimation(Texture2D *texture, Animation *animation, AnimationType type) {
    animation->type = type;
    animation->size_frame = texture->height;
    animation->n_sprites = texture->width/animation->size_frame;
    animation->current_frame = 0;
    animation->frame_speed =  (int) ((float)animation->n_sprites*(1.5f));
}
