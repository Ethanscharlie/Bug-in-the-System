#pragma once

#include "Charlie2D.hpp"

class Enemy : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  void onDestroy() override;

  float tempPos;
  bool allowFire = false;
  int health = 1;
  bool shield = true;
  Entity *light;
};
