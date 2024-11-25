#include "Enemy_component.hpp"
#include "AudioHeader.hpp"
#include "Light.hpp"
#include "creaters/Drone_mce.hpp"
#include "creaters/Explosion_mce.hpp"
#include "creaters/Light.hpp"

void Enemy::start() {
  tempPos = entity->box.position.y;
  entity->box.position.y -= 1000;

  light = GameManager::createEntity("Light");
  light->add<Alignment>()->parent = entity;
  createLight(light, Vector2f(0, -1000), 400, {255, 255, 255});
}

void Enemy::onDestroy() { light->toDestroy = true; }

void Enemy::update(float deltaTime) {
  if (shield) {
    light->get<Light>()->r += 400 * deltaTime;
    light->get<Light>()->g -= 300 * deltaTime;
    light->get<Light>()->b -= 300 * deltaTime;
  } else {

    light->get<Light>()->r = 220;
    light->get<Light>()->g = 0;
    light->get<Light>()->b = 0;
  }

  if (entity->box.position.y < tempPos && !allowFire) {
    entity->box.position.y += 300 * deltaTime;

  } else {
    allowFire = true;

    Circle myCircle(entity->box.getCenter(), 7);
    for (Entity *bullet : GameManager::getEntities("PlayerBullet")) {
      Circle bulletCircle(bullet->box.getCenter(), entity->box.size.y * 0.7);
      if (bulletCircle.checkCollision(myCircle) && !shield) {
        health--;
        bullet->toDestroy = true;
        Explosion::createInstance(entity->box.getCenter());
      }
    }

    if (health <= 0) {
      entity->toDestroy = true;
    }

    shield = false;
  }
}
