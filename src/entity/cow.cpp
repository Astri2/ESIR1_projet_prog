//
// Created by tomch on 28/05/2024.
//

#include "cow.h"

#include <algorithm>
#include "renderer.h"
#include "map/map.h"


cow::cow(vec2<float> pos, vec2<float> size, float max_health) :
        entity(pos),

        pnj(pos, size, max_health, aabb{24, 24, 32, 8}, {{32, 32}}, "../resources/cow.png", {3, 3, 2}) {
}

void cow::update(float dt) {
    pnj::update(dt);

    if (delai_interact >= max_delai_interact) {
        sprite_offset.y = 0;
    } else {
        delai_interact += dt;
    }
}

void cow::damage(float damage_value)
{
    current_health = std::max(current_health - damage_value, 0.f);
}

void cow::heal(float benefit_value)
{
    current_health = std::min(benefit_value + current_health, max_health);
}

float cow::get_max_health() const
{
    return max_health;
}

float cow::get_current_health() const
{
    return current_health;
}

void cow::interact(player* user) {
    if (delai_interact >= max_delai_interact) {
        sprite_offset.y = 1;
        delai_interact = 0;


        float f = user -> get_current_food();
        if (f >= 10){
            user->heal(10);
            user->lose_food(10);
        }
    }
}
