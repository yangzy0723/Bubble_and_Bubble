#ifndef NUMPLUSPROP_H
#define NUMPLUSPROP_H

#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

class NumPlusProp:public Component
{
public:
     NumPlusProp(QPointF pos);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

    void bepicked();

private:
    ImageTransform* image;

    QPointF set_pos;
};


#endif // NUMPLUSPROP_H
