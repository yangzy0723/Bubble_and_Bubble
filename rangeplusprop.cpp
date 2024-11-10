#include "rangeplusprop.h"

RangePlusProp::RangePlusProp(QPointF pos)
{
    this -> set_pos = pos;
}

void RangePlusProp::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    image -> setPos(set_pos);
    image -> setAlignment(Qt::AlignCenter);
    image -> setImage(":/image/image/rangeplusprop.png");
}

void RangePlusProp::onUpdate(float deltaTime)
{

}

void RangePlusProp::bepicked()
{
    destory(this->gameObject);
}
