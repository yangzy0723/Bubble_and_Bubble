#ifndef FIRE_H
#define FIRE_H

#include <player.h>
#include <component.h>
#include <transform.h>
#include <gameobject.h>

class Fire:public Component
{
public:
    Fire(QPointF pos,Player* owner);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

private:
    Player* owner;
    ImageTransform* image;
    QGraphicsItem *collider;

    int timeToLive;
    QPointF set_pos;
};

#endif // FIRE_H

//可破坏hitable和继承了hitable的health
