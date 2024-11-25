#include "TextDrifter_mce.hpp"
#include "Math.hpp"

#define ENTITY_TAG "{}"
#define IMAGE_FILE ""
#define SIZE                                                                   \
  { 10000, 10000 }

void TextDrifter::start() {
  tempPos = entity->box.position.y;
  entity->box.position.y -= 1000;
}

void TextDrifter::update(float deltaTime) {
  if (entity->box.position.y < tempPos) {
    entity->box.position.y += 300 * deltaTime;
  }
}

void TextDrifter::createInstance(Vector2f centerPosition, std::string text) {
  Entity *entity = GameManager::createEntity(ENTITY_TAG);
  entity->box.size = SIZE;
  entity->box.setWithCenter(centerPosition);
  configureInstance(entity, text);
}

void TextDrifter::configureInstance(Entity *entity, std::string text) {
  if ((std::string)IMAGE_FILE != "") {
    Sprite *sprite = entity->add<Sprite>();
    sprite->image = {IMAGE_FILE};
  }

  entity->renderPositionType = EntityRenderPositionType::Screen;
  entity->layer = 200;

  Text *textC = entity->add<Text>();
  textC->changeFont("res/fonts/ThaleahFat_TTF.ttf", 80);
  textC->text = text;
  textC->text_color = {255, 255, 255};

  entity->add<TextDrifter>();
}
