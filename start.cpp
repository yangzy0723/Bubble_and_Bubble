#include "start.h"

#include "exit.h"
#include "pause.h"
#include "player.h"
#include "physics.h"
#include "hardwall.h"
#include "softwall.h"
#include "scoreboard.h"
#include "gameobject.h"
#include "resultshow.h"
#include "instructions.h"
#include "aicontroller.h"
#include "usercontroller.h"
#include "imagetransform.h"

Start::Start(GameObject *instructionButton, GameObject* exitButton, GameObject *gameMenu, GameScene *gameScene, MainWindow *w)
{
    this -> instruction_Button = instructionButton;
    this -> exit_Button = exitButton;
    this -> game_Menu = gameMenu;
    this -> gameScene = gameScene;
    this -> window = w;

    this -> buttonSound = new QSoundEffect();
    this -> buttonSound -> setSource(QUrl::fromLocalFile(":/sound/sound/buttonSound.wav"));
    this -> buttonSound -> setVolume(1.0f);
}

void Start::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(image != nullptr);
    image -> setImage(":/image/image/start.png");
    image -> setPos(QPointF(500,560));
    image -> setAlignment(Qt::AlignCenter);
}

void Start::onClick(QGraphicsSceneMouseEvent *ev)
{
    this -> buttonSound -> play();

    auto player1 = new GameObject;
    player1->addComponent(new ImageTransform());
    player1->addComponent(new Player(1,1,1,gameScene));
    player1->addComponent(new Physics());
    player1->addComponent(new UserController(Qt::Key_W,Qt::Key_S,Qt::Key_A,Qt::Key_D,Qt::Key_Space,
                                             ":/image/image/player1up.png",
                                             ":/image/image/player1down.png",
                                             ":/image/image/player1left.png",
                                             ":/image/image/player1right.png"));

    auto player2 = new GameObject;
    player2->addComponent(new ImageTransform());
    player2->addComponent(new Player(1,18,2,gameScene));
    player2->addComponent(new Physics());
    player2->addComponent(new UserController(Qt::Key_I,Qt::Key_K,Qt::Key_J,Qt::Key_L,Qt::Key_Return,
                                             ":/image/image/player2up.png",
                                             ":/image/image/player2down.png",
                                             ":/image/image/player2left.png",
                                             ":/image/image/player2right.png"));

    auto robot1 = new GameObject;
    robot1->addComponent(new ImageTransform());
    robot1->addComponent(new Player(13,1,3,gameScene));
    robot1->addComponent(new Physics());
    robot1->addComponent(new AIController(
                             ":/image/image/robot1_up.png",
                             ":/image/image/robot1_down.png",
                             ":/image/image/robot1_left.png",
                             ":/image/image/robot1_right.png",
                             gameScene)
                         );

    auto robot2 = new GameObject;
    robot2->addComponent(new ImageTransform());
    robot2->addComponent(new Player(13,18,4,gameScene));
    robot2->addComponent(new Physics());
    robot2->addComponent(new AIController(
                             ":/image/image/robot2_up.png",
                             ":/image/image/robot2_down.png",
                             ":/image/image/robot2_left.png",
                             ":/image/image/robot2_right.png",
                             gameScene)
                         );

    auto Map = new GameObject**[15];
    for(int i = 0; i < 15; i++)
    {
        Map[i] = new GameObject*[20];
        for(int j = 0; j < 20; j++)
        {
            Map[i][j] = new GameObject;
            auto aNewPicture = new ImageTransform;
            aNewPicture->setPos(QPointF(20+40*j,20+40*i));
            aNewPicture->setImage(":/image/image/background.png");
            aNewPicture->setAlignment(Qt::AlignCenter);
            Map[i][j]->addComponent(aNewPicture);
            attachGameObject(Map[i][j]);
        }
    }

    char map_symbol[15][20] =
    {
        {'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N','N','N','N'},
        {'N', ' ', ' ', ' ', ' ', ' ', 'P', 'm', 'P', ' ', 'P', 'm', 'P', ' ', ' ', ' ', ' ',' ',' ','N'},
        {'N', 'M', ' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ', 'P', ' ', ' ', ' ', ' ', ' ', ' ',' ',' ','N'},
        {'N', 'm', 'n', 'M', 'n', ' ', 'n', ' ', 'P', ' ', 'P', ' ', 'n', ' ', 'n', 'M', 'n','M','M','N'},
        {'N', 'm', 'n', ' ', 'M', ' ', 'n', ' ', 'm', ' ', 'm', ' ', 'n', ' ', 'M', ' ', 'n',' ','m','N'},
        {'N', 'M', 'n', ' ', 'n', 'M', 'n', 'M', 'm', ' ', 'm', 'M', 'n', 'M', 'n', ' ', 'n','M','M','N'},
        {'N', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ','m','N'},
        {'N', 'M', 'm', 'M', 'M', 'M', 'm', 'M', ' ', 'X', ' ', 'M', 'm', 'M', 'M', 'M', 'm','M','m','N'},
        {'N', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ','m','N'},
        {'N', 'M', 'n', ' ', 'n', 'M', 'n', 'M', 'm', ' ', 'm', 'M', 'n', 'M', 'n', ' ', 'n','M','M','N'},
        {'N', 'm', 'n', ' ', 'M', ' ', 'n', ' ', 'm', ' ', 'm', ' ', 'n', ' ', 'M', ' ', 'n',' ','m','N'},
        {'N', 'm', 'n', 'M', 'n', ' ', 'n', ' ', 'P', ' ', 'P', ' ', 'n', ' ', 'n', 'M', 'n','M','M','N'},
        {'N', 'M', ' ', ' ', ' ', ' ', ' ', ' ', 'P', ' ', 'P', ' ', ' ', ' ', ' ', ' ', ' ',' ',' ','N'},
        {'N', ' ', ' ', ' ', ' ', ' ', 'P', 'm', 'P', ' ', 'P', 'm', 'P', ' ', ' ', ' ', ' ',' ',' ','N'},
        {'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N','N','N','N'},
    };

    auto objectMap = new GameObject**[15];
    for(int i = 0; i < 15; i++)
    {
        objectMap[i] = new GameObject*[20];
        for(int j = 0; j < 20; j++)
        {
            objectMap[i][j] = new GameObject;
            objectMap[i][j]->addComponent(new ImageTransform());
            if(map_symbol[i][j] != ' ')
            {
                if(map_symbol[i][j] == 'N')
                    objectMap[i][j] -> addComponent(new Hardwall(i, j, 2));
                else if(map_symbol[i][j] == 'M')
                    objectMap[i][j] -> addComponent(new Hardwall(i, j, 1));
                else if(map_symbol[i][j] == 'P')
                    objectMap[i][j] -> addComponent(new Hardwall(i, j, 0));
                else if(map_symbol[i][j] == 'X')
                {
                    objectMap[i][j] -> addComponent(new Hardwall(i, j, 3));
                    objectMap[i][j] -> addComponent(new ResultShow(player1->getComponent<Player>(),
                                                                   player2->getComponent<Player>(),
                                                                   robot1->getComponent<Player>(),
                                                                   robot2->getComponent<Player>()));
                }
                else if(map_symbol[i][j] == 'm')
                    objectMap[i][j] -> addComponent(new Softwall(i, j, 0));
                else if(map_symbol[i][j] == 'n')
                    objectMap[i][j] -> addComponent(new Softwall(i, j, 1));
            }
            attachGameObject(objectMap[i][j]);
        }
    }
    attachGameObject(player1);
    attachGameObject(player2);
    attachGameObject(robot1);
    attachGameObject(robot2);

    auto background = new GameObject;
    auto Picture = new ImageTransform;
    Picture->setPos(QPointF(900,300));
    Picture->setImage(":/image/image/decoration2.jpeg");
    Picture->setAlignment(Qt::AlignCenter);
    background->addComponent(Picture);
    attachGameObject(background);

    auto decoration = new GameObject;
    auto deco = new ImageTransform;
    deco->setPos(QPointF(960,550));
    deco->setImage(":/image/image/decoration1.png");
    deco->setAlignment(Qt::AlignCenter);
    decoration->addComponent(deco);
    attachGameObject(decoration);

    auto newExitButton = new GameObject;
    newExitButton->addComponent(new ImageTransform());
    newExitButton->addComponent(new Exit(900, 525, this -> window));
    gameScene->attachGameObject(newExitButton);

    auto PauseBtn = new GameObject();
    PauseBtn->addComponent(new ImageTransform());
    PauseBtn->addComponent(new Pause(gameScene));
    attachGameObject(PauseBtn);

    auto scoreboard = new GameObject*[5];
    for(int i = 1; i <= 4; i++)
    {
        scoreboard[i] = new GameObject;
        scoreboard[i]->addComponent(new Transform);
        if(i == 1)
            scoreboard[i]->addComponent(new ScoreBoard("\nPlayer1's score is:\n",player1->getComponent<Player>(),i));
        else if(i == 2)
            scoreboard[i]->addComponent(new ScoreBoard("\nPlayer2's score is:\n",player2->getComponent<Player>(),i));
        else if(i == 3)
            scoreboard[i]->addComponent(new ScoreBoard("\nRobot1's score is:\n",robot1->getComponent<Player>(),i));
        else
            scoreboard[i]->addComponent(new ScoreBoard("\nRobot2's score is:\n",robot2->getComponent<Player>(),i));
        attachGameObject(scoreboard[i]);
    }

    detachGameObject(game_Menu);
    detachGameObject(exit_Button);
    detachGameObject(instruction_Button);
    detachGameObject(this->gameObject);
}
