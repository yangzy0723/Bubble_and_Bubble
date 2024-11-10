#ifndef BOMBPHYSICS_H
#define BOMBPHYSICS_H

#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

class BombPhysics:public Component
{
public:
    BombPhysics();

    void onAttach() override;
    void onUpdate(float deltaTime) override;

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
};

#endif // BOMBPHYSICS_H
