//
// Created by gabri on 10/22/2020.
//

#ifndef IP1_2VA_NPC_H
#define IP1_2VA_NPC_H
#include "utils.h"

typedef struct
{
    Texture2D* texture;
    Vector2 position;
    Rectangle collider_rect;

}NPC;


void setNPCPosition(NPC *npc, Vector2 position);
void setNPCTexture(NPC *npc, Texture2D *texture);

#endif //IP1_2VA_NPC_H
