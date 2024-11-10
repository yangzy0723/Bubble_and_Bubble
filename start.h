#ifndef START_H
#define START_H

#include "component.h"
#include "gameobject.h"
#include "mainwindow.h"
#include "imagetransform.h"

#include <QSoundEffect>

class Start:public Component
{
public:
    Start(GameObject* instructionButton,
          GameObject* exitButton,
          GameObject* gameMenu,
          GameScene* gameScene,
          MainWindow *w);

    void onAttach() override;
    void onClick(QGraphicsSceneMouseEvent *ev) override;

private:
    ImageTransform *image;
    GameObject* instruction_Button;
    GameObject* exit_Button;
    GameObject* game_Menu;
    GameScene* gameScene;
    MainWindow* window;

    QSoundEffect* buttonSound;//此时只是声明，未分配内存空间
};

#endif // START_H

//开始游戏的按钮，点击后detach了自己、exit、instructions
