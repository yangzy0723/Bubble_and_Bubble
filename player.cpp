#include "player.h"

#include "bomb.h"
#include "block.h"
#include "health.h"
#include "unmatched.h"
#include "bombphysics.h"
#include "abilitypushbomb.h"

Player::Player(int ypos, int xpos, int type, GameScene *gameScene)
{
    this -> xPos = xpos;
    this -> yPos = ypos;
    this -> type = type;
    this -> score = 0;
    this -> health = 5;
    this -> bomb_num = 1;
    this -> bomb_sum = 1;
    this -> bomb_range = 1;
    this -> gameScene = gameScene;
    this -> abilityPushBombTime = 600;
    this -> abilityUnmatched = 51;
    //无敌时间，设51帧是保证被烧只掉一滴血
}

void Player::onAttach()
{
    this -> image = this -> gameObject -> getComponent<ImageTransform>();
    Q_ASSERT(this -> image != nullptr);
    image -> setPos(20+40*xPos,20+40*yPos);
    image -> setAlignment(Qt::AlignCenter);
    if(type == 1)
        image -> setImage(":/image/image/player1down.png");
    else if(type == 2)
        image -> setImage(":/image/image/player2down.png");
    else if(type == 3)
        image -> setImage(":/image/image/robot1_up.png");
    else if(type == 4)
        image -> setImage(":/image/image/robot2_up.png");
    this -> gameObject -> addComponent(new Block());
    this -> gameObject -> addComponent(new Health(5));
}

void Player::onUpdate(float deltaTime)
{
    if(this -> gameObject -> getComponent<AbilityPushBomb>() != nullptr)
    {
        abilityPushBombTime = abilityPushBombTime - deltaTime;
        if(abilityPushBombTime <= 0)
        {
            this->gameObject->removeComponent(this->gameObject->getComponent<AbilityPushBomb>());
            abilityPushBombTime = 600;
        }
    }
    if(this -> gameObject -> getComponent<Unmatched>() != nullptr)
    {
        abilityUnmatched = abilityUnmatched - deltaTime;
        if(abilityUnmatched <= 0)
        {
            this->gameObject->removeComponent(this->gameObject->getComponent<Unmatched>());
            abilityUnmatched = 51;
        }
    }
}

void Player::set_bomb()
{
    if(bomb_num > 0)
    {
        auto bomb = new GameObject;
        bomb->addComponent(new ImageTransform());
        bomb->addComponent(new BombPhysics());
        bomb->addComponent(new Bomb(image->pos(),bomb_range,this,gameScene));
        attachGameObject(bomb);
        bomb_num--;
    }
}

void Player::bomb_plus()
{
    bomb_num++;
    bomb_sum++;
}

void Player::bomb_recover()
{
    bomb_num++;
}

void Player::bombrange_plus()
{
    bomb_range++;
}

int Player::get_bombrange()
{
    return bomb_range;
}

int Player::get_score()
{
    return score;
}

void Player::score_plus(int score)
{
    this -> score = this->score + score;
}

int Player::get_health()
{
    return health;
}

void Player::be_attacked()
{
    health--;
}

bool Player::check()
{
    if(bomb_num == bomb_sum)
        return 1;
    return 0;
}
