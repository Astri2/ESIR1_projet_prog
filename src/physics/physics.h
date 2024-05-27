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

struct rigid_body{
    std::vector<int> position;
    std::vector<int> size;

    aabb bounding_box;

    void move(int x,int y);
};

class physics {

public:
    physics();

    void check_and_collide( rigid_body & m_entity, const aabb & collide_box);

    void check_and_collide( rigid_body & m_entity, const std::vector<aabb> & collidables );
};