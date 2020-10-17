#include "raylib.h"

typedef struct {
    bool idle, walking, jumping, onGround;
    Vector2 position, velocity;
    Texture2D *texture;
    Rectangle src_rect, collider_rect;
}Player;

void setPlayerPosition(Player *player, Vector2 position) {
    player->position = position;
    player->collider_rect.x = player->position.x;
    player->collider_rect.y = player->position.y;
}

void movePlayer(Player *player) {
    player->position.x += player->velocity.x;
    player->position.y += player->velocity.y;
    player->collider_rect.x = player->position.x;
    player->collider_rect.y = player->position.y;
}

int main ()
{
    //Inicialização da tela do menu:
    const int screenWidth = 640;
    const int screenHeight = 480;

    InitWindow(screenWidth, screenHeight, "Fase 1");

    Vector2 glitchPosition = { 5, 420 };

    //Inicialização das texturas (SEMPRE DEPOIS da inicialização do Windows)
    Texture2D texture = LoadTexture("C:/Users/joaop/Desktop/IP1-2VA/assets/maps/level1/fase1.png");
    Texture2D player = LoadTexture("C:/Users/joaop/Desktop/IP1-2VA/assets/player/glitch.png");

    //Inicialização do loop do jogo:
    while (!WindowShouldClose())
    {
        //Atualização da Posição do glitch
        //------------------------------------------------------
        if (IsKeyDown(KEY_D)) glitchPosition.x += 0.08f;
        if (IsKeyDown(KEY_A)) glitchPosition.x -= 0.08f;
        if (IsKeyDown(KEY_W)) glitchPosition.y -= 0.08;
        if (IsKeyDown(KEY_S)) glitchPosition.y += 0.08f;
        //------------------------------------------------------

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawTexture(texture, 0, 0, WHITE);
            DrawTexture(player, glitchPosition.x, glitchPosition.y, WHITE);

        EndDrawing();

    }

    //Dezinicializando os assets
    UnloadTexture(texture);
    UnloadTexture(player);
    
    CloseWindow();

    return 0;

}