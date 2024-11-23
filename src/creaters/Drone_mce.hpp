#pragma once

#include "Charlie2D.hpp"
#include "Vector2f.hpp"

class Drone : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  void onDestroy() override;
  static void createInstance(Vector2f centerPosition = {0, 0});
  static void configureInstance(Entity* entity);

  void pickPosition();

  Entity *light = nullptr;
  Vector2f targetPos;
};

