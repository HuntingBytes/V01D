#include "utils.h"
extern const int screenWidth;
extern const int screenHeight;

void UpdatePlayerCamera(Camera2D *camera, Player *player, float screen_edge) {
    camera->target.x = player->position.x;
    camera->offset = (Vector2) {0.5f*(float)screenWidth, 0};
    clampCameraToLimits(camera, screen_edge);
}

void UpdateIconPosition(Icon *icon, Camera2D *camera, Player *player)
{
    if(player->position.x > 0.5f*(float)screenWidth && player->position.x < 1600){
        icon->position.x = player->position.x - 0.5f*(float)screenWidth + 5.0f;
    }

}

void clampCameraToLimits(Camera2D *camera, float screen_edge) {
    if (camera->target.x - camera->offset.x < 0) {
        camera->target.x = camera->offset.x;
    }

    if ((camera->target.x - camera->offset.x) + (float) screenWidth > screen_edge) {
        camera->target.x = screen_edge - (float) screenWidth + camera->offset.x;
    }
}