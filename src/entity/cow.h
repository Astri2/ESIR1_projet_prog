//
// Created by tomch on 28/05/2024.
//

#pragma once

#include "physics/circle.h"
#include <cstdint>
#include "animated_sprite.h"
#include "collidable_entity.h"

class cow : public animated_sprite, public collidable_entity
{
protected:
    const uint32_t max_health;
    uint32_t current_health;

public :
    cow(vec2<float> pos, vec2<float> size, int max_health);
    void update(float dt) override;
    void damage(int damage_value);
    void benefit(int benefit_value);
    int get_max_health() const;
    int get_current_health() const;
    circle get_interact_zone() const;
};
