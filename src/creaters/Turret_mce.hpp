#pragma once

#include "Charlie2D.hpp"

class Turret : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  void onDestroy() override;
  static void createInstance(Vector2f centerPosition = {0, 0},
                             float fireRate = 600, float rotationSpeed = 60);
  static void configureInstance(Entity *entity, float fireRate = 600,
                                float rotationSpeed = 60);

  Angle fireAngle;
  float fireRate = 600;
  float rotationSpeed = 60;
};
