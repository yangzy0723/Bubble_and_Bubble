#include "physics.h"

#include <QGraphicsItem>

#include "bomb.h"
#include "block.h"
#include "player.h"
#include "pushprop.h"
#include "speedprop.h"
#include "numplusprop.h"
#include "bombphysics.h"
#include "rangeplusprop.h"
#include "abilitypushbomb.h"

Physics::Physics()
{
    vx = 0;
    vy = 0;
    interval = 20;
    mydeltatime = 1;
    moving_time = interval;

    this -> pickupProp = new QSoundEffect;
    this -> pickupProp -> setSource(QUrl::fromLocalFile(":/sound/sound/pickupProp.wav"));
    this -> pickupProp -> setVolume(1.0f);
}

void Physics::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    this -> collider = dynamic_cast<QGraphicsItem*>(this -> image);
    Q_ASSERT(collider != nullptr);
}

void Physics::onUpdate(float deltaTime)
{
    if(moving_time == interval)
    {
        original_pos = image -> pos();
        for (auto item : this->collider->collidingItems())
        {
            while (item->parentItem() != nullptr)
                item = item->parentItem();
            auto transform = dynamic_cast<Transform *>(item);
            if (transform == nullptr)
                continue;
            auto gameObject = transform->getParentGameObject();
            if(gameObject->getComponent<SpeedProp>()!=nullptr)
            {
                this->pickupProp -> play();
                this->gameObject->getComponent<Player>()->score_plus(5);
                speedplus();
                gameObject->getComponent<SpeedProp>()->bepicked();
            }
            else if(gameObject -> getComponent<NumPlusProp>()!=nullptr)
            {
                this->pickupProp -> play();
                this->gameObject->getComponent<Player>()->score_plus(5);
                this->gameObject->getComponent<Player>()->bomb_plus();
                gameObject->getComponent<NumPlusProp>()->bepicked();
            }
            else if(gameObject->getComponent<PushProp>()!=nullptr)
            {
                this->pickupProp -> play();
                this->gameObject->getComponent<Player>()->score_plus(5);
                this->gameObject->addComponent(new AbilityPushBomb());
                gameObject->getComponent<PushProp>()->bepicked();
            }
            else if(gameObject->getComponent<RangePlusProp>()!=nullptr)
            {
                this->pickupProp -> play();
                this->gameObject->getComponent<Player>()->score_plus(5);
                this->gameObject->getComponent<Player>()->bombrange_plus();
                gameObject->getComponent<RangePlusProp>()->bepicked();
            }
        }
    }
    if(moving_time > 0 && (vx!=0 || vy!=0))
    {
        image->moveBy(mydeltatime*vx,mydeltatime*vy);
        moving_time = moving_time - mydeltatime;
    }
    else
    {
        moving_time = interval;
        original_pos = image -> pos();
        vx = 0;
        vy = 0;
    }
    for (auto item : this->collider->collidingItems())
    {
        while (item->parentItem() != nullptr)
            item = item->parentItem();
        auto transform = dynamic_cast<Transform *>(item);
        if (transform == nullptr)
            continue;
        if(transform->x()-original_pos.x() >= 40
                ||transform->x()-original_pos.x() <= -40
                ||transform->y()-original_pos.y() >= 40
                ||transform->y()-original_pos.y() <=-40)//解决人从炸弹里走出来的问题
        {
            auto gameObject = transform->getParentGameObject();
            auto block = gameObject->getComponent<Block>();
            if (block == nullptr)
                continue;
            else if(this -> gameObject -> getComponent<AbilityPushBomb>()!=nullptr
                    && gameObject -> getComponent<Bomb>() != nullptr)//撞到炸弹，调用炸弹的物理引擎，推动炸弹
            {
                if(vx > 0)
                    gameObject->getComponent<BombPhysics>()->setVelocity(2,0);
                else if(vx < 0)
                    gameObject->getComponent<BombPhysics>()->setVelocity(-2,0);
                else if(vy > 0)
                    gameObject->getComponent<BombPhysics>()->setVelocity(0,2);
                else if(vy < 0)
                    gameObject->getComponent<BombPhysics>()->setVelocity(0,-2);
                image->setPos(original_pos);
                vx = 0;
                vy = 0;
                moving_time = interval;
                break;
                //人物停下，回归原来的位置
            }
            image->setPos(original_pos);
            vx = 0;
            vy = 0;
            moving_time = interval;
            break;
        }
    }
}

int Physics::get_vx()
{
    return vx;
}

int Physics::get_vy()
{
    return vy;
}

void Physics::speedplus()
{
    if(mydeltatime < 4)
        mydeltatime = mydeltatime*2;
}
//速度这个mydeltatime（一步走多少格）得是40/2（速度）的因数

void Physics::setVelocity(float vx, float vy)
{
    if(this->vx == 0 && this->vy ==0)
    {
        this -> vx = vx;
        this -> vy = vy;
    }
}
//走到整格才会更新速度，保证每次走一格

