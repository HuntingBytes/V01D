#include "raylib.h"

extern const int screenWidth;
extern const int screenHeight;

typedef struct {
    Vector2 vetor;
    Rectangle retang;
}NovoRec;

int main(void)
{
    
    InitWindow(screenWidth, screenHeight, "Menu");
    
    //Declaração de variáveis
    Vector2 mousePosition = { -100.0f, -100.0f };
    Vector2 diskPosition = {175, 360};
    Rectangle entrada = {330, 353, 60, 7};
    Rectangle button = {400, 348, 16, 16};
    NovoRec rec_hand;
    NovoRec rec_disk;
    Color colorEntrada = RED;
    Color colorButton = RED;

    //Inicialização das texturas
    Texture2D background = LoadTexture("C:/Users/joaop/Desktop/IP1-2VA/assets/maps/menu/menu_background.png");
    Texture2D cursor = LoadTexture("C:/Users/joaop/Desktop/IP1-2VA/assets/maps/menu/hand.png");
    Texture2D disk = LoadTexture("C:/Users/joaop/Desktop/IP1-2VA/assets/maps/menu/disk.png");
    Texture2D pointerHand = LoadTexture("C:/Users/joaop/Desktop/IP1-2VA/assets/maps/menu/pointer-hand-def.png");
    Texture2D hand = cursor;
    
    //Loop principal do jogo
    while(!WindowShouldClose())
    {
        //atualizando os valores das variáveis de posição da mão e do retânuglo
        mousePosition = GetMousePosition();
        rec_hand.vetor = GetMousePosition();
        rec_hand.retang = (struct Rectangle){rec_hand.vetor.x, rec_hand.vetor.y, cursor.width, cursor.height};
        
        //setando a posição do retânuglo do disquete
        rec_disk.retang = (struct Rectangle) {diskPosition.x, diskPosition.y, disk.width, disk.height};
        
        //checagem de colsião só na maciota entre mão e disco
        if (CheckCollisionRecs(rec_hand.retang, rec_disk.retang) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) 
        {
            rec_disk.retang.x = diskPosition.x;
            rec_disk.retang.y = diskPosition.y;
            
            diskPosition.x = rec_hand.vetor.x;
            diskPosition.y = rec_hand.vetor.y;
            
            //checando se a mão tocou no buraco do disquete pra soltar o disquete 
            if (CheckCollisionRecs(rec_disk.retang, entrada))
            {
                diskPosition.x = -50;
                diskPosition.y = -50;  
                
                colorEntrada = GREEN;
                colorButton = YELLOW;
                hand = pointerHand;              
            }
        }
        
        if (CheckCollisionRecs(rec_hand.retang, button) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            colorButton = GREEN;
            colorEntrada = BLANK;
        }
     
        //AQUI É OS DESENHO

        BeginDrawing();       

        ClearBackground(RAYWHITE);

        HideCursor();
        DrawTexture(background, 0, 0, WHITE);
        DrawRectangleRec(entrada, colorEntrada);
        DrawRectangleRec(button, colorButton); 
        DrawTexture(disk, diskPosition.x, diskPosition.y, WHITE);
        DrawTexture(hand, mousePosition.x, mousePosition.y, WHITE); 
      
        EndDrawing();
    }
    
    return 0;
}