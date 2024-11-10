#include "bomb.h"

#include "fire.h"
#include "block.h"
#include "hardwall.h"
#include "gamescene.h"
#include "QGraphicsItem"

Bomb::Bomb(QPointF pos, int range, Player* owner, GameScene *gameScene)
{
    this -> set_pos = pos;
    this -> range = range;
    this -> owner = owner;
    this -> gameScene = gameScene;
    this -> count = 0;
    this -> timeToLive = 240;

    this -> bombExplode = new QSoundEffect();
    this -> bombExplode -> setSource(QUrl::fromLocalFile(":/sound/sound/bombExplode.wav"));
    this -> bombExplode -> setLoopCount(1);
    this -> bombExplode -> setVolume(0.5f);

}

void Bomb::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    image -> setPos(set_pos);
    image -> setAlignment(Qt::AlignCenter);
    image -> setImage(":/image/image/bomb1.png");

    this->gameObject ->addComponent(new Block());
}

void Bomb::onUpdate(float deltaTime)
{
    if(timeToLive <= 0)
    {
        bombExplode -> play();
        destory(this -> gameObject);
        owner->bomb_recover();

        auto fire = new GameObject;
        fire -> addComponent(new ImageTransform());
        fire -> addComponent(new Fire(image->pos(),owner));
        attachGameObject(fire);
        for(int up = 1; up <= range; up++)
        {
            QGraphicsItem* item = gameScene->itemAt(image->x(),image->y()-up*40,QTransform());
            if(item!=nullptr)
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform == nullptr)
                    continue;
                auto gameObject = transform->getParentGameObject();
                auto if_hardwall = gameObject->getComponent<Hardwall>();
                if (if_hardwall == nullptr)
                {
                    auto fire_up = new GameObject;
                    fire_up -> addComponent(new ImageTransform());
                    fire_up -> addComponent(new Fire(QPointF(image->x(),image->y()-up*40),owner));
                    attachGameObject(fire_up);
                }
                else
                    break;
            }
        }
        for(int down = 1; down <= range; down++)
        {
            QGraphicsItem* item = gameScene->itemAt(image->x(),image->y()+down*40,QTransform());
            if(item != nullptr)
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform == nullptr)
                    continue;
                auto gameObject = transform->getParentGameObject();
                auto if_hardwall = gameObject->getComponent<Hardwall>();
                if (if_hardwall == nullptr)
                {
                    auto fire_down = new GameObject;
                    fire_down -> addComponent(new ImageTransform());
                    fire_down -> addComponent(new Fire(QPointF(image->x(),image->y()+down*40),owner));
                    attachGameObject(fire_down);
                }
                else
                    break;
            }
        }
        for(int left = 1; left <= range; left++)
        {
            QGraphicsItem* item = gameScene->itemAt(image->x()-left*40,image->y(), QTransform());
            if(item != nullptr)
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform == nullptr)
                    continue;
                auto gameObject = transform->getParentGameObject();
                auto if_hardwall = gameObject->getComponent<Hardwall>();
                if (if_hardwall == nullptr)
                {
                    auto fire_left = new GameObject;
                    fire_left -> addComponent(new ImageTransform());
                    fire_left -> addComponent(new Fire(QPointF(image->x()-left*40,image->y()),owner));
                    attachGameObject(fire_left);
                }
                else
                    break;
            }
        }
        for(int right = 1; right <= range; right++)
        {
            QGraphicsItem* item = gameScene->itemAt(image->x()+right*40,image->y(), QTransform());
            if(item != nullptr)
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform == nullptr)
                    continue;
                auto gameObject = transform->getParentGameObject();
                auto if_hardwall = gameObject->getComponent<Hardwall>();
                if (if_hardwall == nullptr)
                {
                    auto fire_right = new GameObject;
                    fire_right -> addComponent(new ImageTransform());
                    fire_right -> addComponent(new Fire(QPointF(image->x()+right*40,image->y()),owner));
                    attachGameObject(fire_right);
                }
                else
                    break;
            }
        }
    }
    else
        timeToLive = timeToLive - deltaTime;
    count++;
    if(count == 20)
        image -> setImage(":/image/image/bomb2.png");
    else if(count == 40)
        image -> setImage(":/image/image/bomb3.png");
    else if(count == 60)
    {
        image -> setImage(":/image/image/bomb1.png");
        count = 0;
    }
}

int Bomb::get_bomb_range()
{
    return range;
}
