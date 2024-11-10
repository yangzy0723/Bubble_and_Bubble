#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

#include <QSoundEffect>

class Instruction:public Component
{
public:
    Instruction(GameObject* gameobject);

    void onAttach() override;
    void onClick(QGraphicsSceneMouseEvent *ev) override;

private:
    ImageTransform *image;
    GameObject* gameobject;

    bool if_click;

    QSoundEffect* buttonSound;
};

#endif // INSTRUCTIONS_H

//游戏说明按钮
