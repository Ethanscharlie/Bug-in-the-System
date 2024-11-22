#pragma once
#include "Charlie2D.hpp"

void createLight(Entity *entity, Vector2f centerPos, float distance,
                 std::array<Uint32, 3> color = {255, 255, 255});
