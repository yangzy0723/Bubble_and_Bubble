#include "instructions.h"

Instruction::Instruction(GameObject* gameobject)
{
    this -> gameobject = gameobject;
    this -> if_click = 0;

    this -> buttonSound = new QSoundEffect();
    this -> buttonSound -> setSource(QUrl::fromLocalFile(":/sound/sound/buttonSound.wav"));
    this -> buttonSound -> setVolume(1.0f);
}

void Instruction::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    image -> setImage(":/image/image/instructionsbutton.png");
    image -> setPos(QPointF(880,575));
    image -> setAlignment(Qt::AlignCenter);
}

void Instruction::onClick(QGraphicsSceneMouseEvent *ev)
{
    this -> buttonSound -> play();

    if(if_click)
    {
        image -> setImage(":/image/image/instructionsbutton.png");
        gameobject->getComponent<ImageTransform>()->setImage(":/image/image/gamestart.png");
        if_click = 0;
    }
    else
    {
        image -> setImage(":/image/image/back.png");
        gameobject->getComponent<ImageTransform>()->setImage(":/image/image/instructions.png");
        if_click = 1;
    }
}
