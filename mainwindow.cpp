#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "exit.h"
#include "start.h"
#include "instructions.h"

void loadScene(GameScene *gameScene, MainWindow *w)
{    
    auto gameStart = new GameObject;
    auto background  = new ImageTransform;
    background -> setPos(QPointF(500,300));
    background -> setImage(":/image/image/gamestart.png");
    background -> setAlignment(Qt::AlignCenter);
    gameStart -> addComponent(background);
    gameScene -> attachGameObject(gameStart);

    auto instructionButton = new GameObject;
    instructionButton->addComponent(new ImageTransform());
    instructionButton->addComponent(new Instruction(gameStart));
    gameScene->attachGameObject(instructionButton);

    auto exitButton = new GameObject;
    exitButton->addComponent(new ImageTransform());
    exitButton->addComponent(new Exit(100,575, w));
    gameScene->attachGameObject(exitButton);

    auto startButton = new GameObject;
    startButton->addComponent(new ImageTransform());
    startButton->addComponent(new Start(instructionButton, exitButton, gameStart, gameScene, w));
    gameScene->attachGameObject(startButton);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    gameScene = new GameScene();
    gameScene->setParent(this);
    auto view = new QGraphicsView(gameScene, this);
    view->setFrameStyle(QFrame::NoFrame);
    view->resize(this->size());
    view->setSceneRect(QRect(0, 0, this->width(), this->height()));
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    loadScene(gameScene, this);

    this -> background = new QSoundEffect();
    this -> background -> setSource(QUrl::fromLocalFile(":/sound/sound/background.wav"));
    this -> background -> setLoopCount(QSoundEffect::Infinite);
    this -> background -> setVolume(0.5f);
    this -> background -> play();
}

MainWindow::~MainWindow() { delete ui; }
