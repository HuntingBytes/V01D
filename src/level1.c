#include "includes/utils.h"

//Definição tamanho da tela
extern const int screenWidth;
extern const int screenHeight;
extern Level currentLevel;
extern bool game_running;
extern Camera2D camera;

//Struct para os retângulos de colisão
typedef struct {
    Vector2 vetor;
    Rectangle retang;

}RecCollider;

//Struct para o jogador
typedef struct {
    bool idle, walking, jumping, onGround;
    Vector2 position, velocity;
    Texture2D *texture;
    Rectangle src_rect, collider_rect;
}PlayerLvl1;

//Função para limitar movimento da câmera nas extremidades
void clampCameraToLimitsLvl1(Camera2D *camera1, float screen_edge) {
    if (camera1->target.x - camera1->offset.x < 0) {
        camera1->target.x = camera1->offset.x;
    }

    if ((camera1->target.x - camera1->offset.x) + (float) screenWidth > screen_edge) {
        camera1->target.x = screen_edge - (float) screenWidth + camera1->offset.x;
    }
}

//função para colisão de Livro
void BookColision(RecCollider recGlitch, RecCollider recBook, bool *boolBook){
    if(CheckCollisionRecs(recGlitch.retang, recBook.retang))
    {
        if(IsKeyPressed(KEY_SPACE)) {*boolBook = true;}
    } else {*boolBook = false;}
}

//função para colisão dos espaços vazios
void recColision(RecCollider recGlitch, RecCollider recRec, bool *boolRec){
    if(CheckCollisionRecs(recGlitch.retang, recRec.retang))
    {
        if(IsKeyPressed(KEY_SPACE))
        {
            *boolRec = true;
        }
    } else {*boolRec = false;}
}

//Função para atualizar a câmera
void UpdatePlayerCameraLvl1(Camera2D *camera1, PlayerLvl1 *player, float screen_edge) {
    camera1->target.x = player->position.x;
    camera1->offset = (Vector2) {0.5f*(float)screenWidth, 0};
    clampCameraToLimitsLvl1(camera1, screen_edge);
}

//Função Principal
void mainLevel1 ()
{
    int velocidade = 5; //Define velocidade de movimento

    //Bool para término do nível
    bool lvl1_End = false;


    //Declaração de variável tipo Player
    PlayerLvl1 glitch;
    glitch.position = (struct Vector2){5, 380};

    //Declarando os retângulos responsáveis por colisão
    RecCollider recBook, recBook1, recBook2, recAviso, recFalso1, recFalso2, recEasterEgg;
    RecCollider recGlitch;
    RecCollider recrec1, recrec2, recrec3, recrec4, recSerializador;

    //Dando posição aos livros
    recBook.vetor = (struct Vector2){100, 400};
    recAviso.vetor = (struct Vector2){400, 400};
    recFalso1.vetor = (struct Vector2){700, 400};
    recBook1.vetor = (struct Vector2){1000, 400};
    recFalso2.vetor = (struct Vector2){1400, 100};
    recEasterEgg.vetor = (struct Vector2){1800, 100};
    recBook2.vetor = (struct Vector2){2250, 400};

    //Dando posição ao vetor2 dos retângulos dos espaços vazios
    recrec1.vetor = (Vector2) {1530, 370};
    recrec2.vetor = (Vector2) {1720, 370};
    recrec3.vetor = (Vector2) {1910, 370};
    recrec4.vetor = (Vector2) {2100, 370};

    //Declaração de variável tipo Bool (apenas Testes)
    bool bool_Book = false;
    bool bool_Book1 = false;
    bool bool_Book2 = false;
    bool bool_Book_Aviso = false;
    bool bool_Book_Falso1 = false;
    bool bool_Book_Falso2 = false;
    bool bool_Easter_Egg = false;

    bool bool_rec1 = false;
    bool bool_rec2 = false;
    bool bool_rec3 = false;
    bool bool_rec4 = false;

    bool boolEnd1 = false;
    bool boolEnd2 = false;
    bool boolEnd3 = false;
    bool boolEnd4 = false;

    bool jogador_parado = true;
    bool jogador_esquerda = false;
    bool pericles = false;

    //Inicialização das texturas do background
    Texture2D texture = LoadTexture(MAPS_DIR"/level1/background1.png");
    Texture2D texture1 = LoadTexture(MAPS_DIR"/level1/background2.png");
    Texture2D texture2 = LoadTexture(MAPS_DIR"/level1/background3.png");
    Texture2D texture3 = LoadTexture(MAPS_DIR"/level1/background4.png");
    Texture2D texture4 = LoadTexture(MAPS_DIR"/level1/background5.png");
    Texture2D texture5 = LoadTexture(MAPS_DIR"/level1/background6.png");
    int contaFrameFundo = 0;

    //inicialização das demais texturas
    Texture2D jogador = LoadTexture(PLAYER_DIR"/glitch_walk.png");
    Texture2D jogadorEsquerda = LoadTexture(PLAYER_DIR"/glitchesquerda.png");
    Texture2D jogadorParado = LoadTexture(PLAYER_DIR"/glitch_parado.png");
    Texture2D jogadorParadoEsquerda = LoadTexture(PLAYER_DIR"/glitchesquerdaparado.png");
    Texture2D player = jogador;
    Texture2D book = LoadTexture(MAPS_DIR"/level1/book.png");
    Texture2D easterEgg = LoadTexture(PLAYER_DIR"/pericles.png");
    Texture2D easterEggEsquerda = LoadTexture(PLAYER_DIR"/periclesEsquerda.png");
    Texture2D periclesParado = LoadTexture(PLAYER_DIR"/periclesParado.png");
    Texture2D num0 = LoadTexture(MAPS_DIR"/level1/0.png");
    Texture2D num1 = LoadTexture(MAPS_DIR"/level1/1.png");

    Texture2D serializador;
    Texture2D text_rec1, text_rec2, text_rec3, text_rec4;

    //Inicialização da câmera
    camera.target = (Vector2){ glitch.position.x, 0 };
    camera.offset = (Vector2){ 0, 0 };
    camera.zoom = 1.0f;

    int contador = 0;
    int framesCounter = 0;
    int framesSpeed = 8;
    int currentFrame = 0;

    //Retângulos responsáveis pra detectar o sprite correto
    Rectangle frameRec = { 0.0f, 0.0f, (float)jogador.width/6, (float)jogador.height };
    Rectangle frameRecEsquerda = { 0.0f, 0.0f, (float)jogadorEsquerda.width/6, (float)jogadorEsquerda.height };
    Rectangle frameRecParado = { 0.0f, 0.0f, (float)jogadorParado.width/4, (float)jogadorParado.height };
    Rectangle frameRecParadoEsquerda = { 0.0f, 0.0f, (float)jogadorParadoEsquerda.width/4, (float)jogadorParadoEsquerda.height };

    Rectangle frameRecPericles = { 0.0f, 0.0f, (float)easterEgg.width/6, (float)easterEgg.height };
    Rectangle frameRecPericlesEsquerda = { 0.0f, 0.0f, (float)easterEggEsquerda.width/6, (float)easterEggEsquerda.height };


    //Inicialização do loop do jogo:
    while (!lvl1_End)
    {
        //Faz com que serializador altere a textura gerada
        contador++; if(contador > 20){contador=0;}
        if(contador <10) {serializador = num0;}
        else {serializador = num1;}

        //PERICLES
        if(player.id == easterEgg.id || player.id == easterEggEsquerda.id) {pericles = true;}
        else {pericles = false;}

        if(player.id == easterEgg.id) {
            if (currentFrame > 5) currentFrame = 0;
            frameRecPericles.x = (float) currentFrame * (float) easterEgg.width / 6;
        }
        if(player.id == easterEggEsquerda.id) {
            if (currentFrame > 5) currentFrame = 0;
            frameRecPericlesEsquerda.x = (float) currentFrame * (float) easterEggEsquerda.width / 6;
        }

        //---------------------------------------------------------------------------------

        //Animação do glitch
        framesCounter++;
        if (framesCounter >= (60/framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;

            if(player.id == jogador.id) {
                if (currentFrame > 5) currentFrame = 0;
                frameRec.x = (float) currentFrame * (float) jogador.width / 6;
            }

            if(player.id == jogadorParado.id){
                if (currentFrame > 3) currentFrame = 0;
                frameRecParado.x = (float)currentFrame*(float)jogadorParado.width/4;
            }

            if(player.id == jogador.id) {
                if (currentFrame > 5) currentFrame = 0;
                frameRecEsquerda.x = (float) currentFrame * (float) jogadorEsquerda.width / 6;
            }

            if(player.id == jogadorParadoEsquerda.id){
                if (currentFrame > 3) currentFrame = 0;
                frameRecParadoEsquerda.x = (float)currentFrame*(float)jogadorParadoEsquerda.width/4;
            }
        }


        //Atualização da Posição do glitch
        //------------------------------------------------------
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            glitch.position.x += (float)velocidade;
            jogador_parado = false;
            jogador_esquerda = false;
            if(player.id == jogador.id || player.id == jogadorParado.id) {
                player = jogador;
            }
            if(player.id == easterEgg.id || player.id == easterEggEsquerda.id) {player = easterEgg;}
        }

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            glitch.position.x -= (float)velocidade;
            jogador_parado = false;
            jogador_esquerda = true;
            if(player.id == jogador.id || player.id == jogadorParado.id) {
                player = jogador;
            }
            if(player.id == easterEgg.id || player.id == easterEggEsquerda.id) {player = easterEggEsquerda;}
        }

        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
        {
            glitch.position.y -= (float)velocidade;
            jogador_parado = false;
            if(player.id == jogador.id || player.id == jogadorParado.id) {
                player = jogador;
            }
        }

        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
        {
            glitch.position.y += (float)velocidade;
            jogador_parado = false;
            if(player.id == jogador.id || player.id == jogadorParado.id) {
                player = jogador;
            }
        }
        //------------------------------------------------------

        //Checando se jogador tá parado e passando assets
        if (IsKeyUp(KEY_D) && IsKeyUp(KEY_RIGHT)
            && IsKeyUp(KEY_A) && IsKeyUp(KEY_LEFT)
            && IsKeyUp(KEY_W) && IsKeyUp(KEY_UP)
            && IsKeyUp(KEY_S) && IsKeyUp(KEY_DOWN))
        {
            jogador_parado = true;
            if(player.id == jogador.id)
            {
                player = jogadorParado;
            }
        }
        //-----------------------------------------------------------


        //Limitando o glitch a se movimentar apenas dentro do cenário
        if (glitch.position.x < 0) { glitch.position.x = 0; }
        if (glitch.position.x > 2500) { glitch.position.x = 2500; }
        if (glitch.position.y < 0) { glitch.position.y = 0; }
        if (glitch.position.y > 400) { glitch.position.y = 400; }

        //Criando os retângulos, propriamente
        recBook.retang = (struct Rectangle){recBook.vetor.x, recBook.vetor.y, (float)book.width, (float)book.height};
        recAviso.retang = (struct Rectangle){recAviso.vetor.x, recAviso.vetor.y, (float)book.width, (float)book.height};
        recFalso1.retang = (struct Rectangle){recFalso1.vetor.x, recFalso1.vetor.y, (float)book.width, (float)book.height};
        recBook1.retang = (struct Rectangle){recBook1.vetor.x, recBook1.vetor.y, (float)book.width, (float)book.height};
        recFalso2.retang = (struct Rectangle){recFalso2.vetor.x, recFalso2.vetor.y, (float)book.width, (float)book.height};
        recEasterEgg.retang = (struct Rectangle){recEasterEgg.vetor.x, recEasterEgg.vetor.y, (float)book.width, (float)book.height};
        recBook2.retang = (struct Rectangle){recBook2.vetor.x, recBook2.vetor.y, (float)book.width, (float)book.height};

        recGlitch.retang = (struct Rectangle) {glitch.position.x, glitch.position.y, 71, 80};

        //Setando posição e tamanho dos retângulos dos espaços vazios
        recrec1.retang = (struct Rectangle) {recrec1.vetor.x, recrec1.vetor.y, 40, 40};
        recrec2.retang = (struct Rectangle) {recrec2.vetor.x, recrec2.vetor.y, 40, 40};
        recrec3.retang = (struct Rectangle) {recrec3.vetor.x, recrec3.vetor.y, 40, 40};
        recrec4.retang = (struct Rectangle) {recrec4.vetor.x, recrec4.vetor.y, 40, 40};
        recSerializador.retang = (struct Rectangle) {2470, 370, 40, 40};

        //Atualizando posição da câmera a cada frame
        UpdatePlayerCameraLvl1(&camera, &glitch, (float)texture.width);

        //Setando colisão dos Livros
        BookColision(recGlitch, recBook, &bool_Book);
        BookColision(recGlitch, recBook1, &bool_Book1);
        BookColision(recGlitch, recBook2, &bool_Book2);
        BookColision(recGlitch, recAviso, &bool_Book_Aviso);
        BookColision(recGlitch, recFalso1, &bool_Book_Falso1);
        BookColision(recGlitch, recFalso2, &bool_Book_Falso2);
        BookColision(recGlitch, recEasterEgg, &bool_Easter_Egg);

        if(CheckCollisionRecs(recGlitch.retang, recSerializador.retang) && IsKeyDown(KEY_SPACE))
        {
            player = serializador;
        }

        //----------------- Iniciando Desenhos --------------------------------
        BeginDrawing();

        BeginMode2D(camera);
        ClearBackground(RAYWHITE);

        //Desenhando Background
        contaFrameFundo ++;
        if(contaFrameFundo > 0) {DrawTexture(texture, 0, 0, WHITE);}
        if(contaFrameFundo > 10) {DrawTexture(texture1, 0, 0, WHITE);}
        if(contaFrameFundo > 20) {DrawTexture(texture2, 0, 0, WHITE);}
        if(contaFrameFundo > 30) {DrawTexture(texture3, 0, 0, WHITE);}
        if(contaFrameFundo > 40) {DrawTexture(texture4, 0, 0, WHITE);}
        if(contaFrameFundo > 50) {DrawTexture(texture5, 0, 0, WHITE);}
        if(contaFrameFundo > 60) {contaFrameFundo = 0;}

        //Desenhando Livros
        DrawTexture(book, (int)recBook.vetor.x, (int)recBook.vetor.y, RED);
        DrawTexture(book, (int)recBook1.vetor.x, (int)recBook1.vetor.y, GREEN);
        DrawTexture(book, (int)recBook2.vetor.x, (int)recBook2.vetor.y, WHITE);
        DrawTexture(book, (int)recAviso.vetor.x, (int)recAviso.vetor.y, SKYBLUE);
        DrawTexture(book, (int)recFalso1.vetor.x, (int)recFalso1.vetor.y, YELLOW);
        DrawTexture(book, (int)recFalso2.vetor.x, (int)recFalso2.vetor.y, YELLOW);
        DrawTexture(book, (int)recEasterEgg.vetor.x, (int)recEasterEgg.vetor.y, DARKPURPLE);

        //Retângulos para Livro e Player, respectivamente(Apagar na versão final)
        //DrawRectangleLinesEx(recBook.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recBook1.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recBook2.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recAviso.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recFalso1.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recFalso2.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recEasterEgg.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recGlitch.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recSerializador.retang, 5, ORANGE);

        //Retângulos dos espaços para 0 e 1 e Serializador
        //DrawRectangleLinesEx(recrec1.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recrec2.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recrec3.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recrec4.retang, 5, ORANGE);
        //DrawRectangleLinesEx(recSerializador.retang, 5, ORANGE);


        //pondo as texturas (0,1) nos espaços vazios
        recColision(recGlitch, recrec1, &bool_rec1);
        recColision(recGlitch, recrec2, &bool_rec2);
        recColision(recGlitch, recrec3, &bool_rec3);
        recColision(recGlitch, recrec4, &bool_rec4);

        //If's para desenho das mensagens
        if(bool_Book == true)
        {
            DrawRectangle((int)(recBook.vetor.x - 25.0f), 80, 270, 110, BLACK);
            DrawText("  Se estiver lendo isso,\nVocê está preso nessa\n     máquina Maldita!", 90, 100, 20, LIGHTGRAY);
        }

        if(bool_Book1 == true)
        {
            DrawRectangle((int)(recBook1.vetor.x - 30.0f), 80, 240, 80, BLACK);
            DrawText("Conserte os binários\n  se quiser avançar", (int)(recBook1.vetor.x - 20.0f), 100, 20, LIGHTGRAY);
        }

        if(bool_Book2 == true)
        {
            DrawRectangle((int)(recBook2.vetor.x - 30.0f), 80, 280, 60, BLACK);
            DrawText("O valor correto é 0xA7", (int)(recBook2.vetor.x - 20.0f), 100, 20, LIGHTGRAY);
        }

        if(bool_Book_Aviso == true)
        {
            DrawRectangle((int)(recAviso.vetor.x - 60.0f), 80, 350, 60, BLACK);
            DrawText("Amarelo não é uma cor confiável", (int)(recAviso.vetor.x - 50.0f), 100, 20, LIGHTGRAY);
        }

        if(bool_Book_Falso1 == true)
        {
            DrawRectangle((int)(recFalso1.vetor.x - 60.0f), 80, 280, 80, BLACK);
            DrawText("Informação importante\ntende a flutuar aqui", (int)(recFalso1.vetor.x - 50.0f), 100, 20, LIGHTGRAY);
        }

        if(bool_Book_Falso2 == true)
        {
            DrawRectangle((int)(recFalso2.vetor.x - 60.0f), 300, 280, 60, BLACK);
            DrawText("Não há pastas suspeitas", (int)(recFalso2.vetor.x - 50.0f), 320, 20, LIGHTGRAY);
        }

        if(bool_Easter_Egg == true)
        {
            DrawRectangle((int)(recEasterEgg.vetor.x - 60.0f), 300, 280, 110, BLACK);
            DrawText("Essa skin representa\no grande mestre\ndeste mundo louco", (int)(recEasterEgg.vetor.x - 50.0f), 320, 20, LIGHTGRAY);
            if(jogador_esquerda == false) { player = easterEgg; }
            else {player = easterEggEsquerda;}
            pericles = true;
        }

        //Fazendo com que espaços vazios recebam textura atual, player volte a ser glitch
        if(bool_rec1 == true && player.id != jogador.id && player.id != jogadorParado.id)
        {
            if(player.id != easterEgg.id && player.id != easterEggEsquerda.id)
            {
                text_rec1 = player;
            } else{text_rec1 = periclesParado;}

            DrawTexture(text_rec1, (int)(recrec1.vetor.x -15.0f), (int)(recrec1.vetor.y -15.0f), WHITE);
            if(text_rec1.id == num0.id) {boolEnd1 = true;}
            else {boolEnd1 = false;}
            if(player.id != easterEgg.id || player.id != easterEggEsquerda.id)
            player = jogador;
        }
        else {DrawTexture(text_rec1, (int)(recrec1.vetor.x -15.0f), (int)(recrec1.vetor.y -15.0f), WHITE);}

        if(bool_rec2 == true && player.id != jogador.id && player.id != jogadorParado.id)
        {
            if(player.id != easterEgg.id && player.id != easterEggEsquerda.id)
            {
                text_rec2 = player;
            } else{text_rec2 = periclesParado;}

            DrawTexture(text_rec2, (int)(recrec2.vetor.x -15.0f), (int)(recrec2.vetor.y -15.0f), WHITE);
            if(text_rec2.id == num0.id) {boolEnd2 = true;}
            else {boolEnd2 = false;}
            player = jogador;
        }
        else {DrawTexture(text_rec2, (int)(recrec2.vetor.x -15.0f), (int)(recrec2.vetor.y -15.0f), WHITE);}

        if(bool_rec3 == true && player.id != jogador.id && player.id != jogadorParado.id)
        {
            if(player.id != easterEgg.id && player.id != easterEggEsquerda.id)
            {
                text_rec3 = player;
            } else{text_rec3 = periclesParado;}

            DrawTexture(text_rec3, (int)(recrec3.vetor.x -15.0f), (int)(recrec3.vetor.y -15.0f), WHITE);
            if(text_rec3.id == num1.id) {boolEnd3 = true;}
            else {boolEnd3 = false;}
            player = jogador;
        }
        else {DrawTexture(text_rec3, (int)(recrec3.vetor.x -15.0f), (int)(recrec3.vetor.y -15.0f), WHITE);}

        if(bool_rec4 == true && player.id != jogador.id && player.id != jogadorParado.id)
        {
            if(player.id != easterEgg.id && player.id != easterEggEsquerda.id)
            {
                text_rec4 = player;
            } else{text_rec4 = periclesParado;}

            DrawTexture(text_rec4, (int)(recrec4.vetor.x -15.0f), (int)(recrec4.vetor.y -15.0f), WHITE);
            if(text_rec4.id == num1.id) {boolEnd4 = true;}
            else {boolEnd4 = false;}
            player = jogador;
        }
        else {DrawTexture(text_rec4, (int)(recrec4.vetor.x -15.0f), (int)(recrec4.vetor.y -15.0f), WHITE);}

        //Desenhando jogador com animação
        if(player.id == jogador.id && jogador_parado == false && jogador_esquerda == false) {DrawTextureRec(jogador, frameRec, glitch.position, WHITE); } //Andando pra Direita
        if(player.id == jogador.id && jogador_parado == false && jogador_esquerda == true) {DrawTextureRec(jogadorEsquerda, frameRecEsquerda, glitch.position, WHITE); } //Andando pra Esquerda

        if(player.id == jogadorParado.id && jogador_parado == true && jogador_esquerda == false) {DrawTextureRec(jogadorParado, frameRecParado, glitch.position, WHITE); } //Parado pra Direita
        if(player.id == jogadorParado.id && jogador_parado == true && jogador_esquerda == true) {DrawTextureRec(jogadorParadoEsquerda, frameRecParado, glitch.position, WHITE); } //Parado pra Esquerda

        if(player.id == easterEgg.id && jogador_esquerda == false) {DrawTextureRec(easterEgg, frameRecPericles, glitch.position, WHITE); } //Andando pra Direita
        if(player.id == easterEggEsquerda.id && jogador_esquerda == true) {DrawTextureRec(easterEggEsquerda, frameRecPericlesEsquerda, glitch.position, WHITE); } //Andando pra Esquerda

        if(player.id != jogador.id && player.id != jogadorParado.id && pericles == false) { DrawTexture(player, (int)glitch.position.x, (int)glitch.position.y, WHITE);} //Qualquer outro
        DrawTexture(serializador, (int)(recSerializador.retang.x - 15.0f), (int)(recSerializador.retang.y - 15.0f), WHITE);

        EndMode2D();

        if(boolEnd1 == true && boolEnd2 == true && boolEnd3 == true && boolEnd4 == true)
        {
            lvl1_End = true;
            currentLevel = LEVEL2;
        }

        if(text_rec1.id == periclesParado.id && text_rec2.id == periclesParado.id && text_rec3.id == periclesParado.id && text_rec4.id == periclesParado.id)
        {
            lvl1_End = true;
            currentLevel = LEVEL2;
        }

        EndDrawing();

        if(WindowShouldClose()){
            lvl1_End = true;
            game_running = false;
        }

        //----------------------- Finalizando Desenhos -------------------------

    }

    //Dezinicializando os assets
    UnloadTexture(texture);
    UnloadTexture(texture1);
    UnloadTexture(texture2);
    UnloadTexture(texture3);
    UnloadTexture(texture4);
    UnloadTexture(texture5);
    UnloadTexture(player);
    UnloadTexture(book);
    UnloadTexture(jogadorEsquerda);
    UnloadTexture(jogadorParado);
    UnloadTexture(jogadorParadoEsquerda);
    UnloadTexture(easterEgg);
    UnloadTexture(easterEggEsquerda);
    UnloadTexture(periclesParado);
    UnloadTexture(num0);
    UnloadTexture(num1);
}