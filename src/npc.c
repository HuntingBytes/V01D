//
// Created by gabri on 10/22/2020.
//
#include "includes/npc.h"

void setNPCPosition(NPC *npc, Vector2 position)
{
    npc->position = position;
    npc->collider_rect.x = position.x;
    npc->collider_rect.y = position.y;
}

void setNPCTexture(NPC *npc, Texture2D *texture)
{
    npc->texture = texture;
    npc->collider_rect.width = (float)texture->height;
    npc->collider_rect.height = (float)texture->height;
}