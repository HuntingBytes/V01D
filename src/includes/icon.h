//
// Created by gabri on 10/22/2020.
//

#ifndef IP1_2VA_ICON_H
#define IP1_2VA_ICON_H
#include "utils.h"


typedef struct
{
    Texture2D *texture;
    Vector2 position;
    Rectangle icon_rect;
}Icon;

void setIcon(Icon *icon, Texture2D *texture, Vector2 position);
void UpdateIconPosition(Icon *icon, Camera2D *camera, Player *player);

#endif //IP1_2VA_ICON_H
