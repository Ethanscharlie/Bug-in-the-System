#pragma once

#include "Charlie2D.hpp"

class Boss : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  void onDestroy() override;
  static void createInstance(Vector2f centerPosition = {0, 0},
                             float fireRate = 500, float rotationSpeed = 60);
  static void configureInstance(Entity *entity, float fireRate = 500,
                                float rotationSpeed = 60);

  Angle fireAngle;
  Entity *light = nullptr;
  float fireRate = 500;
  float rotationSpeed = 60;
};
