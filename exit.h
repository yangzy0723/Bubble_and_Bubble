#ifndef EXIT_H
#define EXIT_H

#include "component.h"
#include "gameobject.h"
#include "mainwindow.h"
#include "imagetransform.h"

class Exit:public Component
{
public:
    Exit(int xPos, int yPos, MainWindow* w);

    void onAttach() override;
    void onClick(QGraphicsSceneMouseEvent *ev) override;

private:
    QWidget* window;
    ImageTransform *image;

    int x_pos;
    int y_pos;
};

#endif // EXIT_H

//退出按钮
