#include "Enemy_component.hpp"

void Enemy::start() {
}

void Enemy::update(float deltaTime) {
  Circle myCircle(entity->box.getCenter(), 7);
  for (Entity *bullet : GameManager::getEntities("PlayerBullet")) {
    Circle bulletCircle(bullet->box.getCenter(), entity->box.size.x / 2);
    if (bulletCircle.checkCollision(myCircle)) {
      entity->toDestroy = true;
    }
  }
}
