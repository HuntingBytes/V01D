#ifndef IP1_2VA_CAMERA_H
#define IP1_2VA_CAMERA_H

#include "utils.h"

//Funções Câmera ------------------------------------------------------------
void UpdatePlayerCamera(Camera2D *camera, Player *player, float screen_edge);
void clampCameraToLimits(Camera2D *camera, float screen_edge);
//---------------------------------------------------------------------------

#endif //IP1_2VA_CAMERA_H
