//
// Created by tomch on 27/05/2024.
//
#pragma once

#include <vector>

#include "aabb.h"
#include "circle.h"

struct collidable;

namespace physics {

    bool are_colliding(const aabb & collide_1,const aabb & collide_2);
    bool are_colliding(const circle & collide_1,const circle & collide_2);

    void check_and_collide(collidable& entity, aabb const& obstacle);
    void check_and_collide(collidable& entity, std::vector<aabb> const& obstacles);

} // namespace physics
