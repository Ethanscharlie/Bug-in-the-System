#include "Explosion_mce.hpp"
#include "Math.hpp"
#include "creaters/Light.hpp"

#define ENTITY_TAG "{}"
#define SIZE                                                                   \
  { 17, 17 }

void Explosion::start() {
  light = GameManager::createEntity("Light");
  light->add<Alignment>()->parent = entity;
  createLight(light, Vector2f(0, -1000), 400, {220, 0, 0});
}

void Explosion::update(float deltaTime) {}

void Explosion::onDestroy() { light->toDestroy = true; }

static std::vector<Image>
generateSpritesheetAnimationButNotShit(Image image, int gridSize = 16,
                                       int row = 0) {
  int width, height;
  SDL_QueryTexture(image.texture, nullptr, nullptr, &width, &height);

  int gridWidth = width / gridSize;
  int gridHeight = height / gridSize;

  if (gridHeight < row) {
    throw std::runtime_error("Row was to high in animation");
  }

  std::vector<Image> frames;
  int y = row * gridSize;
  for (int x = 0; x < gridSize * gridWidth; x += gridSize) {
    Image frame = image;
    frame.srcRect = {x, y, gridSize, gridSize};
    frames.push_back(frame);
  }

  return frames;
}

void Explosion::createInstance(Vector2f centerPosition) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = SIZE;
  entity->box.size *= 5;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity);
}

void Explosion::configureInstance(Entity *entity) {
  entity->layer = 20;

  Sprite *sprite = entity->add<Sprite>();
  // sprite->image = {"res/images/explosionsTrimmed.png"};
  sprite->addAnimation("go",
                       generateSpritesheetAnimationButNotShit(
                           {"res/images/explosionsTrimmed.png"}, 17),
                       0.05);
  sprite->animations["go"]->play(1, [entity]() { entity->toDestroy = true; });

  entity->add<Explosion>();
}
