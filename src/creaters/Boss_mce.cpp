#include "Boss_mce.hpp"
#include "Bullet_mce.hpp"
#include "Scheduler.hpp"
#include "Vector2f.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Light.hpp"
#include "creaters/Turret_mce.hpp"

#define ENTITY_TAG "{}"
#define IMAGE_FILE "res/images/boss.png"
Vector2f BOSS_SIZE = {128, 64};

void Boss::start() {
  light = GameManager::createEntity("Light");
  light->add<Alignment>()->parent = entity;
  createLight(light, Vector2f(0, -1000), 400, {220, 0, 0});
}

void Boss::update(float deltaTime) {}

void Boss::onDestroy() { light->toDestroy = true; }

void Boss::createInstance(Vector2f centerPosition, float fireRate,
                          float rotationSpeed) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = BOSS_SIZE * 4;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity, fireRate, rotationSpeed);
}

void Boss::configureInstance(Entity *entity, float fireRate,
                             float rotationSpeed) {
  if ((std::string)IMAGE_FILE != "") {
    Sprite *sprite = entity->add<Sprite>();
    sprite->image = {IMAGE_FILE};
  }

  entity->layer = 15;

  entity->add<Enemy>()->health = 10;
  Boss *boss = entity->add<Boss>();
  // turret->rotationSpeed = rotationSpeed;
  // turret->fireRate = fireRate;
  //
  entity->add<Scheduler>()->addSchedule("fire", 1000, [entity, boss]() {
    if (entity->get<Enemy>()->allowFire &&
        GameManager::getComponents<Enemy>().size() <= 1) {
      Turret::createInstance({-500, 0});
      Turret::createInstance({500, 0});
    }
  });
}
