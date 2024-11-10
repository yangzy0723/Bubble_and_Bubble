#ifndef BOMB_H
#define BOMB_H

#include "player.h"
#include "component.h"
#include "transform.h"
#include "gameobject.h"

#include <QSoundEffect>

class Bomb:public Component
{
public:
    Bomb(QPointF pos, int range, Player* owner, GameScene *gameScene);

    void onAttach() override;
    void onUpdate(float deltaTime) override;
    int get_bomb_range();
private:
    Player* owner;
    GameScene *gameScene;
    ImageTransform* image;

    int range;
    int count;
    int timeToLive;
    QPointF set_pos;

    QSoundEffect* bombExplode;
};

#endif // BOMB_H

//bomb自动挂载了障碍物属性
