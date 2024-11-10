#include "scoreboard.h"

#include "qfont.h"
#include "qbrush.h"
#include "abilitypushbomb.h"

ScoreBoard::ScoreBoard(QString text, Player* player, int type)
{
    this -> type = type;
    this -> text = text;
    this -> player = player;
}

void ScoreBoard::onAttach()
{
    auto transform = this -> gameObject -> getComponent<Transform>();
    Q_ASSERT(transform != nullptr);
    this -> textBox = new QGraphicsSimpleTextItem(transform);
    textBox->setBrush(QColorConstants::White);
    QFont font;
    font.setPointSize(14);//字体大小
    textBox -> setFont(font);//其他控件一样
    if(type == 1)
        transform->setPos(QPointF(820,120));
    else if(type == 2)
        transform -> setPos(QPointF(820,210));
    else if(type == 3)
        transform -> setPos(QPointF(820,300));
    else
        transform -> setPos(QPointF(820,390));
}

void ScoreBoard::onUpdate(float deltaTime)
{
    QString score = QString::number(this -> player -> get_score(),10);
    QString hp = QString::number(this -> player -> get_health(),10);
    QString display = text+score+"\nHP:"+hp;
    if(this -> player -> getParentGameObject() -> getComponent<AbilityPushBomb>() != nullptr)
        display = display + "  PushBomb";
    textBox->setText(display);
}
