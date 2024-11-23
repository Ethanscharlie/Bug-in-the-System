#include "MultiTurret_mce.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Bullet_mce.hpp"
#include "creaters/Light.hpp"

#define ENTITY_TAG "MultiTurret"
#define IMAGE_FILE "res/images/turret.png"
#define SIZE                                                                   \
  { 32, 32 }

void MultiTurret::start() {
  light = GameManager::createEntity("Light");
  light->add<Alignment>()->parent = entity;
  createLight(light, Vector2f(0, -1000), 400, {220, 0, 0});
}

void MultiTurret::update(float deltaTime) {}

void MultiTurret::onDestroy() { light->toDestroy = true; }

void MultiTurret::createInstance(Vector2f centerPosition, float firerate,
                                 int directionCount) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = Vector2f(SIZE) * 2;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity);
}

void MultiTurret::configureInstance(Entity *entity, float firerate,
                                    int directionCount) {
  Sprite *sprite = entity->add<Sprite>();
  sprite->image = {IMAGE_FILE};

  MultiTurret *multiTurret = entity->add<MultiTurret>();
  multiTurret->firerate = firerate;
  multiTurret->directionCount = directionCount;
  entity->add<Scheduler>()->addSchedule(
      "fire", firerate, [entity, multiTurret] {
        if (entity->get<Enemy>()->allowFire) {
          for (int i = 0; i < multiTurret->directionCount; i++) {
            Angle &angle = multiTurret->angle;
            angle.rotate(360.0 / multiTurret->directionCount);
            Bullet::createInstance(entity->box.getCenter(), angle);
          }
        }
      });

  entity->add<Enemy>();
}
