#include <QGraphicsEllipseItem>

#include "bomb.h"
#include "player.h"
#include "usercontroller.h"

UserController::UserController(Qt::Key up, Qt::Key down, Qt::Key left, Qt::Key right, Qt::Key setbomb_key,
                               const char* upimage_route,
                               const char* downimage_route,
                               const char* leftimage_route,
                               const char* rightimage_route)
{
    this -> up = up;
    this -> down = down;
    this -> left = left;
    this -> right = right;
    this -> setbomb_key = setbomb_key;
    this -> upimage_route = upimage_route;
    this -> downimage_route = downimage_route;
    this -> leftimage_route = leftimage_route;
    this -> rightimage_route = rightimage_route;
}

void UserController::onAttach()
{
    this -> phy = this -> gameObject -> getComponent<Physics>();
    Q_ASSERT(phy != nullptr);
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    this -> collider = dynamic_cast<QGraphicsItem*>(this -> image);
    Q_ASSERT(collider != nullptr);
}

void UserController::onUpdate(float deltaTime)
{
    float vx = 0;
    float vy = 0;
    if(getKey(setbomb_key))
    {
        bool if_there_is_a_bomb = 0;
        if(phy->get_vx()==0 && phy->get_vy()==0)
        {
            for (auto item : this->collider->collidingItems())
            {
                while (item->parentItem() != nullptr)
                    item = item->parentItem();
                auto transform = dynamic_cast<Transform *>(item);
                if (transform == nullptr)
                    continue;
                auto gameObject = transform->getParentGameObject();
                auto bomb = gameObject->getComponent<Bomb>();
                if(bomb != nullptr)
                    if_there_is_a_bomb = 1;
                else
                    continue;
            }
            if(!if_there_is_a_bomb)
                this -> gameObject -> getComponent<Player>() -> set_bomb();
        }
    }
    if(getKey(up))
    {
        vy = -2;
        image->setImage(upimage_route);
    }
    else if(getKey(down))
    {
        vy = 2;
        image->setImage(downimage_route);
    }
    else if(getKey(left))
    {
        vx = -2;
        image->setImage(leftimage_route);
    }
    else if(getKey(right))
    {
        vx = 2;
        image->setImage(rightimage_route);
    }
    phy->setVelocity(vx,vy);
}

