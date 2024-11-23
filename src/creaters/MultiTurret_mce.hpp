#pragma once

#include "Charlie2D.hpp"

class MultiTurret : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  void onDestroy() override;
  static void createInstance(Vector2f centerPosition = {0, 0}, float firerate=200, int directionCount=4);
  static void configureInstance(Entity* entity, float firerate=200, int directionCount=4);

  Angle angle;
  float firerate = 200;
  int directionCount = 4;
  Entity* light;
};

