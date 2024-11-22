#include "Charlie2D.hpp"
#include "Vector2f.hpp"
#include "creaters/Player_mce.hpp"
#include "creaters/Turret_mce.hpp"
#include <functional>
#include <iostream>
#include <vector>

int main(int, char **) {
  GameManager::init();
  GameManager::shadowFilter->shadowFilterTint = {60, 60, 60};

  Entity *background = GameManager::createEntity("Background");
  background->layer = -10;
  background->box.size = GameManager::gameWindowSize;
  background->box.setWithCenter({0, 0});
  background->add<Sprite>()->image = {"res/images/background.png"};

  Player::createInstance({0, 0});

  GameManager::doUpdateLoop();
  return 0;
}
