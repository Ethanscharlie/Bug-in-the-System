#include "Levels.hpp"
#include "Event.hpp"
#include "Light.hpp"
#include "Math.hpp"
#include "Player_mce.hpp"
#include "SDL_keycode.h"
#include "SDL_mixer.h"
#include "SDL_timer.h"
#include "Scheduler.hpp"
#include "Vector2f.hpp"
#include "components/Enemy_component.hpp"
#include "creaters/Boss_mce.hpp"
#include "creaters/Bullet_mce.hpp"
#include "creaters/Drone_mce.hpp"
#include "creaters/Explosion_mce.hpp"
#include "creaters/MultiTurret_mce.hpp"
#include "creaters/PlayerBullet_mce.hpp"
#include "creaters/TextDrifter_mce.hpp"
#include "creaters/Turret_mce.hpp"
#include <format>

std::vector<std::function<void()>> levels = {
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
      Turret::createInstance({0, 50}, 70, 20);
      Turret::createInstance({0, -50}, 70, 20);
      GameManager::getComponents<Turret>().back()->fireAngle.rotate(180);
      ;
    },
    []() {
      Turret::createInstance({0, 50}, 70, 20);
      Turret::createInstance({0, -50}, 70, 20);
      GameManager::getComponents<Turret>().back()->fireAngle.rotate(180);
      Drone::createInstance({-500, -450});
      Drone::createInstance({500, 450});
      Drone::createInstance({0, 450});
      ;
    },
    []() {
      Turret::createInstance({0, 50}, 70, 20);
      Turret::createInstance({0, -50}, 70, 20);
      GameManager::getComponents<Turret>().back()->fireAngle.rotate(180);
      MultiTurret::createInstance({500, 0}, 600, 6);
      MultiTurret::createInstance({-500, 0}, 600, 6);
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
                      Mix_LoadMUS("res/audio/music/Juhani Junkala [Retro Game
                                  "
                                  "Music Pack] Level 3.wav");
                  Mix_PlayMusic(music, -1);
                },
                true);
      }

      Boss::createInstance({0, -300});
      Explosion::createInstance({0, 0});

      donttouchmusic = true;
      ;
    },
    []() {
      GameManager::getComponents<Player>()[0]
          ->entity->add<Scheduler>()
          ->addSchedule(
              "drama2", 10,
              []() {
                Mix_FreeMusic(music);
                music =
                    Mix_LoadMUS("res/audio/music/Juhani Junkala [Retro Game "
                                "Music Pack] Ending.wav");
                Mix_PlayMusic(music, -1);
              },
              true);

      GameManager::getComponents<Player>()[0]
          ->entity->add<Scheduler>()
          ->addSchedule(
              "text 1", 5000,
              []() {
                TextDrifter::createInstance({0, 400}, "Bug in the System");
              },
              true);
      GameManager::getComponents<Player>()[0]
          ->entity->add<Scheduler>()
          ->addSchedule(
              "text 2", 8000,
              []() {
                TextDrifter::createInstance({0, 200},
                                            "Created By Ethanscharlie");
              },
              true);
      GameManager::getComponents<Player>()[0]
          ->entity->add<Scheduler>()
          ->addSchedule(
              "text a", 11000,
              []() {
                TextDrifter::createInstance(
                    {0, 50},
                    "Time: " +
                        floatToString((SDL_GetTicks() - startTime) / 1000));
              },
              true);
      GameManager::getComponents<Player>()[0]
          ->entity->add<Scheduler>()
          ->addSchedule(
              "text f", 13000,
              []() {
                TextDrifter::createInstance({0, -40},
                                            std::format("Turns: {}", turns));
              },
              true);
      GameManager::getComponents<Player>()[0]
          ->entity->add<Scheduler>()
          ->addSchedule(
              "text 3", 16000,
              []() {
                TextDrifter::createInstance({0, -200}, "Thanks for Playing");
              },
              true);
      ;
    },
};
