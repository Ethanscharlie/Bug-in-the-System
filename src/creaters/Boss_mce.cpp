#include "Boss_mce.hpp"
#include "Bullet_mce.hpp"
#include "Math.hpp"
#include "Scheduler.hpp"
#include "Vector2f.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Drone_mce.hpp"
#include "creaters/Explosion_mce.hpp"
#include "creaters/Light.hpp"
#include "creaters/MultiTurret_mce.hpp"
#include "creaters/Turret_mce.hpp"
#include <format>

#define ENTITY_TAG "{}"
#define IMAGE_FILE "res/images/boss.png"
Vector2f BOSS_SIZE = {128, 64};

void Boss::start() {}

void Boss::update(float deltaTime) {
  int health = entity->get<Enemy>()->health;

  if (GameManager::getComponents<Enemy>().size() > 1 || health <= 2) {
    entity->get<Enemy>()->shield = true;
    entity->get<Sprite>()->image = {"res/images/bloodthurstyboss.png"};
  } else {
    entity->get<Enemy>()->shield = false;
    entity->get<Sprite>()->image = {"res/images/boss.png"};

    if (healthLock == -1) {
      healthLock = health;
      delay = true;
      entity->add<Scheduler>()->addSchedule(
          "delay", 1000, [this]() { delay = false; }, true);
    }
  }

  if (blink) {
    entity->get<Sprite>()->image = {"res/images/bossnull.png"};
  }

  if (healthLock != -1) {
    if (health < healthLock) {
      health = healthLock - 1;
      if (!delay) {
        healthLock = -1;
        if (health == 6) {
          MultiTurret::createInstance({-500, 450});
          MultiTurret::createInstance({500, -450});
          Turret::createInstance({-350, 350}, 300, 60);
          Turret::createInstance({350, -350}, 300, 60);
        } else if (health == 5) {
          Turret::createInstance({0, 0}, 200, 70);
          Drone::createInstance({-500, -450});
          MultiTurret::createInstance({-500, 0}, 800, 4);
          Turret::createInstance({0, -200}, 200, 70);
        } else if (health == 4) {
          Turret::createInstance({0, 50}, 200, 50);
          Turret::createInstance({0, -50}, 200, 50);
          GameManager::getComponents<Turret>().back()->fireAngle.rotate(180);
          Drone::createInstance({-500, -450});
          Drone::createInstance({500, 450});
        } else if (health == 3) {
          Turret::createInstance({0, 50}, 200, 50);
          Turret::createInstance({0, -50}, 200, 50);
          GameManager::getComponents<Turret>().back()->fireAngle.rotate(180);
          Drone::createInstance({-500, -450});
          Drone::createInstance({500, 450});
        } else if (health == 2) {
          for (int i = 0; i < 8; i++) {
            entity->add<Scheduler>()->addSchedule(
                std::format("ex{}", i), randFloat(0, 9000), [this]() {
                  Explosion::createInstance(
                      {randFloat(entity->box.getLeft(), entity->box.getRight()),
                       randFloat(entity->box.getTop(),
                                 entity->box.getBottom())});
                });
            entity->add<Scheduler>()->addSchedule(
                std::format("end"), 9000,
                [this]() { entity->toDestroy = true; });
          }
        }
      }
    }
  }
}

void Boss::createInstance(Vector2f centerPosition, float fireRate,
                          float rotationSpeed) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = BOSS_SIZE * 4;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity, fireRate, rotationSpeed);
}

void Boss::configureInstance(Entity *entity, float fireRate,
                             float rotationSpeed) {
  if ((std::string)IMAGE_FILE != "") {
    Sprite *sprite = entity->add<Sprite>();
    sprite->image = {IMAGE_FILE};
  }

  entity->layer = 15;

  entity->add<Enemy>()->health = 7;
  Boss *boss = entity->add<Boss>();

  Turret::createInstance({-500, 0});
  Turret::createInstance({500, 0});

  entity->add<Scheduler>()->addSchedule(
      "blink", 500, [boss]() { boss->blink = !boss->blink; });
}
