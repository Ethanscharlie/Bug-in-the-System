#pragma once

#include "Charlie2D.hpp"

class PlayerBullet : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  void onDestroy() override;
  static void createInstance(Vector2f centerPosition = {0, 0}, Angle direction=Angle());
  static void configureInstance(Entity* entity, Angle direction);

  Entity* light;
};

