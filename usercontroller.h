#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include "physics.h"
#include "component.h"
#include "gameobject.h"
#include "imagetransform.h"

class UserController:public Component
{
public:
    UserController(Qt::Key up, Qt::Key down, Qt::Key left, Qt::Key right, Qt::Key setbomb_key,
                   const char* upimage_route,
                   const char* downimage_route,
                   const char* leftimage_route,
                   const char* rightimage_route);

    void onAttach() override;
    void onUpdate(float deltatime) override;

private:
    Qt::Key up;
    Qt::Key down;
    Qt::Key left;
    Qt::Key right;
    Qt::Key setbomb_key;

    Physics* phy;
    ImageTransform* image;
    QGraphicsItem *collider;
    const char* upimage_route;
    const char* downimage_route;
    const char* leftimage_route;
    const char* rightimage_route;
};

#endif // USERCONTROLLER_H
