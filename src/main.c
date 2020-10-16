#include "raylib.h"

const int screenWidth = 640;
const int screenHeight = 480;

Texture2D player_asset;
Texture2D tile;
Texture2D mascara;
Texture2D virado;
Rectangle teste = {200, 100, 60, 60};
Rectangle grid = {70, 35, 260, 390};
Rectangle box = {450, 35, 150, 390};
Texture2D pieces[6];
Rectangle coords[6];

struct Vector2 mousePos = {0};

int game_running = 1;

bool init(void);
bool loadAssets(void);
void update(void);
void inputHandler(void);
void close(void);
void puzzle(void);
void checkPieces();
void checkMouse(void);
void initPieces(void);

int main() {
    if(!init()) return  -1; 
    loadAssets();
    initPieces();
    while (game_running)
    {
        inputHandler();
        update();
    }

    close();
    return 0;
}

bool loadAssets() {
    player_asset = LoadTexture("assets/player/Dude_Monster_Attack1_4.png");
    player_asset.height = (int)(player_asset.height*1.5);
    player_asset.width = (int)(player_asset.width*1.5);
    tile = LoadTexture("assets/maps/level2/phase1/final.png");

    virado = LoadTexture("assets/player/Dude_Monster_Climb_4.png");
    virado.height = (int)(virado.height*1.5);
    virado.width = (int)(virado.width*1.5);

    mascara = LoadTexture("assets/maps/level2/phase1/final.png");
    pieces[0] = LoadTexture("assets/puzzle/01.jpg");
    pieces[1] = LoadTexture("assets/puzzle/02.jpg");
    pieces[2] = LoadTexture("assets/puzzle/03.jpg");
    pieces[3] = LoadTexture("assets/puzzle/04.jpg");
    pieces[4] = LoadTexture("assets/puzzle/05.jpg");
    pieces[5] = LoadTexture("assets/puzzle/06.jpg");

    return  true;
}

bool init() {
    InitWindow(screenWidth, screenHeight, "Teste");
    SetTargetFPS(60);
    return IsWindowReady();
}

void update() {
    mousePos = GetMousePosition();

    BeginDrawing();
    ClearBackground(WHITE);
    DrawTexture(tile, 0, 0, WHITE);
    DrawTexture(player_asset, 10, 145, WHITE);
    DrawTexture(virado, 200, 200, WHITE);
    /*if(CheckCollisionPointRec(mousePos, teste)){
        DrawRectangleRec(teste, MAGENTA);
    }else{
        DrawRectangleRec(teste, YELLOW);
    }*/
    puzzle();

    EndDrawing();


}

void puzzle (){
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
        DrawTexture(pieces[i], coords[i].x, coords[i].y, WHITE);
        DrawRectangleLinesEx(coords[i], 2, BLACK);
    }
}

void checkMouse(){
    int i;
    //este for serve para mover as peças, atualizando a posição dos retângulos que as representam
    //com estas coordenadas, ele desenha as peças na tela
    //PROBLEMA: a função está detectando o mouse passando por cima de outros quadrados e agrupando na mesma coordenada
    for(i = 0; i < 6; i++){
        //testa se o botão esquerda está emitindo sinal. caso sim, atualiza posição do retangulo
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, coords[i])) {
            coords[i].x = GetMouseX() - coords[i].width / 2;
            coords[i].y = GetMouseY() - coords[i].height / 2;
        }
            //if(CheckCollisionPointRec(mousePos, coords[i])){
                //DrawRectangleRec(piecesCoords, MAGENTA);
                //DrawTexture(pieces[i], coords[i].x, coords[i].y, WHITE);
            //}else{
                //DrawRectangleRec(piecesCoords, YELLOW);
                //DrawTexture(pieces[i], coords[i].x, coords[i].y, WHITE);
            //}
    }

    //testa para que o quadrado/retângulo não saia dos limites da janela
    if(teste.x + teste.width >= GetScreenWidth()){
        teste.x = GetScreenWidth() - teste.width;
    }else if(teste.x < 0){
        teste.x = 0;
    }
    if(teste.y + teste.height >= GetScreenHeight()){
        teste.y = GetScreenHeight() - teste.height;
    }else if(teste.y < 0){
        teste.y = 0;
    }
}

void initPieces (){
    int i, j = 45;

    for(i = 0; i < 6; i++){
        coords[i].height = coords[i].width = 130;
        if(i % 2 == 0){
            coords[i].x = 460 - 5;
        }else{
            coords[i].x = 460 + 5;
        }

        coords[i].y = j;
        j = j + 45;
    }
}

void inputHandler() {
    if(WindowShouldClose()) game_running = 0;
}

void close() {
    CloseWindow();
}