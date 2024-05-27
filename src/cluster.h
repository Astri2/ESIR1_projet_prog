//
// Created by malo1 on 5/27/2024.
//

#pragma once


#include <set>
#include "entity/entity.h"
#include "entity/interactible.h"


class cluster {
private:
    // trying to add y sort comparator
    std::set<entity*> entities;
    std::set<interactible*> interactibles;
    aabb collision_box;
    //movables?
public:
    explicit cluster(const aabb& _collide_box);

    std::set<entity*>& get_entities();
    std::set<interactible*>& get_interactibles();
    const std::set<interactible*>& get_interactibles() const;
    const aabb& get_collision_box();
};
