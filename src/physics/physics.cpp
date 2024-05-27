//
// Created by tomch on 27/05/2024.
//

#include "physics.h"
// #include "entity/collidable.h"

bool physics::are_colliding(const aabb & collide_1,const aabb & collide_2){
    return ( collide_1.left < collide_2.left && collide_2.left < collide_1.right )
        || ( collide_1.left < collide_2.right && collide_2.right < collide_1.right )
        || ( collide_1.top < collide_2.bottom && collide_2.bottom < collide_1.bottom )
        || ( collide_1.top < collide_2.top && collide_2.top < collide_1.bottom )
    ;
}

bool physics::are_colliding(const circle & collide_1,const circle & collide_2) {
    return collide_1.position.distance(collide_2.position) < collide_1.rayon + collide_2.rayon;
}

void physics::check_and_collide( collidable & m_entity, const aabb & collide_box) {
    aabb entity_box /* = m_entity.get_collide_box()*/;

    float mx = 0;
    float my = 0;

    if ( collide_box.left < entity_box.left && entity_box.left < collide_box.right ) {
        mx = collide_box.right - entity_box.left;
    }
    else if ( collide_box.left < entity_box.right && entity_box.right < collide_box.right ){
        mx = collide_box.left - entity_box.right;
    }

    if ( collide_box.top < entity_box.bottom && entity_box.bottom < collide_box.bottom ) {
        my = collide_box.top - entity_box.bottom;
    }
    else if ( collide_box.top < entity_box.top && entity_box.top < collide_box.bottom ){
        my = collide_box.bottom - entity_box.top;
    }

    // m_entity.move(mx, my);
}

void physics::check_and_collide(collidable & m_entity, const std::vector<aabb> & collidables){
    for (aabb collidable : collidables) {
        check_and_collide(m_entity,collidable);
    }
}