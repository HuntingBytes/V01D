#include "startPuzzle.h"

Texture2D mascara;
Rectangle grid = {70, 35, 260, 390};
Rectangle box = {450, 35, 150, 390};
Texture2D pieces[6];
Rectangle coords[6];
struct Vector2 mousePos = {0};

int v[] = {0, 1, 2, 3, 4, 5};

void loadTextures(){
    mascara = LoadTexture("assets/maps/level2/phase1/final.png");
    pieces[v[0]] = LoadTexture("assets/puzzle/01.jpg");
    pieces[v[1]] = LoadTexture("assets/puzzle/02.jpg");
    pieces[v[2]] = LoadTexture("assets/puzzle/03.jpg");
    pieces[v[3]] = LoadTexture("assets/puzzle/04.jpg");
    pieces[v[4]] = LoadTexture("assets/puzzle/05.jpg");
    pieces[v[5]] = LoadTexture("assets/puzzle/06.jpg");
}

void initPieces(){
    int i, j = 45;

    for(i = 0; i < 6; i++){
        coords[i].height = coords[i].width = 130;

        if(i % 2 == 0){
            coords[i].x = 460 - 5;
        }else{
            coords[i].x = 460 + 5;
        }

        coords[i].y = (float) j;
        j = j + 45;
    }
}

void random(){
    int j, aux;
    //gera semente aleatória
    srand(time(NULL)*time(NULL));

    //embaralha os números no vetor
    for(int i = 5; i > 0; i--){
        j = rand() % 6;
        aux = v[j];
        v[j] = v[i];
        v[i] = aux;
    }
}

void callPuzzle(){
    mousePos = GetMousePosition();

    DrawTexture(mascara, 0, 0, Fade(BLACK, 0.6f));
    DrawRectangleRec(grid, Fade(WHITE, 0.5f));
    DrawRectangleLinesEx(grid,2, BLACK);
    DrawRectangleRec(box, Fade(WHITE, 0.5f));
    DrawRectangleLinesEx(box, 2, BLACK);
    checkPieces();
    checkMouse();
}

void checkPieces(){
    int i;
    //passa por cada um dos elementos do vetor de peças e imprime na tela usando as coordenadas no vetor coords
    for(i = 0; i < 6; i++){
        DrawTexture(pieces[i], (int) coords[i].x, (int) coords[i].y, WHITE);
        DrawRectangleLinesEx(coords[i], 2, BLACK);
    }
}

void checkMouse(){
    int i;
    //este "for" serve para mover as peças, atualizando a posição dos retângulos que as representam
    //com estas coordenadas, ele desenha as peças na tela
    for(i = 0; i < 6; i++){
        //testa se o botão esquerdo está pressionado. caso sim, atualiza posição do retangulo
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, coords[i])) {
            coords[i].x = (float) GetMouseX() - coords[i].width / 2;
            coords[i].y = (float) GetMouseY() - coords[i].height / 2;
            //printf("SEGURANDO A PECA %i -- v = %i", i, v[i]);
            piecesColl(i);
        }
        //testa a posição das peças para não sairem das bordas da tela
        if(coords[i].x + coords[i].width >= (float) GetScreenWidth()){
            coords[i].x = (float) GetScreenWidth() - coords[i].width;
        }else if(coords[i].x < 0){
            coords[i].x = 0;
        }
        if(coords[i].y + coords[i].height >= (float) GetScreenHeight()){
            coords[i].y = (float) GetScreenHeight() - coords[i].height;
        }else if(coords[i].y < 0){
            coords[i].y = 0;
        }
    }
}

void piecesColl(int i){
    //função para impedir peças de empilhar
    for(int j = 0; j < 6; j++){
        if(j != i){
            //move as peças caso estejam perto umas das outras "como um glitch"
            if(coords[i].x == coords[j].x && coords[i].y != coords[j].y){
                coords[i].x = (float) GetMouseX() - coords[i].width/2;
            }
            if(coords[i].y == coords[j].y && coords[i].x != coords[j].x){
                coords[i].y = coords[i].height/2;
            }
        }
    }
}

bool complete(){
    int i;
    float area = 0, limX, limY, areaMax;
    Vector2 p; //struct para armazenar ponto central da peça

    areaMax = grid.height * grid.width; //area maxima possivel, ou seja, area do grid total
    limX = grid.x + 130; //marca o ponto central do grid
    limY = grid.y + 130; //marca 1/3 do comprimento do grid

    for(i = 0; i < 6; i++){
        p.x = coords[v[i]].x + coords[v[i]].width/2;//armazena coordenada x da metade da peça
        p.y = coords[v[i]].y + coords[v[i]].height/2;//armazena coordenada x da metade da peça
        if(i % 2 == 0){//peças do lado direito
            if(p.x > grid.x && p.x <= limX){
                if(p.y > grid.y && p.y < limY){
                    //soma area das peças do lado direito
                    area += GetCollisionRec(grid, coords[i]).height * GetCollisionRec(grid, coords[i]).width;
                }
            }
        }else{//peças do lado esquerdo
            if(p.x > limX && p.x <= limX + 130){
                if(p.y > grid.y && p.y < limY){
                    //soma area das peças do lado esquerdo
                    area += GetCollisionRec(grid, coords[i]).height * GetCollisionRec(grid, coords[i]).width;
                    //aumenta o limite vertical do grid a ser avaliado
                    limY += 130;
                }
            }
        }
    }

    if(area >= areaMax*0.7){
        return true;
    }
    return false;
}

void fim (){
    BeginDrawing();
    DrawRectangle(0, 0, 640, 480, RAYWHITE);
    DrawText("DALE DALE DALE", 160, 220, 30, BLACK);
    EndDrawing();
}