//
// Created by celia on 27/05/2024.
//
#pragma once

#include <cstdint>

#include "physics/circle.h"
#include "animated_sprite.h"
#include "collidable_entity.h"

class player : public animated_sprite, public collidable_entity
{
protected:
    const float max_health;
    float current_health;

public:
    enum class event : uint8_t {
        died
    };

public :
    player(vec2<float> pos, vec2<float> size, float max_health);
    void update(float dt) override;
    void damage(float damage_value);
    void heal(float benefit_value);
    int get_max_health() const;
    int get_current_health() const;
    circle get_interact_zone() const;

    void draw(const camera & cam) const override;
};

bool operator==(int32_t val, player::event e);
bool operator==(player::event e, int32_t val);
