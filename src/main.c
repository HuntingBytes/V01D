#include "raylib.h"

const int screenWidth = 640;
const int screenHeight = 480;

Texture2D player_asset;
Texture2D tile;

Texture2D mascara;//mudei aqui
Texture2D virado;
Rectangle teste = {200, 100, 60, 60};
Rectangle grid = {70, 35, 260, 390};
Rectangle box = {450, 35, 150, 390};
Texture2D pieces[6];
Rectangle piecesCoords[6];
struct Vector2 mousePos = {0};
int game_running = 1;

bool checkMouseCollision();
bool init(void);
bool loadAssets(void);
void update(void);
void inputHandler(void);
void close(void);
void quebraCabeca(void);
void checkPieces(Rectangle grid, Texture2D piece[]);

int main() {
    if(!init()) return  -1; 
    loadAssets();

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

    for(int i = 0; i < 6; i++){

    }
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
    quebraCabeca();
    DrawTexture(pieces[0], 400, 400, WHITE);
    EndDrawing();


}

void quebraCabeca (){
    //testa se o botão esquerda está emitindo sinal. caso sim, atualiza posição do quadrado
    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        teste.x = GetMouseX() - teste.width/2;
        teste.y = GetMouseY() - teste.height/2;
    }

    //testa para que o quadrado não saia dos limites da janela
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

    if(CheckCollisionPointRec(mousePos, teste)){
        DrawRectangleRec(teste, MAGENTA);
    }else{
        DrawRectangleRec(teste, YELLOW);
    }
    DrawTexture(mascara, 0, 0, Fade(BLACK, 0.6f));

    DrawRectangleRec(grid, Fade(WHITE, 0.5f));
    DrawRectangleLinesEx(grid,2, BLACK);
    DrawRectangleRec(box, Fade(WHITE, 0.5f));
    DrawRectangleLinesEx(box, 2, BLACK);
}
void checkPieces(Rectangle grid,Texture2D piece[]){

}

bool checkMouseCollision(Texture2D pieces[]){
    
}
void inputHandler() {
    if(WindowShouldClose()) game_running = 0;
}

void close() {
    CloseWindow();
}