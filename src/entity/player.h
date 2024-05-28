//
// Created by celia on 27/05/2024.
//
#pragma once

#include "entity.h"
#include "physics/circle.h"
#include "SDL_scancode.h"
#include <cstdint>
#include <cassert>

#include "physics/collidable.h"
#include "animated_sprite.h"
#include "collidable_entity.h"

class player : public animated_sprite, public collidable_entity {
protected:
    const uint32_t max_health;
    uint32_t current_health;

    int32_t keyboard_size;
    const uint8_t* keyboard_state;
public :
    player(vec2<float> pos, vec2<float> size, int max_health);
    void update(float dt) override;
    void damage(int damage_value);
    void benefit(int benefit_value);
    int get_max_health() const;
    int get_current_health() const;
    const circle get_interact_zone() const;

private:
    bool is_key_pressed(SDL_Scancode scancode) {
        assert(scancode < keyboard_size);
        return keyboard_state[scancode];

    }
};
