#include "Turret_mce.hpp"
#include "Bullet_mce.hpp"
#include "Scheduler.hpp"
#include "Vector2f.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Light.hpp"

#define ENTITY_TAG "{}"
#define IMAGE_FILE "res/images/turret.png"
Vector2f SIZE = {32, 32};

void Turret::start() {}

void Turret::update(float deltaTime) {
  fireAngle.rotate(rotationSpeed * deltaTime);
}

void Turret::onDestroy() {}

void Turret::createInstance(Vector2f centerPosition, float fireRate,
                            float rotationSpeed) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = SIZE * 3;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity, fireRate, rotationSpeed);
}

void Turret::configureInstance(Entity *entity, float fireRate,
                               float rotationSpeed) {
  if ((std::string)IMAGE_FILE != "") {
    Sprite *sprite = entity->add<Sprite>();
    sprite->image = {IMAGE_FILE};
  }

  entity->add<Enemy>();
  Turret *turret = entity->add<Turret>();
  turret->rotationSpeed = rotationSpeed;
  turret->fireRate = fireRate;

  entity->add<Scheduler>()->addSchedule("fire", fireRate, [entity, turret]() {
    if (entity->get<Enemy>()->allowFire) {
      Bullet::createInstance(entity->box.getCenter(), turret->fireAngle);
    }
  });
}
