#include "includes/utils.h"

extern const int screenWidth;
extern const int screenHeight;
extern bool game_running;

void mainEnding() {
    Texture2D backgroundfinal = LoadTexture(MAPS_DIR"/ending/final.png");
    const char message[128] = "You were ejected.\n\nMoesio\nGabriel\nJoao\nJoao\nLucas\nEduardo\nPress 'F' to exit.";
    bool ending_finished = false;
    int framesCounterfinal = 0;

    if(backgroundfinal.id <= 0) {
        ending_finished = true;
        game_running = false;
        return;
    }

    while (!ending_finished)    // Detect window close button or ESC key
    {
        framesCounterfinal++;

        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(backgroundfinal, 0, 0, WHITE);
        DrawText(TextSubtext(message, 0, framesCounterfinal / 10), 242, 120, 10, WHITE);

        if(framesCounterfinal > INT_MAX - 500) framesCounterfinal = INT_MAX;

        EndDrawing();

        if (IsKeyPressed(KEY_F) || WindowShouldClose()) {
            ending_finished = true;
            game_running = false;
        }
    }

    UnloadTexture(backgroundfinal);
}