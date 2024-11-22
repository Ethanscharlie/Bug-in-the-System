#include "Charlie2D.hpp"
#include "Vector2f.hpp"
#include "creaters/Player_mce.hpp"
#include "creaters/Turret_mce.hpp"
#include <iostream>

int main(int, char **) {
  GameManager::init();
  GameManager::shadowFilter->shadowFilterTint = {60, 60, 60};

  Entity *background = GameManager::createEntity("Background");
  background->layer = -10;
  background->box.size = GameManager::gameWindowSize;
  background->box.setWithCenter({0, 0});
  background->add<Sprite>()->image = {"res/images/background.png"};

  Player::createInstance({0, 0});

  Turret::createInstance({0, 0});
  Turret::createInstance(Vector2f(0, 0) - GameManager::gameWindowSize / 2 +
                         100);

  GameManager::doUpdateLoop();
  return 0;
}
