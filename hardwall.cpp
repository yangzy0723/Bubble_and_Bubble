#include "hardwall.h"

#include "block.h"
Hardwall::Hardwall(int ypos, int xpos, int type)
{
    this -> xPos = xpos;
    this -> yPos = ypos;
    this -> type = type;
}

void Hardwall::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(this -> image != nullptr);
    image -> setPos(20+40*xPos,20+40*yPos);
    image -> setAlignment(Qt::AlignCenter);
    if(type == 0)
        image -> setImage(":/image/image/hardwall0.png");
    else if(type == 1)
        image -> setImage(":/image/image/hardwall1.png");
    else if(type == 2)
        image -> setImage(":/image/image/hardwall2.png");
    else if(type == 3)
        image -> setImage(":/image/image/hardwall3.png");

    this -> gameObject -> addComponent(new Block());
}

void Hardwall::onUpdate(float deltaTime)
{

}
