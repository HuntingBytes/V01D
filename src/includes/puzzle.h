#ifndef IP1_2VA_PUZZLE_H
#define IP1_2VA_PUZZLE_H

//#include "utils.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

typedef struct {
    Texture2D mascara;
    Rectangle grid;
    Rectangle box;
    Texture2D pieces[6];
    Rectangle coords[6];
    struct Vector2 mousePos;
    int v[6];
}Puzzle;

void allocatePuzzle(void);
void deallocatePuzzle(void);
bool complete(void);
void loadTextures(void);
void callPuzzle(void);
void checkPieces(void);
void checkMouse(void);
void initPieces(void);
void random(void);
void fim(void);
void piecesColl(int i);

#endif //IP1_2VA_PUZZLE_H