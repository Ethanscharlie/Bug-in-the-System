#include "Enemy_component.hpp"
#include <chrono>
#include <thread>

void Enemy::start() {
  tempPos = entity->box.position.y;
  entity->box.position.y -= 1000;
}

void Enemy::update(float deltaTime) {
  if (entity->box.position.y < tempPos) {
    entity->box.position.y += 300 * deltaTime;
  }
  
  Circle myCircle(entity->box.getCenter(), 7);
  for (Entity *bullet : GameManager::getEntities("PlayerBullet")) {
    Circle bulletCircle(bullet->box.getCenter(), entity->box.size.x / 2);
    if (bulletCircle.checkCollision(myCircle)) {
      entity->toDestroy = true;
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
      GameManager::lastTime = deltaTime;
    }
  }
}
