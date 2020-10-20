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
Camera2D camera; //Camera global, assim nao precisamos ficar criando outras câmeras nos outros niveis
Font font; //Fonte que vamos utilizar (nao precisa ser ela)
//---------------------

//Assets comuns ---------------------------------
Texture2D player_textures[NUMBER_PLAYER_TEXTURES]; //Armazena todas as texturas do jogador, assim nao precisamos ficar carregando as mesmas texturas em niveis diferentes
Animation player_animations[NUMBER_PLAYER_TEXTURES]; //Armazena todas as animacoes num vetor de struc Animation
Texture2D bullet_texture; //Armazena a textura da bala
//------------------------------------------------

//Funcoes Gerais
bool init(void); //Funcao que inicializa a janela e algumas variaveis
bool loadCommonResources(void); //Funcao que carrega as texturas do jogador, da bala, fonte e animacao
void initializePlayer(void); //Funcao que inicializa a struct jogador
void close(void); //Funcao que fecha a janela e descarrega as texturas usadas
//---------------

int main() {
    if(!init() || !loadCommonResources()) return -1; //Se nao foi possivel carregar as texturas/janelas, o jogo nem inicia

    initializePlayer(); //Iniciar os valores de cada membro do jogador (struct)

    //Se o jogo estiver rodando, roca a main() equivalente ao nivel atual
    while (game_running) {
            switch (currentLevel) {
                case MENU:
                    mainMenu();
                    break;
                case LEVEL1:
                    //mainLevel1();
                    break;
                case LEVEL2:
                    mainLevel2();
                    break;
                case LEVEL3:
                    //mainLevel3();
                    break;
                case ENDING:
                    //mainEnding();
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
    InitWindow(screenWidth, screenHeight, "Teste");
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
    font = LoadFont(FONT_DIR"/Unipix.ttf");

    player_textures[IDLE] = LoadTexture(PLAYER_DIR"/idle.png");
    player_textures[WALK] = LoadTexture(PLAYER_DIR"/walk.png");
    player_textures[JUMP] = LoadTexture(PLAYER_DIR"/jump.png");
    player_textures[CLIMB] = LoadTexture(PLAYER_DIR"/climb.png");
    player_textures[DIE] = LoadTexture(PLAYER_DIR"/death.png");
    bullet_texture = LoadTexture(PLAYER_DIR"/bullet.png");

    if(font.texture.id <= 0) return  false;
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
    UnloadFont(font);
    UnloadTexture(bullet_texture);
    for(int i = 0; i < NUMBER_PLAYER_TEXTURES; i++) { UnloadTexture(player_textures[i]); }
    CloseWindow();
}