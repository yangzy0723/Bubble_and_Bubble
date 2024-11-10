#include "exit.h"
#include "bomb.h"
#include "qwidget.h"

Exit::Exit(int xPos, int yPos, MainWindow *w)
{
    this -> x_pos = xPos;
    this -> y_pos = yPos;
    this -> window = w;
}

void Exit::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    image -> setImage(":/image/image/exit.png");
    image -> setPos(QPointF(x_pos,y_pos));
    image -> setAlignment(Qt::AlignCenter);
}

void Exit::onClick(QGraphicsSceneMouseEvent *ev)
{
    window->close();
}
