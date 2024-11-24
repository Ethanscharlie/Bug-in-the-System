#include "MultiTurret_mce.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Bullet_mce.hpp"
#include "creaters/Explosion_mce.hpp"
#include "creaters/Light.hpp"

#define ENTITY_TAG "MultiTurret"
#define IMAGE_FILE "res/images/multiturret.png"
#define SIZE                                                                   \
  { 32, 32 }

void MultiTurret::start() {}

void MultiTurret::update(float deltaTime) {}

void MultiTurret::onDestroy() {}

void MultiTurret::createInstance(Vector2f centerPosition, float firerate,
                                 int directionCount) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = Vector2f(SIZE) * 4;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity, firerate, directionCount);
}

void MultiTurret::configureInstance(Entity *entity, float firerate,
                                    int directionCount) {
  Sprite *sprite = entity->add<Sprite>();
  sprite->addAnimation("fire",
                       generateSpritesheetAnimationButNotShit(
                           {"res/images/multiturret-sheet.png"}, 32),
                       0.1);
  sprite->image = {IMAGE_FILE};

  entity->layer = 1;

  MultiTurret *multiTurret = entity->add<MultiTurret>();
  multiTurret->firerate = firerate;
  multiTurret->directionCount = directionCount;
  entity->add<Scheduler>()->addSchedule(
      "fire", firerate, [entity, multiTurret] {
        if (entity->get<Enemy>()->allowFire) {
          entity->get<Sprite>()->animations["fire"]->play();
          for (int i = 0; i < multiTurret->directionCount; i++) {
            Angle &angle = multiTurret->angle;
            angle.rotate(360.0 / multiTurret->directionCount);
            Bullet::createInstance(entity->box.getCenter(), angle);
          }
        }
      });

  entity->add<Enemy>();
}
