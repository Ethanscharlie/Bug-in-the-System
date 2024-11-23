#include "creaters/Bullet_mce.hpp"
#include "Alighnment.hpp"
#include "Light.hpp"
#include "Vector2f.hpp"
#include "AudioHeader.hpp"

#define ENTITY_TAG "Bullet"
#define IMAGE_FILE "res/images/bullet.png"
#define SIZE {16, 16}
int ENEMY_BULLET_SPEED = 400;

void Bullet::start() {
  light = GameManager::createEntity("Light");
  light->add<Alignment>()->parent = entity;
  createLight(light, Vector2f(0, 0), 100, {255, 0, 0});
}

void Bullet::onDestroy() { light->toDestroy = true; }

void Bullet::update(float deltaTime) {
  entity->box.position +=
      entity->get<Sprite>()->angle.getVector() * ENEMY_BULLET_SPEED * deltaTime;

  if (!entity->box.checkCollision(
          GameManager::getEntities("Background")[0]->box)) {
    entity->toDestroy = true;
  }
}

void Bullet::createInstance(Vector2f centerPosition, Angle direction) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = SIZE;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity, direction);
}

void Bullet::configureInstance(Entity *entity, Angle direction) {
  Audio sfx(AUDIO_ENEMY_FIRE);
  Mix_VolumeChunk(sfx.chunk, 40);
  sfx.play();

  Sprite *sprite = entity->add<Sprite>();
  sprite->image = {IMAGE_FILE};
  sprite->angle = direction;

  entity->add<Bullet>();
}
