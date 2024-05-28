//
// Created by tomch on 27/05/2024.
//

#include "interactible.h"

interactible::interactible(float x, float y, float interact_r) {
    interact_zone.rayon = interact_r;
    interact_zone.position = vec2<float>();
    interact_zone.position.x = x;
    interact_zone.position.y = y;
}

const circle & interactible::get_interact_zone() const{
    return interact_zone;
}
