#include "includes/utils.h"

extern const int screenWidth;
extern const int screenHeight;
extern bool game_running;

void mainEnding() {
    Texture2D backgroundfinal = LoadTexture(MAPS_DIR"/level3/phase2/background_final.png");
    const char message[128] = "Wobbuffet was ejected.\n\n\nMoesiof\nGabriel do zap\nJohnnus\nJoao pedro\nLucas\nPudim\n\nPress('F')for exit.";

    bool ending_finished = false;

    int framesCounterfinal = 0;

    // Main game loop
    while (!ending_finished)    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        framesCounterfinal++;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(backgroundfinal, 0, 0, WHITE);
        DrawText(TextSubtext(message, 0, framesCounterfinal / 10), 210, 160, 20, WHITE);


        EndDrawing();

        if (IsKeyPressed(KEY_F) || WindowShouldClose()) {
            ending_finished = true;
            game_running = false;
        }
    }

    UnloadTexture(backgroundfinal);
}