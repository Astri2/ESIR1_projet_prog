//
// Created by tomch on 28/05/2024.
//

#pragma once

#include "physics/circle.h"
#include <cstdint>
#include <iostream>

#include "animated_sprite.h"
#include "collidable_entity.h"
#include "interactible.h"

class cow : public animated_sprite, public collidable_entity, public interactible
{
protected:
    const float max_health;
    float current_health;
    float max_delai_interact = 2.0f;
    float delai_interact = max_delai_interact;

public :
    cow(vec2<float> pos, vec2<float> size, int max_health);
    void update(float dt) override;
    void damage(float damage_value);
    void benefit(float benefit_value);
    float get_max_health() const;
    float get_current_health() const;
    circle get_interact_zone() const override;

    void draw(const camera& cam) const override;

    void interact(player* user) override
    {
        if ( delai_interact >= max_delai_interact) {
            sprite_offset.y = 1;
            delai_interact = 0;
            user -> benefit(10.f);
        }

    }
};
