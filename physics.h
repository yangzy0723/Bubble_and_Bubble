#ifndef PHYSICS_H
#define PHYSICS_H

#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

#include <QSoundEffect>

class Physics:public Component
{
public:
    Physics();

    void onAttach() override;
    void onUpdate(float deltaTime) override;

    int get_vx();
    int get_vy();
    void speedplus();
    void setVelocity(float vx, float vy);

private:
    ImageTransform* image;
    QGraphicsItem *collider;

    QPointF original_pos;
    float vx;
    float vy;
    int interval;
    int moving_time;
    int mydeltatime;

    QSoundEffect* pickupProp;
};

#endif // PHYSICS_H
