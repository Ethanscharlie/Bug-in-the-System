#pragma once

#include "Charlie2D.hpp"

class TextDrifter : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  static void createInstance(Vector2f centerPosition = {0, 0}, std::string text="Sample");
  static void configureInstance(Entity* entity, std::string text="Sample");
  float tempPos;
};

