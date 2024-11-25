#pragma once

#include "Charlie2D.hpp"

inline Mix_Music *music;
inline int turns = 0;
inline float startTime = 0;

class Player : public Component {
public:
  void start() override;
  void update(float deltaTime) override;
  static void createInstance(Vector2f centerPosition = {0, 0});
  static void configureInstance(Entity *entity);
  void turn(float degrees = 90);
  void setAngle(Angle newAngle);
  void moveForward();

  Angle direction;
  Angle tempAngleCapture;

  float charge = 0;
  float chargeMax = 100;

private:
  void onPress();
  void onHold();
};
