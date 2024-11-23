#pragma once

#include "Charlie2D.hpp"

class Enemy : public Component {
public:
  void start() override;
  void update(float deltaTime) override;

  float tempPos;
  bool allowFire = false;
};
