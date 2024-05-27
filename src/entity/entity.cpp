#include "entity.h"

entity::entity(float width, float height, float x, float y)
        : position({x, y}), size({width, height}) {}

entity::~entity(){}

void entity::move(float dx, float dy) {
    position.x += dx;
    position.y += dy;
}

void entity::move_to(float x, float y) {
    position.x = x;
    position.y = y;
}
