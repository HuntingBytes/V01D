#ifndef IP1_2VA_LEVEL2_H
#define IP1_2VA_LEVEL2_H

#include "utils.h"
#include "animation.h"
#include "player.h"
#include "camera.h"
#include "bullet.h"

typedef struct {
    Texture2D *bg; //Ponteiro para textura do fundo (cenario)
    Collider2D *colliders; //Ponteiro para todos os colisores do cenario
    size_t *colliders_length; //Quantidade de colisores existentes no cenario
    char *file_name; //Nome do arquivo para a parte 1
    char *sign_text; //Texto que deve ser mostrado na placa
    char *npc_text; //Texto que deve ser mostrado no npc
    bool transition; //Indica se esta na transicao da parte 1 para parte 2 (tela ficar clara)
    bool sign_colliding; //Indica se o jogador colide com a placa
    bool npc_colliding; // Indica se o jogador colide com o npc
    //bool goto_phase3; //Indica se o jogador colide com o npc e aperta "Enter" para ir para a próxima fase;
    bool ladder_colliding; //Indica se o jogador colide com a escada
    bool levelFinished; //Indica se o nivel foi terminado (Assim a main.c pode passar para o poximo)
    float invert_factor; //Usado para a inversao dos controles na parte 1
    float duration; //Indica a duracao da transicao
    float alpha; //Usada no efeito de fade da transicao
    int frame_counter; //Utilizada para as animacoes (quantos frames passaram)
    int current_ground; //Usada para saber se o jogador saiu do chao (fazer ele cair)
    float deltaTime; //Representa quanto tempo passou desde o ultimo "frame"
}Level2;

//Funcoes Nivel --------------------------------
static void startLevel2(void); //Start level2. Set initial position, load textures, etc
static void setupPhase1(void); //Start/set phase 1
static void setupPhase2(void); //Start/set phase 2
static void inputHandlerLevel2(void); //Handle the input data according to the phase
static void updateLevel2(void); //Move player and check limits of the world**(To do)
static void physicsUpdateLevel2(void); //Detect and correct collisions according to its type
static void renderLevel2(void); //Draw frame
static void clearPhase1(void); //Clear Phase1
static void clearLevel2(void); //Clear level
//--------------------------------------

#endif //IP1_2VA_LEVEL2_H
