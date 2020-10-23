#include "puzzle.h"
#include "utils.h"

static Puzzle *puzzle;

void allocatePuzzle() {
    puzzle = (Puzzle*) malloc(sizeof(Puzzle));
    puzzle->grid = (Rectangle){70, 35, 260, 390};
    puzzle->box = (Rectangle){450, 35, 150, 390};
    puzzle->mousePos = (Vector2){0};
    for(int i = 0; i < 6; i++) {
        puzzle->v[i] = i;
    }
}

void deallocatePuzzle() {
    UnloadTexture(puzzle->mascara);
    for(int i = 0; i < 6; i++) UnloadTexture(puzzle->pieces[i]);
    free(puzzle);
    puzzle = NULL;
}

void loadTextures() {
    puzzle->mascara = LoadTexture(MAPS_DIR"/level3/phase1/final.png");
    puzzle->pieces[puzzle->v[0]] = LoadTexture(PUZZLE_DIR"/01.jpg");
    puzzle->pieces[puzzle->v[1]] = LoadTexture(PUZZLE_DIR"/02.jpg");
    puzzle->pieces[puzzle->v[2]] = LoadTexture(PUZZLE_DIR"/03.jpg");
    puzzle->pieces[puzzle->v[3]] = LoadTexture(PUZZLE_DIR"/04.jpg");
    puzzle->pieces[puzzle->v[4]] = LoadTexture(PUZZLE_DIR"/05.jpg");
    puzzle->pieces[puzzle->v[5]] = LoadTexture(PUZZLE_DIR"/06.jpg");
}

void initPieces() {
    int i, j = 45;

    for (i = 0; i < 6; i++) {
        puzzle->coords[i].height = puzzle->coords[i].width = 130;

        if (i % 2 == 0) {
            puzzle->coords[i].x = 460 - 5;
        } else {
            puzzle->coords[i].x = 460 + 5;
        }

        puzzle->coords[i].y = (float) j;
        j = j + 45;
    }
}

void random() {
    int j, aux;
    //gera semente aleatória
    srand(time(NULL)*time(NULL));

    //embaralha os números no vetor
    for (int i = 5; i > 0; i--) {
        j = rand() % 6;
        aux = puzzle->v[j];
        puzzle->v[j] = puzzle->v[i];
        puzzle->v[i] = aux;
    }
}

void callPuzzle() {
    puzzle->mousePos = GetMousePosition();

    DrawTexture(puzzle->mascara, 0, 0, Fade(BLACK, 0.6f));
    DrawRectangleRec(puzzle->grid, Fade(WHITE, 0.5f));
    DrawRectangleLinesEx(puzzle->grid, 2, BLACK);
    DrawRectangleRec(puzzle->box, Fade(WHITE, 0.5f));
    DrawRectangleLinesEx(puzzle->box, 2, BLACK);
    checkPieces();
    checkMouse();
}

void checkPieces() {
    int i;
    //passa por cada um dos elementos do vetor de peças e imprime na tela usando as coordenadas no vetor coords
    for (i = 0; i < 6; i++) {
        DrawTexture(puzzle->pieces[i], (int) puzzle->coords[i].x, (int) puzzle->coords[i].y, WHITE);
        DrawRectangleLinesEx(puzzle->coords[i], 2, BLACK);
    }
}

void checkMouse() {
    int i;
    //este "for" serve para mover as peças, atualizando a posição dos retângulos que as representam
    //com estas coordenadas, ele desenha as peças na tela
    for (i = 0; i < 6; i++) {
        //testa se o botão esquerdo está pressionado. caso sim, atualiza posição do retangulo
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(puzzle->mousePos, puzzle->coords[i])) {
            puzzle->coords[i].x = (float) GetMouseX() - puzzle->coords[i].width / 2;
            puzzle->coords[i].y = (float) GetMouseY() - puzzle->coords[i].height / 2;
            //printf("SEGURANDO A PECA %i -- v = %i", i, v[i]);
            piecesColl(i);
        }
        //testa a posição das peças para não sairem das bordas da tela
        if (puzzle->coords[i].x + puzzle->coords[i].width >= (float) GetScreenWidth()) {
            puzzle->coords[i].x = (float) GetScreenWidth() - puzzle->coords[i].width;
        } else if (puzzle->coords[i].x < 0) {
            puzzle->coords[i].x = 0;
        }
        if (puzzle->coords[i].y + puzzle->coords[i].height >= (float) GetScreenHeight()) {
            puzzle->coords[i].y = (float) GetScreenHeight() - puzzle->coords[i].height;
        } else if (puzzle->coords[i].y < 0) {
            puzzle->coords[i].y = 0;
        }
    }
}

void piecesColl(int i) {
    //função para impedir peças de empilhar
    for (int j = 0; j < 6; j++) {
        if (j != i) {
            //move as peças caso estejam perto umas das outras "como um glitch"
            if (puzzle->coords[i].x == puzzle->coords[j].x && puzzle->coords[i].y != puzzle->coords[j].y) {
                puzzle->coords[i].x = (float) GetMouseX() - puzzle->coords[i].width / 2;
            }
            if (puzzle->coords[i].y == puzzle->coords[j].y && puzzle->coords[i].x != puzzle->coords[j].x) {
                puzzle->coords[i].y = puzzle->coords[i].height / 2;
            }
        }
    }
}

bool complete() {
    int i;
    float area = 0, limX, limY, areaMax;
    Vector2 p; //struct para armazenar ponto central da peça

    areaMax = puzzle->grid.height * puzzle->grid.width; //area maxima possivel, ou seja, area do grid total
    limX = puzzle->grid.x + 130; //marca o ponto central do grid
    limY = puzzle->grid.y + 130; //marca 1/3 do comprimento do grid

    for (i = 0; i < 6; i++) {
        p.x = puzzle->coords[puzzle->v[i]].x + puzzle->coords[puzzle->v[i]].width / 2; //armazena coordenada x da metade da peça
        p.y = puzzle->coords[puzzle->v[i]].y + puzzle->coords[puzzle->v[i]].height / 2; //armazena coordenada x da metade da peça
        if (i % 2 == 0) { //peças do lado direito
            if (p.x > puzzle->grid.x && p.x <= limX) {
                if (p.y > puzzle->grid.y && p.y < limY) {
                    //soma area das peças do lado direito
                    area += GetCollisionRec(puzzle->grid, puzzle->coords[i]).height * GetCollisionRec(puzzle->grid, puzzle->coords[i]).width;
                }
            }
        } else { //peças do lado esquerdo
            if (p.x > limX && p.x <= limX + 130) {
                if (p.y > puzzle->grid.y && p.y < limY) {
                    //soma area das peças do lado esquerdo
                    area += GetCollisionRec(puzzle->grid, puzzle->coords[i]).height * GetCollisionRec(puzzle->grid, puzzle->coords[i]).width;
                    //aumenta o limite vertical do grid a ser avaliado
                    limY += 130;
                }
            }
        }
    }

    if (area >= areaMax * 0.85) {
        return true;
    }
    return false;
}

void fim () {
    deallocatePuzzle();
    DrawRectangle(0, 0, 640, 480, RAYWHITE);
    DrawText("DALE DALE DALE", 160, 220, 30, BLACK);
}