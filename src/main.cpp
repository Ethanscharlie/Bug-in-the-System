#include "Charlie2D.hpp"
#include "Vector2f.hpp"
#include "creaters/Player_mce.hpp"
#include "creaters/Turret_mce.hpp"
#include <functional>
#include <iostream>
#include <vector>

bool musicHasBeenStarted = false;

void play_music() {
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    fprintf(stderr, "Could not initialize SDL_mixer: %s\n", Mix_GetError());
  }

  music = Mix_LoadMUS(
      "res/audio/music/Juhani Junkala [Retro Game Music Pack] Level 2.wav");
  if (!music) {
    fprintf(stderr, "Failed to load music: %s\n", Mix_GetError());
    Mix_CloseAudio();
  }

  Mix_VolumeMusic(60);

  if (Mix_PlayMusic(music, -1) == -1) {
    fprintf(stderr, "Failed to play music: %s\n", Mix_GetError());
  }
}

int main(int, char **) {
  GameManager::init();
  GameManager::shadowFilter->shadowFilterTint = {60, 60, 60};

#ifdef __EMSCRIPTEN__
  Event::addEventListener("LeftMouseButtonDown", []() {
    if (!musicHasBeenStarted)
      play_music();
    musicHasBeenStarted = true;
  });
#else
  play_music();
#endif

  Entity *background = GameManager::createEntity("Background");
  background->layer = -10;
  background->box.size = GameManager::gameWindowSize;
  background->box.setWithCenter({0, 0});
  background->add<Sprite>()->image = {"res/images/background.png"};

  Player::createInstance({0, 0});

  GameManager::doUpdateLoop();
  return 0;
}
