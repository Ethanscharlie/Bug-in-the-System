#pragma once

#include "Charlie2D.hpp"

class IntoText : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  static void createInstance(Vector2f centerPosition = {0, 0});
  static void configureInstance(Entity* entity);
};

