#ifndef IP1_2VA_ANIMATION_H
#define IP1_2VA_ANIMATION_H

#include "utils.h"

//Funcoes -----------------------------------------------------------------------
void loadAnimation(Texture2D *texture, Animation *animation, AnimationType type);
void moveAnimation(Player *player, int *frame_counter);
void changeAnimationTo(Player *player, Animation *target);
//------------------------------------------------------------------------------

#endif //IP1_2VA_ANIMATION_H
