#include "fire.h"

#include <cstdlib>
#include <QGraphicsItem>

#include "health.h"
#include "hitable.h"
#include "pushprop.h"
#include "speedprop.h"
#include "unmatched.h"
#include "numplusprop.h"
#include "rangeplusprop.h"

Fire::Fire(QPointF pos, Player *owner)
{
    timeToLive = 50;
    this -> owner = owner;
    this -> set_pos = pos;
}

void Fire::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    this -> collider = dynamic_cast<QGraphicsItem*>(this -> image);
    Q_ASSERT(collider != nullptr);
    image -> setPos(set_pos);
    image -> setAlignment(Qt::AlignCenter);
    image -> setImage(":/image/image/fire.png");
}

void Fire::onUpdate(float deltaTime)
{
    if(timeToLive <= 0)
        destory(this -> gameObject);
    else
        timeToLive = timeToLive - deltaTime;
    for (auto item : this->collider->collidingItems())
    {
        while (item->parentItem() != nullptr)
            item = item -> parentItem();
        auto transform = dynamic_cast<Transform *>(item);
        if (transform == nullptr)
            continue;
        auto gameObject = transform -> getParentGameObject();
        auto if_can_be_hit = gameObject -> getComponent<Hitable>();
        if (if_can_be_hit != nullptr)
        {
            if(gameObject -> getComponent<Unmatched>()!= nullptr)
                continue;
            else
                gameObject -> addComponent(new Unmatched());
            if(gameObject -> getComponent<Player>() != nullptr)
            {
                gameObject->getComponent<Player>()->be_attacked();//人掉血
                this -> owner -> score_plus(10);
            }
            else
            {
                this -> owner -> score_plus(1);
                int random=rand()%10;
                if(random == 1)
                {
                    auto numplusprop = new GameObject;
                    numplusprop->addComponent(new ImageTransform());
                    numplusprop->addComponent(new NumPlusProp(image->pos()));
                    attachGameObject(numplusprop);
                }
                else if(random == 2)
                {
                    auto pushprop = new GameObject;
                    pushprop->addComponent(new ImageTransform());
                    pushprop->addComponent(new PushProp(image->pos()));
                    attachGameObject(pushprop);
                }
                else if(random == 3)
                {
                    auto rangeplusprop = new GameObject;
                    rangeplusprop->addComponent(new ImageTransform());
                    rangeplusprop->addComponent(new RangePlusProp(image->pos()));
                    attachGameObject(rangeplusprop);
                }
                else if(random == 4)
                {
                    auto speedprop = new GameObject;
                    speedprop->addComponent(new ImageTransform());
                    speedprop->addComponent(new SpeedProp(image->pos()));
                    attachGameObject(speedprop);
                }
            }
            if_can_be_hit->beHit();//一个可以复用的函数，用来销毁对象（既是softwall里的hitable里的behit，也是player里的health里的behit）
        }
    }
}
