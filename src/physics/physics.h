//
// Created by tomch on 27/05/2024.
//

#pragma once

#include <vector>

struct aabb{
    float left;
    float right;
    float bottom;
    float top;
};

struct collidable{
    aabb get_collide_box();
    void move(float x, float y);
};

class physics {

public:
    physics();

    void check_and_collide( collidable & m_entity, const aabb & collide_box);

    void check_and_collide( collidable & m_entity, const std::vector<aabb> & collidables );
};