#include "resultshow.h"

ResultShow::ResultShow(Player* p1,Player* p2, Player* p3, Player* p4)
{
    this -> p1 = p1;
    this -> p2 = p2;
    this -> p3 = p3;
    this -> p4 = p4;
}

void ResultShow::onAttach()
{
    this->image = this->gameObject->getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
}

void ResultShow::onUpdate(float deltaTime)
{
    if(p1->get_health()==0 && p2->get_health()==0 && p3->get_health()==0)
        image->setImage(":/image/image/R2WIN.png");
    else if(p1->get_health()==0 && p2->get_health()==0 && p4->get_health()==0)
        image->setImage(":/image/image/R1WIN.png");
    else if(p1->get_health()==0 && p3->get_health()==0 && p4->get_health()==0)
        image->setImage(":/image/image/P2WIN.png");
    else if(p2->get_health()==0 && p3->get_health()==0 && p4->get_health()==0)
        image->setImage(":/image/image/P1WIN.png");
}
