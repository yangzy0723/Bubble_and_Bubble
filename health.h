#ifndef HEALTH_H_
#define HEALTH_H_

#include "hitable.h"
#include "gameobject.h"

#include <QSoundEffect>

class Health : public Hitable
{
public:
    explicit Health(int health);

    void beHit() override;

private:
    int health;

    QSoundEffect* playerDead;
};

#endif  // HEALTH_H_
