#include "Light.hpp"

void createLight(Entity *entity, Vector2f centerPos, float distance,
                 std::array<Uint32, 3> color) {
  entity->box.setWithCenter(centerPos);
  entity->box.setScale({distance * 2, distance * 2});
  entity->layer = 30;

  Light *lightComponent = entity->add<Light>();
  lightComponent->image = Image("res/images/light2.png");
  lightComponent->r = color[0];
  lightComponent->g = color[1];
  lightComponent->b = color[2];
}
