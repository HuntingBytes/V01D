#ifndef IP1_2VA_LEVEL3_1_H
#define IP1_2VA_LEVEL3_1_H

#include "utils.h"
#include "animation.h"
#include "player.h"
#include "camera.h"
#include "bullet.h"
#include "puzzle.h"

typedef struct {
    Texture2D *bg; //Ponteiro para textura do fundo (cenario)
    Collider2D *colliders; //Ponteiro para todos os colisores do cenario
    size_t *colliders_length; //Quantidade de colisores existentes no cenario
    char *chest_text; //Texto que deve ser mostrado na placa
    bool ladder_colliding; //Indica se o jogador colide com a escada
    bool levelFinished; //Indica se o nivel foi terminado (Assim a main.c pode passar para o poximo)
    bool isPuzzleOn;
    bool isNearChest;
    float invert_factor; //Usado para a inversao dos controles na parte 1
    int frame_counter; //Utilizada para as animacoes (quantos frames passaram)
    int current_ground; //Usada para saber se o jogador saiu do chao (fazer ele cair)
    float deltaTime; //Representa quanto tempo passou desde o ultimo "frame"
}Level3_1;

static void initLevel(void);
static void inputHandler(void);
static void update(void);
static void physicsUpdate(void);
static void draw(void);
static void clearLevel(void);
#endif //IP1_2VA_LEVEL3_1_H
