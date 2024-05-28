//
// Created by malo1 on 5/27/2024.
//

#pragma once


#include <set>
#include "entity/entity.h"
#include "entity/interactible.h"

struct compare {
    bool operator()(entity* a, entity* b) {
        return a->get_position().y < b->get_position().y;
    }
};

class cluster {
private:
    // trying to add y sort comparator
    std::set<entity*, compare> entities;
    std::set<interactible*, compare> interactibles;
    aabb collision_box;
    //movables?
public:
    explicit cluster(const aabb& _collide_box);

    std::set<entity*, compare>& get_entities();
    std::set<interactible*, compare>& get_interactibles();
    const std::set<interactible*, compare>& get_interactibles() const;
    const aabb& get_collision_box();
};
