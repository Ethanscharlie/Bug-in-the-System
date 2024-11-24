#include "Turret_mce.hpp"
#include "Bullet_mce.hpp"
#include "Math.hpp"
#include "Scheduler.hpp"
#include "Vector2f.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Explosion_mce.hpp"
#include "creaters/Light.hpp"

#define ENTITY_TAG "{}"
#define IMAGE_FILE "res/images/oneturret.png"
Vector2f SIZE = {32, 32};

void Turret::start() {}

void Turret::update(float deltaTime) {
  if (entity->get<Enemy>()->allowFire) {
    fireAngle.rotate(rotationSpeed * deltaTime);
    entity->get<Sprite>()->angle = fireAngle;
  }
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

  Sprite *sprite = entity->add<Sprite>();
  sprite->addAnimation(
      "fire", generateSpritesheetAnimationButNotShit({"res/images/oneturret-sheet.png"}, 32),
      0.1);
  sprite->image = {IMAGE_FILE};

  entity->add<Enemy>();
  Turret *turret = entity->add<Turret>();
  turret->rotationSpeed = rotationSpeed;
  turret->fireRate = fireRate;

  entity->layer = 1;

  entity->add<Scheduler>()->addSchedule("fire", fireRate, [entity, turret]() {
    if (entity->get<Enemy>()->allowFire) {
      Bullet::createInstance(entity->box.getCenter(), turret->fireAngle);
      entity->get<Sprite>()->animations["fire"]->play();
    }
  });
}
