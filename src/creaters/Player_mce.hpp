#pragma once

#include "Charlie2D.hpp"

class Player : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  static void createInstance(Vector2f centerPosition = {0, 0});
  static void configureInstance(Entity* entity);
  void turn(float degrees=90);
  void moveForward();

  Angle direction;
};

