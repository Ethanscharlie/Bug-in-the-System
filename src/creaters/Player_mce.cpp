#include "Player_mce.hpp"
#include "Event.hpp"
#include "Light.hpp"
#include "SDL_keycode.h"
#include "SDL_mixer.h"
#include "Scheduler.hpp"
#include "Vector2f.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Boss_mce.hpp"
#include "creaters/Bullet_mce.hpp"
#include "creaters/Drone_mce.hpp"
#include "creaters/Explosion_mce.hpp"
#include "creaters/MultiTurret_mce.hpp"
#include "creaters/PlayerBullet_mce.hpp"
#include "creaters/Turret_mce.hpp"
#include <format>

#define ENTITY_TAG "{}"
#define IMAGE_FILE "res/images/jet.png"
Vector2f SIZE_RATIO{17, 16};
int SCALE = 3;
float MOVE_SPEED = 500;

static bool donttouchmusic = false;

std::vector<std::function<void()>> levels = {
    []() {
      Boss::createInstance({0, -300});
      Explosion::createInstance({0,0});
      ;
    },
    []() {
      Turret::createInstance({0, 0});
      ;
    },
    []() {
      Turret::createInstance({-500, 0});
      Turret::createInstance({500, 0});
      ;
    },
    []() {
      Turret::createInstance({-500, 0});
      Turret::createInstance({500, 0});
      Turret::createInstance({0, -200}, 300, 70);
      ;
    },
    []() {
      Turret::createInstance({-500, 0});
      Turret::createInstance({500, 0});
      Turret::createInstance({-500, -450}, 2000, 30);
      Turret::createInstance({500, 450}, 2000, 30);
      ;
    },
    []() {
      MultiTurret::createInstance({0, 0});
      ;
    },
    []() {
      MultiTurret::createInstance({0, 0});
      Turret::createInstance({500, 0});
      Turret::createInstance({-500, -450}, 2000, 30);
      Turret::createInstance({500, 450}, 2000, 30);
      ;
    },
    []() {
      MultiTurret::createInstance({-500, 450});
      MultiTurret::createInstance({500, -450});
      ;
    },
    []() {
      MultiTurret::createInstance({0, 0}, 200, 3);
      Turret::createInstance({-500, 200}, 200, 70);
      Turret::createInstance({500, 200}, 200, 70);
      Turret::createInstance({0, -200}, 200, 90);
      ;
    },
    []() {
      MultiTurret::createInstance({-500, 450});
      MultiTurret::createInstance({500, -450});
      Turret::createInstance({-350, 350}, 300, 60);
      Turret::createInstance({350, -350}, 300, 60);
      ;
    },
    []() {
      Drone::createInstance({-500, -300});
      Drone::createInstance({500, -300});
      ;
    },
    []() {
      Drone::createInstance({500, -300});
      Drone::createInstance({500, 450});
      Turret::createInstance({-500, 0}, 180, 100);
      ;
    },
    []() {
      Drone::createInstance({500, -300});
      Drone::createInstance({500, 450});
      Turret::createInstance({-500, 200}, 200, 70);
      Turret::createInstance({500, 200}, 200, 70);
      Turret::createInstance({0, -200}, 200, 90);
      ;
    },
    []() {
      MultiTurret::createInstance({-500, 450});
      MultiTurret::createInstance({500, -450});
      Drone::createInstance({-500, -450});
      Drone::createInstance({500, 450});
      Drone::createInstance({0, 450});
      Drone::createInstance({500, 0});
      ;
    },
    []() {
      Drone::createInstance({-500, -450});
      Drone::createInstance({500, 450});
      ;
    },
    []() {
      MultiTurret::createInstance({-500, 450});
      MultiTurret::createInstance({500, -450});
      Drone::createInstance({-500, -450});
      Drone::createInstance({500, 450});
      Turret::createInstance({-500, 0}, 180, 100);
      Turret::createInstance({500, 0}, 180, 100);
      ;
    },
    []() {
      MultiTurret::createInstance({0, 0}, 200, 6);
      Drone::createInstance({-500, -450});
      Drone::createInstance({500, 450});
      ;
    },
    []() {
      MultiTurret::createInstance({0, 0}, 200, 6);
      Drone::createInstance({500, 450});
      Turret::createInstance({-500, 0}, 180, 100);
      Turret::createInstance({500, 0}, 180, 100);
      ;
    },
    []() {
      Turret::createInstance({0, 0}, 70, 70);
      ;
    },
    []() {
      Turret::createInstance({0, 0}, 70, 70);
      Drone::createInstance({-500, -450});
      Drone::createInstance({500, 450});
      Drone::createInstance({0, 450});
      Drone::createInstance({500, 0});
      ;
    },
    []() {
      Turret::createInstance({0, 0}, 70, 70);
      Drone::createInstance({-500, -450});
      MultiTurret::createInstance({-500, 0}, 800, 4);
      Turret::createInstance({500, 0}, 200, 70);
      Turret::createInstance({0, -200}, 200, 70);
      ;
    },
    []() {
      Turret::createInstance({0, 50}, 70, 50);
      Turret::createInstance({0, -50}, 70, 50);
      GameManager::getComponents<Turret>().back()->fireAngle.rotate(180);
      ;
    },
    []() {
      Turret::createInstance({0, 50}, 70, 50);
      Turret::createInstance({0, -50}, 70, 50);
      GameManager::getComponents<Turret>().back()->fireAngle.rotate(180);
      Drone::createInstance({-500, -450});
      Drone::createInstance({500, 450});
      Drone::createInstance({0, 450});
      Drone::createInstance({500, 0});
      ;
    },
    []() {
      Turret::createInstance({0, 50}, 70, 50);
      Turret::createInstance({0, -50}, 70, 50);
      GameManager::getComponents<Turret>().back()->fireAngle.rotate(180);
      MultiTurret::createInstance({500, 0}, 600, 6);
      Turret::createInstance({0, -200}, 200, 70);
      ;
    },
    []() {
      Mix_HaltMusic();
      Turret::createInstance({0, 0});
      ;
    },
    []() {
      if (!donttouchmusic) {
        GameManager::getComponents<Player>()[0]
            ->entity->add<Scheduler>()
            ->addSchedule(
                "drama", 4000,
                []() {
                  Mix_FreeMusic(music);
                  music =
                      Mix_LoadMUS("res/audio/music/Juhani Junkala [Retro Game "
                                  "Music Pack] Level 3.wav");
                  Mix_PlayMusic(music, -1);
                },
                true);
      }

      donttouchmusic = true;

      Turret::createInstance({0, 50}, 70, 50);
      Turret::createInstance({0, -50}, 70, 50);
      GameManager::getComponents<Turret>().back()->fireAngle.rotate(180);
      Drone::createInstance({-500, -450});
      MultiTurret::createInstance({-500, 0}, 800, 4);
      MultiTurret::createInstance({500, 0}, 600, 6);
      Turret::createInstance({0, -200}, 200, 70);
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
    Circle bulletCircle(bullet->box.getCenter(), bullet->box.size.x);
    if (bulletCircle.checkCollision(playerCircle)) {
      onPlayerDeath();
    }
  }
  for (Enemy *enemy : GameManager::getComponents<Enemy>()) {
    Circle enemyCircle(enemy->entity->box.getCenter(),
                       enemy->entity->box.size.y / 2);
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
