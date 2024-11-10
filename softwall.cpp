#include "softwall.h"

#include "block.h"
#include "hitable.h"

Softwall::Softwall(int ypos, int xpos, int type)
{
    this -> xPos = xpos;
    this -> yPos = ypos;
    this -> type = type;
}

void Softwall::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(this -> image != nullptr);
    image -> setPos(20+40*xPos,20+40*yPos);
    image -> setAlignment(Qt::AlignCenter);
    if(type == 0)
        image -> setImage(":/image/image/softwall0.png");
    else if(type == 1)
        image -> setImage(":/image/image/softwall1.png");

    this -> gameObject -> addComponent(new Block());
    this -> gameObject -> addComponent(new Hitable());
}

void Softwall::onUpdate(float deltaTime)
{

}
