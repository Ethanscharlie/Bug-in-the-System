#pragma once

#include "Charlie2D.hpp"

std::vector<Image> generateSpritesheetAnimationButNotShit(Image image,
                                                          int gridSize = 16,
                                                          int row = 0);

class Explosion : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  void onDestroy() override;
  static void createInstance(Vector2f centerPosition = {0, 0});
  static void configureInstance(Entity *entity);
  Entity *light = nullptr;
};
