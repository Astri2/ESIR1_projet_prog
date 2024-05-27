//
// Created by celia on 27/05/2024.
//
#pragma once

#include "entity.h"
#include "physics/circle.h"

class player : public entity {
protected:
    circle interact_zone;
    const int max_health;
    int current_health;
public :
    player(float x, float y, float width, float height, int max_health, float interact_r);
    virtual ~player() override;
    virtual void draw() override;
    virtual void update(float dt) override;
    int get_max_health() const;
    int get_current_health() const;
    const circle & get_interact_zone() const;
};
