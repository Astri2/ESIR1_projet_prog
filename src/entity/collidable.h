//
// Created by tomch on 28/05/2024.
//

#pragma once

#include "physics/aabb.h"

class collidable {
public :
    virtual aabb get_collide_box() const = 0;
};