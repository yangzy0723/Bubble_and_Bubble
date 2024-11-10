#ifndef PLAYER_H
#define PLAYER_H

#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

class Player:public Component
{
public:
    Player(int ypos, int xpos, int type, GameScene *gameScene);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

    void set_bomb();
    void bomb_plus();
    void bomb_recover();
    void bombrange_plus();
    int get_bombrange();

    int get_score();
    void score_plus(int score);

    int get_health();
    void be_attacked();

    bool check();

protected:
    GameScene *gameScene;
    ImageTransform* image;

    int xPos;
    int yPos;
    int type;
    int score;
    int health;
    int bomb_num;
    int bomb_sum;
    int bomb_range;
    int abilityPushBombTime;
    int abilityUnmatched;
};

#endif // PLAYER_H

//player自动挂载了障碍物属性和可破坏属性
