#include "health.h"

Health::Health(int health) : health(health)
{
    this -> playerDead = new QSoundEffect;
    this -> playerDead -> setSource(QUrl::fromLocalFile(":/sound/sound/playerDead.wav"));
    this -> playerDead -> setVolume(1.0f);
}

void Health::beHit()
{
  health--;
  if (health <= 0)
  {
      this -> playerDead -> play();

      detachGameObject(this->gameObject);
  }
}
