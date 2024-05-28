//
// Created by tomch on 28/05/2024.
//

#include "collidable.h"

collidable::collidable(float top, float bottom, float left, float right){
    collide_box.top = top;
    collide_box.left = left;
    collide_box.bottom = bottom;
    collide_box.right = right;
}

const aabb & collidable::get_collide_box() const{
    return collide_box;
}