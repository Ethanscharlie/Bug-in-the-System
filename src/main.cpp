#include "Charlie2D.hpp"
#include <iostream>
#include "creaters/Player_mce.hpp"

int main(int, char **) {
  GameManager::init();

  Player::createInstance({0, 0});

  GameManager::doUpdateLoop();
  return 0;
}
