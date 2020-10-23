#ifndef IP1_2VA_UTILS_H
#define IP1_2VA_UTILS_H

#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define FPS 60 //Define quantos fps o jogo deve rodar

#define BLOCK_SIZE 48 //Define o tamanho padrao de um tile do cenario
#define MAX_HEALTH 4 //Define a vida maxima do jogador

#define FONT_DIR "assets/fonts" //Define a pasta das fontes
#define PLAYER_DIR "assets/player" //Define a pasta dos assets do jogador
#define AUDIO_DIR "assets/audio" //Define a pasta dos arquivos de som
#define MAPS_DIR "assets/maps" //Define a pasta das imagens
#define ENEMY_DIR "assets/enemies"
#define NPC_DIR "assets/npc"

typedef enum {MENU = 0, LEVEL1, LEVEL2, LEVEL3_1, LEVEL3_2, ENDING} Level; //Uma outra forma de representar os niveis (ex:. no lugar de 0, escrevemos MENU)
typedef enum {GROUND = 0, WALL, PLATFORM, TRIGGER_SIGN, TRIGGER_LADDER, TRIGGER_BULLET} ColliderType; //Uma forma de diferenciar os diferentes tipos de colisores
typedef enum {IDLE = 0, WALK, JUMP, CLIMB, DIE} AnimationType; //Uma forma de diferenciar as diferentes animacoes

typedef struct {
    AnimationType type; //Armazena qual o tipo da animacao
    int size_frame; //Armazena o tamanho de um quadro
    int n_sprites; //Armazena quantos quadros possui
    int current_frame; //Armazena o quadro atual
    int frame_speed; //Armazena a velocidade de animacao
}Animation;

typedef struct {
    Rectangle collider; //Retangulo que delimita o colisor
    ColliderType colliderType; //Tipo de colisor
}Collider2D;

typedef struct {
    bool active; //Indica se a bala esta ativada (i. e., foi atirada)
    int damage; //Indica o dano que essa bala aplica
    float distance, current_distance; //Armazena a distancia maxima e atual da bala
    Texture2D *texture; //Armazena a textura da bala
    Collider2D collider; //Armazena o colisor da bala
    Vector2 velocity; //Armazena a velocidade da bala
}Bullet;

typedef struct {
    bool idle, walking, jumping, climbing, onGround; //Booleanos para checar uma informacao sobre o jogador
    int health; //Quantidade de vida atual
    float dir; //-1 or 1 : Direction (1: Right, -1: Left)
    Vector2 position, velocity; //Posicao e velocidade do jogador
    Texture2D *texture; //Texura atual do jogador
    Rectangle src_rect, collider_rect; //Retangulos usados para animacao e colisao
    Bullet bullet; //Uma bala
    Animation *current_animation; //Ponteiro para a animacao atual
}Player;

//Main de cada Nivel ---------
void mainMenu(void);
void mainLevel1(void);
void mainLevel2(void);
void mainLevel3_1(void);
void mainLevel3_2(void);
void mainEnding(void);
//----------------------

#endif //IP1_2VA_UTILS_H
