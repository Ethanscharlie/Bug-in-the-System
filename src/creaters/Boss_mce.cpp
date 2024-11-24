#include "Boss_mce.hpp"
#include "Bullet_mce.hpp"
#include "Scheduler.hpp"
#include "Vector2f.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Light.hpp"

#define ENTITY_TAG "{}"
#define IMAGE_FILE "res/images/turret.png"
Vector2f BOSS_SIZE = {32, 32};

void Boss::start() {
  light = GameManager::createEntity("Light");
  light->add<Alignment>()->parent = entity;
  createLight(light, Vector2f(0, -1000), 400, {220, 0, 0});
}

void Boss::update(float deltaTime) {
  fireAngle.rotate(rotationSpeed * deltaTime);
}

void Boss::onDestroy() { light->toDestroy = true; }

void Boss::createInstance(Vector2f centerPosition, float fireRate,
                            float rotationSpeed) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = BOSS_SIZE * 3;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity, fireRate, rotationSpeed);
}

void Boss::configureInstance(Entity *entity, float fireRate,
                               float rotationSpeed) {
  if ((std::string)IMAGE_FILE != "") {
    Sprite *sprite = entity->add<Sprite>();
    sprite->image = {IMAGE_FILE};
  }

  entity->add<Enemy>()->health = 10;
  Boss *turret = entity->add<Boss>();
  turret->rotationSpeed = rotationSpeed;
  turret->fireRate = fireRate;

  entity->add<Scheduler>()->addSchedule("fire", fireRate, [entity, turret]() {
    if (entity->get<Enemy>()->allowFire) {
      Bullet::createInstance(entity->box.getCenter(), turret->fireAngle);
    }
  });
}
