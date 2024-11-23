#include "Player_mce.hpp"
#include "Event.hpp"
#include "Light.hpp"
#include "SDL_keycode.h"
#include "Vector2f.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Bullet_mce.hpp"
#include "creaters/Drone_mce.hpp"
#include "creaters/MultiTurret_mce.hpp"
#include "creaters/PlayerBullet_mce.hpp"
#include "creaters/Turret_mce.hpp"
#include <format>

#define ENTITY_TAG "{}"
#define IMAGE_FILE "res/images/jet.png"
Vector2f SIZE_RATIO{17, 16};
int SCALE = 3;
float MOVE_SPEED = 500;

std::vector<std::function<void()>> levels = {
    []() {
      Drone::createInstance({0, 0});
      ;
    },
    []() {
      Turret::createInstance({0, 0});
      ;
    },
    []() {
      Turret::createInstance({0, -250});
      Turret::createInstance({500, 0});
      Turret::createInstance({-500, 0});
      ;
    },
    []() {
      MultiTurret::createInstance({0, -200}, 60);
      ;
    },
    []() {
      MultiTurret::createInstance({-500, 0}, 20);
      Turret::createInstance({200, 0});
      ;
    },
    []() {
      MultiTurret::createInstance({-400, -400}, 60);
      MultiTurret::createInstance({400, 400}, 60);
      ;
    },
};

int currentLevel = 0;

static void loadLevel(int levelIndex) {
  std::cout << std::format("NEXT LEVEL: {}\n", levelIndex);
  levels[levelIndex]();
}

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
  // Movement
  if (InputManager::keyEvents[SDLK_SPACE]) {
    turn();
    PlayerBullet::createInstance(entity->box.getCenter(), direction);
  }

  moveForward();

  // Reflection
  if (entity->box.position.x < -GameManager::gameWindowSize.x / 2) {
    entity->box.position.x = GameManager::gameWindowSize.x / 2;
  } else if (entity->box.position.x > GameManager::gameWindowSize.x / 2) {
    entity->box.position.x = -GameManager::gameWindowSize.x / 2;
  } else if (entity->box.position.y < -GameManager::gameWindowSize.y / 2) {
    entity->box.position.y = GameManager::gameWindowSize.y / 2;
  } else if (entity->box.position.y > GameManager::gameWindowSize.y / 2) {
    entity->box.position.y = -GameManager::gameWindowSize.y / 2;
  }

  // Collisions
  auto onPlayerDeath([&]() {
    for (Enemy *enemy : GameManager::getComponents<Enemy>()) {
      enemy->entity->toDestroy = true;
    }
    for (Bullet *bullet : GameManager::getComponents<Bullet>()) {
      bullet->entity->toDestroy = true;
    }

    entity->box.position = {0, 0};
    loadLevel(currentLevel - 1);
  });

  Circle playerCircle(entity->box.getCenter(), 7);
  for (Entity *bullet : GameManager::getEntities("Bullet")) {
    Circle bulletCircle(bullet->box.getCenter(), bullet->box.size.x / 2);
    if (bulletCircle.checkCollision(playerCircle)) {
      onPlayerDeath();
    }
  }
  for (Enemy *enemy : GameManager::getComponents<Enemy>()) {
    Circle enemyCircle(enemy->entity->box.getCenter(),
                       enemy->entity->box.size.x / 2);
    if (enemyCircle.checkCollision(playerCircle)) {
      onPlayerDeath();
    }
  }

  // Level
  if (GameManager::getComponents<Enemy>().size() <= 0) {
    if (levels.size() > currentLevel) {
      loadLevel(currentLevel);
      currentLevel++;
    }
  }
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

  Entity *light = GameManager::createEntity("Light");
  light->add<Alignment>()->parent = entity;
  createLight(light, Vector2f(0, 0), 100, {255, 255, 200});

  entity->add<Player>();
}
