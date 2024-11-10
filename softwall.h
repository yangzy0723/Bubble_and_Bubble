#ifndef SOFTWALL_H
#define SOFTWALL_H

#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

class Softwall:public Component
{
public:
    Softwall(int ypos, int xpos, int type);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

protected:
    ImageTransform* image;

    int xPos;
    int yPos;
    int type;
};

#endif // SOFTWALL_H

//自动挂载了障碍物和可破坏属性
