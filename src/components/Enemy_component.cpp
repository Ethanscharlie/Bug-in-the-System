#include "Enemy_component.hpp"
#include "AudioHeader.hpp"
#include "creaters/Drone_mce.hpp"

void Enemy::start() {
  tempPos = entity->box.position.y;
  entity->box.position.y -= 1000;
}

void Enemy::update(float deltaTime) {
  if (entity->box.position.y < tempPos && !allowFire) {
    entity->box.position.y += 300 * deltaTime;
  } else {
    allowFire = true;

    Circle myCircle(entity->box.getCenter(), 7);
    for (Entity *bullet : GameManager::getEntities("PlayerBullet")) {
      Circle bulletCircle(bullet->box.getCenter(), entity->box.size.x / 2);
      if (bulletCircle.checkCollision(myCircle)) {
        entity->toDestroy = true;
        bullet->toDestroy = true;
        Audio(ENEMY_DEATH_SOUND).play();
      }
    }
  }
}
