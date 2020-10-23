//
// Created by gabri on 10/22/2020.
//


#include "includes/icon.h"

extern const int screenWidth;

void UpdateIconPosition(Icon *icon, Camera2D *camera, Player *player)
{
    if(player->position.x > 0.5f*(float)screenWidth && player->position.x < 1600){
        icon->position.x = player->position.x - 0.5f*(float)screenWidth + 5.0f;
    }
}


void setIcon(Icon *icon, Texture2D *texture, Vector2 position)
{
    icon->texture = texture;
    icon->position = position;
    icon->icon_rect = (Rectangle){0, 0, (float)texture->height, (float)texture->height};
}

