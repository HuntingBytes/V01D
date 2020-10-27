#include "includes/utils.h" //Utils.h contem algumas estruturas/enum que estao sendo utilizadas na main (Player e Level)
#include "includes/animation.h" //Contem algumas funcoes relacionadas com as animacoes do nivel 2 (Podem ser reaproveitadas para o nivel 3 depois)
#include "includes/player.h" //Contem funcoes para alterar membros do Player (struct)
#include "includes/bullet.h" //Contem funcoes relacionadas com a bala

#define NUMBER_PLAYER_TEXTURES 5 //Quantidade de texturas a serem carregadas, podemos alterar se surgir uma nova

//Variaveis do Jogo----------
const int screenWidth = 640; //Uma variavel global que guarda a largura da tela, ai nao precisamos definir outra
const int screenHeight = 480; //variavel global que guarda a altura da tela
Level currentLevel; //Um enum que armazena o nivel atual (MENU, LEVEL1, LEVEL2, LEVEL3, ENDING)
bool game_running; //Booleano que indica se o jogo esta rodando
//--------------------------

//Variaveis Globais----
Player player; //Struct para representar o jogador. Nao precisa ser usada em todas as fases
Camera2D camera; //Camera global, assim nao precisamos ficar criando outras c�meras nos outros niveis
//---------------------

//Assets comuns ---------------------------------
Texture2D player_textures[NUMBER_PLAYER_TEXTURES]; //Armazena todas as texturas do jogador, assim nao precisamos ficar carregando as mesmas texturas em niveis diferentes
Animation player_animations[NUMBER_PLAYER_TEXTURES]; //Armazena todas as animacoes num vetor de struc Animation
Texture2D bullet_texture; //Armazena a textura da bala
//------------------------------------------------

//Funcoes Gerais -------
bool init(void); //Funcao que inicializa a janela e algumas variaveis
bool loadCommonResources(void); //Funcao que carrega as texturas do jogador, da bala, fonte e animacao
void initializePlayer(void); //Funcao que inicializa a struct jogador
void close(void); //Funcao que fecha a janela e descarrega as texturas usadas
void showLevelName(void );
//-------------------

//Texto dos Niveis---------------------------------
static const char txt[6][300] = {"Que sorte achar esse computador velho no sótão.\n"
                                 "Acho que é esse computador que meu pai fala tanto quando pergunto da adolescência dele.\n"
                                 "Será que isso ainda funciona?\n"
                                 "Vou tentar ligar.",
                                 "Opa, deu certo.\n"
                                 "Consegui ligar esse troço.\n"
                                 "Hã?\n"
                                 "Que tela estranha a desse computador, o brilho deve estar muito for-.\n"
                                 "Ué, que lugar é esse?\n"
                                 "Cheio de 0 e 1 por toda parte.\n"
                                 "Onde diabos eu estou?",
                                 "Consegui!\n"
                                 "Resolver esse binários foi um pouco mais difícil do que eu achei que seria.\n"
                                 "Tenho que continuar agora.\n"
                                 "Hum, eu estou me movendo pra frente mas estou voltando, será que isso é um bug no sistema desse jogo?",
                                 "Não esperava ter que deletar arquivos pra resolver uma fase como aquelas, muito menos enfrentar um boss como aqueles.\n"
                                 "Esse mundo é bem cheio de puzzles.\n"
                                 "Espero que os próximos desafios sejam mais tranquilos.",
                                 "Ato 4 - Epilogo?",
                                 "Fim do jogo."};

static int n_line_break[6] = {4, 7, 4, 3, 1, 1};
static int txt_speed[6] = {5, 4, 5, 5, 5, 5};
//------------------------------------------------

int main() {
    if(!init() || !loadCommonResources()) return -1; //Se nao foi possivel carregar as texturas/janelas, o jogo nem inicia

    initializePlayer(); //Iniciar os valores de cada membro do jogador (struct)

    //Se o jogo estiver rodando, roca a main() equivalente ao nivel atual
    while (game_running) {
        if(currentLevel != LEVEL3_2) {
            showLevelName();
        }
        switch (currentLevel) {
                case MENU:
                    mainMenu();
                    break;
                case LEVEL1:
                   mainLevel1();
                    break;
                case LEVEL2:
                    mainLevel2();
                    break;
                case LEVEL3_1:
                    mainLevel3_1();
                    break;
                case LEVEL3_2:
                    mainLevel3_2();
                    break;
                case ENDING:
                    mainEnding();
                    break;
                default:
                    break;
            }
    }

    //Uma vez que o jogo nao esteja mais rodando, podemos fechar a janela
    close();

    return 0;
}

bool init() {
    InitWindow(screenWidth, screenHeight, "V01D");
    SetTargetFPS(FPS);
    game_running = true;
    currentLevel = MENU;
    camera.target = (Vector2) {0,0};
    camera.offset = (Vector2) {0,0};
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;
    return IsWindowReady();
}

bool loadCommonResources() {
    player_textures[IDLE] = LoadTexture(PLAYER_DIR"/idle.png");
    player_textures[WALK] = LoadTexture(PLAYER_DIR"/walk.png");
    player_textures[JUMP] = LoadTexture(PLAYER_DIR"/jump.png");
    player_textures[CLIMB] = LoadTexture(PLAYER_DIR"/climb.png");
    player_textures[DIE] = LoadTexture(PLAYER_DIR"/death.png");
    bullet_texture = LoadTexture(PLAYER_DIR"/bullet.png");

    if(bullet_texture.id <= 0) return false;
    for(int i = IDLE; i < NUMBER_PLAYER_TEXTURES; i++) {
        if(player_textures[i].id <= 0) {return false;}
        loadAnimation(&player_textures[i], &player_animations[i], i);
    }

    return true;
}

void initializePlayer() {
    setPlayerHealth(&player, MAX_HEALTH);
    setPlayerPosition(&player, (Vector2){0, 0});
    setPlayerTexture(&player, &player_textures[IDLE], &player_animations[IDLE]);
    setPlayerVelocity(&player, (Vector2){0, 0});

    setBulletDamage(&player.bullet, 1);
    setBulletDistance(&player.bullet, 400.0f);
    setBulletPosition(&player.bullet, (Vector2){0,0});
    setBulletTexture(&player.bullet, &bullet_texture);
    setBulletVelocity(&player.bullet, (Vector2){5.0f,0.0f});

    player.idle = true;
    player.walking = false;
    player.jumping = false;
    player.climbing = false;
    player.onGround = false;
    player.bullet.active = false;
    player.dir = 1;
}

void close() {
    UnloadTexture(bullet_texture);
    for(int i = 0; i < NUMBER_PLAYER_TEXTURES; i++) { UnloadTexture(player_textures[i]); }
    CloseWindow();
}

void showLevelName() {
    int LENGTH = (int) TextLength(txt[currentLevel]);
    int TEXT_SPEED = txt_speed[currentLevel];
    int frame_counter = 0;
    bool finished = false;

    float x_offset = 30;
    float width = (float)screenWidth - 2*x_offset;
    float n_line = 3.0f + (float)n_line_break[currentLevel] + (float)MeasureText(txt[currentLevel], 24)/width;
    float y_offset = ((float)screenHeight - 2*n_line*(float)MeasureText("A", 24))/2.0f;
    float height = (float)screenHeight - 2*y_offset;

    Rectangle txt_rect = (Rectangle) {x_offset,
                                      y_offset,
                                      width,
                                      height};

    if(currentLevel == ENDING) {
        txt_rect.x = (float)(screenWidth - MeasureText(txt[currentLevel], 24)) / 2.0f;
        txt_rect.y = (float)(screenHeight - MeasureText("A", 32)) / 2.0f;
    }

    while (!finished) {
        if(WindowShouldClose()) {
            game_running = false;
            return;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        frame_counter++;
        DrawTextRec(GetFontDefault(),
                    TextSubtext(txt[currentLevel], 0,frame_counter / TEXT_SPEED),
                    txt_rect, 24.0f, 1.0f, true, WHITE);

        if (frame_counter / TEXT_SPEED > LENGTH + 2) {
            frame_counter = 0;
            finished = true;
        }
        EndDrawing();
    }
}