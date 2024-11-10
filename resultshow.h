#ifndef RESULTSHOW_H
#define RESULTSHOW_H

#include <player.h>
#include <component.h>
#include <gameobject.h>
#include <imagetransform.h>

class ResultShow:public Component
{
public:
    ResultShow(Player* p1,Player* p2, Player* p3, Player* p4);

    void onAttach() override;
    void onUpdate(float deltaTime) override;

private:
    Player* p1;
    Player* p2;
    Player* p3;
    Player* p4;
    ImageTransform* image;
};

#endif // RESULTSHOW_H
