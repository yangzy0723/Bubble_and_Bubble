#include "pushprop.h"

PushProp::PushProp(QPointF pos)
{
    this -> set_pos = pos;
}

void PushProp::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    image -> setPos(set_pos);
    image -> setAlignment(Qt::AlignCenter);
    image -> setImage(":/image/image/pushprop.png");
}

void PushProp::onUpdate(float deltaTime)
{

}

void PushProp::bepicked()
{
    destory(this->gameObject);
}
