#include "utils.h"

void setEnemyHealth(Enemy *enemy, Vector2 health_position)
{
    enemy->health_position.x = health_position.x;
    enemy->health_position.y = health_position.y;
    enemy->current_health = 5;
    enemy->is_dead = false;
}
void setEnemyPosition(Enemy *enemy, Vector2 position)
{
    enemy->position = position;
    enemy->collider_rect.x = position.x;
    enemy->collider_rect.y = position.y;
}
void setEnemyTexture(Enemy *enemy, Texture2D *texture)
{
    enemy->texture = texture;
    enemy->src_rect.width = enemy->collider_rect.width = (float)texture->height;
    enemy->src_rect.height = enemy->collider_rect.height = (float)texture->height;
}

void enemyAttack(Enemy *enemy, Player *player)
{
    if(CheckCollisionRecs(enemy->collider_rect, player->collider_rect))
    {
        player->position.x = player->position.x - 30 * player->velocity.x;
        player->health--;
    }
}


















/*
void enemyRespawn(Enemy *enemy)
{
    if(checkRespawn())
    {
        setEnemyPosition(enemy, (Vector2){enemy->position.x, enemy->position.y});
    }
}

bool checkRespawn(Enemy *enemy, Player *player)
{
    Vector2 new_position;

    //Check if player is on the Enemy Territory
    if( (player->position.x > (float)BLOCK_SIZE * 24.73f) && (player->position.x < 1890))
    {

        if (player->onGround)
        {
            new_position = lastPositionPlayer(player);
            //sleep();
            enemy->position.x = new_position.x;
            enemy->position.y = new_position.y;
            return true;
        }
        else return false;
    }
    return false;
}
*/
