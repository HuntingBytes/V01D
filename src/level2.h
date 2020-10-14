
#ifndef IP1_2VA_LEVEL2_H
#define IP1_2VA_LEVEL2_H
void startLevel2(void); //Start level2. Set initial position, load textures, etc
void inputHandlerLevel2(void); //Handle the input data according to the phase
void updateLevel2(void); //Move player and check limits of the world**(To do)
void physicsUpdateLevel2(void); //Detect and correct collisions according to its type
void renderLevel2(void); //Draw frame
void clearLevel2(void); //Clear level
#endif //IP1_2VA_LEVEL2_H
