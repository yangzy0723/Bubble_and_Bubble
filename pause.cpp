#include "pause.h"

#include "qtimer.h"
#include "gamescene.h"

Pause::Pause(GameScene *gameScene)
{
    this -> gameScene = gameScene;
    if_pause = 0;

    this -> buttonSound = new QSoundEffect();
    this -> buttonSound -> setSource(QUrl::fromLocalFile(":/sound/sound/buttonSound.wav"));
    this -> buttonSound -> setVolume(1.0f);
}

void Pause::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    image -> setImage(":/image/image/pause.png");
    image -> setPos(QPointF(900,575));
    image -> setAlignment(Qt::AlignCenter);
}

void Pause::onClick(QGraphicsSceneMouseEvent *ev)
{
    this -> buttonSound -> play();

    if(if_pause)
    {
        image -> setImage(":/image/image/pause.png");
        this->gameScene->updateTimer->start();
        if_pause = 0;
    }
    else
    {
        image -> setImage(":/image/image/resume.png");
        this->gameScene->updateTimer->stop();
        if_pause = 1;
    }
}
