#include "numplusprop.h"

NumPlusProp::NumPlusProp(QPointF pos)
{
    this -> set_pos = pos;
}

void NumPlusProp::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    image -> setPos(set_pos);
    image -> setAlignment(Qt::AlignCenter);
    image -> setImage(":/image/image/numplusprop.png");
}

void NumPlusProp::onUpdate(float deltaTime)
{

}

void NumPlusProp::bepicked()
{
    destory(this->gameObject);
}
