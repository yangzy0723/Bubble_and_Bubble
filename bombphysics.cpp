#include "bombphysics.h"

#include "block.h"

BombPhysics::BombPhysics()
{
    vx = 0;
    vy = 0;
    interval = 20;
    mydeltatime = 10;
    moving_time = interval;
}

void BombPhysics::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    this -> collider = dynamic_cast<QGraphicsItem*>(this -> image);
    Q_ASSERT(collider != nullptr);
}

void BombPhysics::onUpdate(float deltaTime)
{
    if(moving_time == interval)
        original_pos = image -> pos();
    if(moving_time > 0 && (vx != 0 || vy != 0))
    {
        image->moveBy(mydeltatime*vx, mydeltatime*vy);
        moving_time = moving_time - mydeltatime;
    }
    else
        moving_time = interval;
    for (auto item : this->collider->collidingItems())
    {
        while (item->parentItem() != nullptr) item = item->parentItem();
        auto transform = dynamic_cast<Transform *>(item);
        if (transform == nullptr)
            continue;
        auto gameObject = transform->getParentGameObject();
        auto block = gameObject->getComponent<Block>();
        if (block == nullptr)
            continue;
        image->setPos(original_pos);
        vx = 0;
        vy = 0;
        moving_time = interval;
        break;
    }
}

void BombPhysics::setVelocity(float vx, float vy)
{
    this -> vx = vx;
    this -> vy = vy;
}
