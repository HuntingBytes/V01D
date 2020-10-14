#ifndef IP1_2VA_PLAYER_H
#define IP1_2VA_PLAYER_H

#define MAX_HEALTH 4

typedef struct {
    bool idle, walking, jumping, onGround;
    int health;
    Vector2 position, velocity;
    Texture2D *texture;
    Rectangle src_rect, collider_rect;
}Player;

void setPlayerHealth(Player *player, int value);
void setPlayerPosition(Player *player, Vector2 position);
void setPlayerTexture(Player *player, Texture2D *texture);
void setPlayerVelocity(Player *player, Vector2 velocity);
void movePlayer(Player *player);
Vector2 lastPositionPlayer(Player *player);

#endif //IP1_2VA_PLAYER_H
