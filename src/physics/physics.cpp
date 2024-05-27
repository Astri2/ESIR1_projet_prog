//
// Created by tomch on 27/05/2024.
//

#include "aabb.h"
#include "physics.h"
// #include "entity/collidable.h"

bool physics::are_colliding(const aabb & collide_1,const aabb & collide_2){
    return !(
       collide_1.right < collide_2.left
    || collide_1.left > collide_2.right
    || collide_1.top > collide_2.bottom
    || collide_1.bottom > collide_2.top
    );
}

float physics::shared_distance(const circle & collide_1, const circle & collide_2) {
    return std::max( 0.0f , (collide_1.rayon + collide_2.rayon) - collide_1.position.distance(collide_2.position) ) ;
}

void physics::check_and_collide( entity & m_entity, const vec2 & dpos,const aabb & collide_box) {
    aabb check = m_entity.get_collide_box() + dpos;
    if ( !are_colliding(check,collide_box) ){
        m_entity.move(dpos.x,dpos.y);
    }
}

void physics::check_and_collide(entity & m_entity, const vec2 & dpos, const std::vector<aabb> & collidables){
    for (aabb collidable : collidables) {
        check_and_collide(m_entity,dpos,collidable);
    }
}