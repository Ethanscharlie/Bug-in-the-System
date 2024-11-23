#include "creaters/PlayerBullet_mce.hpp"
#include "Alighnment.hpp"
#include "AudioHeader.hpp"
#include "Light.hpp"
#include "Vector2f.hpp"

#define ENTITY_TAG "PlayerBullet"
#define IMAGE_FILE "res/images/bullet.png"
#define SIZE                                                                   \
  { 16, 16 }
int PLAYER_BULLET_SPEED = 1200;

void PlayerBullet::start() {
  light = GameManager::createEntity("Light");
  light->add<Alignment>()->parent = entity;
  createLight(light, Vector2f(0, 0), 100, {0, 255, 0});
}

void PlayerBullet::update(float deltaTime) {
  entity->box.position += entity->get<Sprite>()->angle.getVector() *
                          PLAYER_BULLET_SPEED * deltaTime;
}

void PlayerBullet::createInstance(Vector2f centerPosition, Angle direction) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = SIZE;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity, direction);
}

void PlayerBullet::onDestroy() { light->toDestroy = true; }

void PlayerBullet::configureInstance(Entity *entity, Angle direction) {
  Audio(AUDIO_PLAYER_FIRE).play();

  Sprite *sprite = entity->add<Sprite>();
  sprite->image = {IMAGE_FILE};
  sprite->image.color = {255, 255, 0};
  sprite->angle = direction;

  entity->add<PlayerBullet>();
}
