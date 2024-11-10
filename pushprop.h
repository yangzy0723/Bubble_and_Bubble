#ifndef PUSHPROP_H
#define PUSHPROP_H


#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

class PushProp:public Component
{
public:
    PushProp(QPointF pos);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

    void bepicked();

private:
    ImageTransform* image;

    QPointF set_pos;
};

#endif // PUSHPROP_H
