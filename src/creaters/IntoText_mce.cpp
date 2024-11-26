#include "IntoText_mce.hpp"

#define ENTITY_TAG "{}"
#define IMAGE_FILE ""
#define SIZE {10000, 100000}

void IntoText::start() {}

void IntoText::update(float deltaTime) {
  if (InputManager::keyEvents[SDLK_SPACE]) {
    entity->toDestroy = true;
  }
}

void IntoText::createInstance(Vector2f centerPosition) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = SIZE;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity);
}

void IntoText::configureInstance(Entity *entity) {
  if ((std::string)IMAGE_FILE != "") {
    Sprite *sprite = entity->add<Sprite>();
    sprite->image = {IMAGE_FILE};
  }

  entity->renderPositionType = EntityRenderPositionType::Screen;
  entity->layer = 200;

  Text *textC = entity->add<Text>();
  textC->changeFont("res/fonts/ThaleahFat_TTF.ttf", 80);
  textC->text = "Bug in the System\n\n\n\nPress Space";
  textC->text_color = {255, 255, 255};

  entity->add<IntoText>();
}
