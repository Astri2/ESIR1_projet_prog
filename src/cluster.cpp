//
// Created by malo1 on 5/27/2024.
//

#include "cluster.h"

cluster::cluster(const aabb &_collide_box): collision_box(_collide_box) {

}

std::set<entity *, compare> &cluster::get_entities() {
    return this->entities;
}

std::set<interactible *, compare> &cluster::get_interactibles() {
    return this->interactibles;
}

const std::set<interactible *, compare> &cluster::get_interactibles() const{
    return this->interactibles;
}

const aabb &cluster::get_collision_box() {
    return this->collision_box;
}
