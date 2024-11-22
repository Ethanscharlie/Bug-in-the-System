#include "creaters/Bullet_mce.hpp"
#include "Alighnment.hpp"
#include "Light.hpp"
#include "Vector2f.hpp"

#define ENTITY_TAG "{}"
#define IMAGE_FILE "res/images/bullet.png"
#define SIZE {16, 16}
int SPEED = 400;

void Bullet::start() {}

void Bullet::update(float deltaTime) {
  entity->box.position +=
      entity->get<Sprite>()->angle.getVector() * SPEED * deltaTime;
}

void Bullet::createInstance(Vector2f centerPosition, Angle direction) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = SIZE;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity, direction);
}

void Bullet::configureInstance(Entity *entity, Angle direction) {
  Sprite *sprite = entity->add<Sprite>();
  sprite->image = {IMAGE_FILE};
  sprite->angle = direction;

  Entity *light = GameManager::createEntity("Light");
  light->add<Alignment>()->parent = entity;
  createLight(light, Vector2f(0, 0), 100, {255, 0, 0});

  entity->add<Bullet>();
}
