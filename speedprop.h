#ifndef SPEEDPROP_H
#define SPEEDPROP_H

#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

class SpeedProp:public Component
{
public:
    SpeedProp(QPointF pos);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

    void bepicked();

private:
    ImageTransform* image;

    QPointF set_pos;
};

#endif // SPEEDPROP_H
