#ifndef IP1_2VA_LEVEL2_H
#define IP1_2VA_LEVEL2_H

#include "utils.h"
#include "animation.h"
#include "player.h"
#include "camera.h"
#include "bullet.h"

typedef struct {
    Texture2D *bg;
    Collider2D *colliders;
    size_t *colliders_length;
    char *file_name;
    char *sign_text;
    bool transition;
    bool sign_colliding;
    bool ladder_colliding;
    bool levelFinished;
    float invert_factor;
    float duration;
    float alpha;
    int frame_counter;
    int current_ground;
    float deltaTime;
}Level2;

//Funções Nível --------------------------------
static void startLevel2(void); //Start level2. Set initial position, load textures, etc
static void setupPhase1(void);
static void setupPhase2(void);
static void inputHandlerLevel2(void); //Handle the input data according to the phase
static void updateLevel2(void); //Move player and check limits of the world**(To do)
static void physicsUpdateLevel2(void); //Detect and correct collisions according to its type
static void renderLevel2(void); //Draw frame
static void clearPhase1(void); //Clear Phase1
static void clearLevel2(void); //Clear level
//--------------------------------------

#endif //IP1_2VA_LEVEL2_H
