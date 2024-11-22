#include "Player_mce.hpp"
#include "Event.hpp"
#include "SDL_keycode.h"
#include "Vector2f.hpp"

#define ENTITY_TAG "{}"
#define IMAGE_FILE "res/images/jet.png"
Vector2f SIZE_RATIO{17, 16};
int SCALE = 3;
float MOVE_SPEED = 500;

void Player::start() { turn(45); }

void Player::turn(float degrees) {
  direction.rotate(degrees);
  Sprite *sprite = entity->get<Sprite>();
  sprite->angle = direction;
}

void Player::moveForward() {
  entity->box.position +=
      direction.getVector() * MOVE_SPEED * GameManager::deltaTime;
}

void Player::update(float deltaTime) {
  if (InputManager::keyEvents[SDLK_SPACE]) {
    turn();
  }

  moveForward();
}

void Player::createInstance(Vector2f centerPosition) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = SIZE_RATIO * SCALE;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity);
}

void Player::configureInstance(Entity *entity) {
  Sprite *sprite = entity->add<Sprite>();
  sprite->image = {IMAGE_FILE};

  entity->add<Player>();
}
