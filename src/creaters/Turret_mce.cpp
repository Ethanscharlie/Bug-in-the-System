#include "Turret_mce.hpp"
#include "Bullet_mce.hpp"
#include "Scheduler.hpp"
#include "Vector2f.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Light.hpp"

#define ENTITY_TAG "{}"
#define IMAGE_FILE "res/images/turret.png"
Vector2f SIZE = {32, 32};
float FIRE_RATE = 500;
float ROTATION_SPEED = 60;

void Turret::start() {
  entity->add<Scheduler>()->addSchedule("fire", FIRE_RATE, [this]() {
    Bullet::createInstance(entity->box.position, fireAngle);
  });

  light = GameManager::createEntity("Light");
  light->add<Alignment>()->parent = entity;
  createLight(light, Vector2f(0, 0), 400, {220, 0, 0});
}

void Turret::update(float deltaTime) {
  fireAngle.rotate(ROTATION_SPEED * deltaTime);
}

void Turret::onDestroy() { light->toDestroy = true; }

void Turret::createInstance(Vector2f centerPosition) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = SIZE * 3;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity);
}

void Turret::configureInstance(Entity *entity) {
  if ((std::string)IMAGE_FILE != "") {
    Sprite *sprite = entity->add<Sprite>();
    sprite->image = {IMAGE_FILE};
  }

  entity->add<Enemy>();

  entity->add<Turret>();
}
