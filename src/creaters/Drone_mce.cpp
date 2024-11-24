#include "Drone_mce.hpp"
#include "Circle.hpp"
#include "Light.hpp"
#include "Math.hpp"
#include "Scheduler.hpp"
#include "Vector2f.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Player_mce.hpp"

#define ENTITY_TAG "{}"
#define IMAGE_FILE "res/images/turret.png"
Vector2f DRONE_SIZE = {32, 32};

void Drone::start() {}

void Drone::pickPosition() {
  targetPos = GameManager::getComponents<Player>()[0]->entity->box.getCenter();
  targetPos.x += randFloat(-100, 100);
  targetPos.y += randFloat(-100, 100);
}

void Drone::update(float deltaTime) {
  if (entity->get<Enemy>()->allowFire) {
    Angle &angle = entity->add<Sprite>()->angle;
    angle.lookAt(entity->box.getCenter(), targetPos);
    entity->box.position += angle.getVector() * 200 * deltaTime;

    if (Circle(entity->box.getCenter(), 10)
            .checkCollision(Circle(targetPos, 1))) {
      pickPosition();
    }
  }
}

void Drone::onDestroy() {}

void Drone::createInstance(Vector2f centerPosition) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = Vector2f(DRONE_SIZE) * 2;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity);
}

void Drone::configureInstance(Entity *entity) {
  if ((std::string)IMAGE_FILE != "") {
    Sprite *sprite = entity->add<Sprite>();
    sprite->image = {IMAGE_FILE};
  }

  entity->add<Enemy>();
  Drone *drone = entity->add<Drone>();

  entity->add<Scheduler>()->addSchedule(
      "move", 2000, [drone, entity]() { drone->pickPosition(); });
}
