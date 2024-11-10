#ifndef PAUSE_H
#define PAUSE_H

#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

#include <QSoundEffect>

class Pause:public Component
{
public:
    Pause(GameScene *gameScene);

    void onAttach() override;
    void onClick(QGraphicsSceneMouseEvent *ev) override;

private:
    GameScene *gameScene;
    ImageTransform *image;

    bool if_pause;

    QSoundEffect* buttonSound;
};

#endif // PAUSE_H

//暂停按钮
