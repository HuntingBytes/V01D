#ifndef IP1_2VA_STARTPUZZLE
#define IP1_2VA_STARTPUZZLE

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool complete(void);
void loadTextures(void);
void callPuzzle(void);
void checkPieces(void);
void checkMouse(void);
void initPieces(void);
void random(void);
void fim();
void piecesColl(int i);

#endif