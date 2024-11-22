#pragma once

#include "Charlie2D.hpp"

class Bullet : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  static void createInstance(Vector2f centerPosition = {0, 0}, Angle direction=Angle());
  static void configureInstance(Entity* entity, Angle direction);
  void onDestroy() override;

  Entity* light = nullptr;
};

