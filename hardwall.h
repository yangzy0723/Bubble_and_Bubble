#ifndef HARDWALL_H
#define HARDWALL_H

#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

class Hardwall:public Component
{
public:
    Hardwall(int ypos, int xpos, int type);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

protected:
    ImageTransform* image;

    int xPos;
    int yPos;
    int type;
};

#endif // HARDWALL_H

//自动挂载了障碍物属性
