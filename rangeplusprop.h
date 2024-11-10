#ifndef RANGEPLUSPROP_H
#define RANGEPLUSPROP_H

#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

class RangePlusProp:public Component
{
public:
     RangePlusProp(QPointF pos);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

    void bepicked();

private:
    ImageTransform* image;

    QPointF set_pos;
};

#endif // RANGEPLUSPROP_H

