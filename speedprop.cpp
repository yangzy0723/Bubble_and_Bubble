#include "speedprop.h"

SpeedProp::SpeedProp(QPointF pos)
{
    this -> set_pos = pos;
}

void SpeedProp::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    image -> setPos(set_pos);
    image -> setAlignment(Qt::AlignCenter);
    image -> setImage(":/image/image/speedprop.png");
}

void SpeedProp::onUpdate(float deltaTime)
{

}

void SpeedProp::bepicked()
{
    destory(this->gameObject);
}
