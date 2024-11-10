#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QGraphicsSimpleTextItem>

#include "player.h"
#include "component.h"

class ScoreBoard:public Component
{
public:
    ScoreBoard(QString text, Player* player, int type);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

private:
    Player* player;
    Transform* transform;
    QGraphicsSimpleTextItem* textBox;

    int type;
    QString text;
};

#endif // SCOREBOARD_H

//计分板
