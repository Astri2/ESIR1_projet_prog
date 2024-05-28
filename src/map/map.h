//
// Created by tomch on 28/05/2024.
//
#pragma once


#include "camera.h"
#include "cluster.h"
#include "entity/player.h"

namespace map {

    extern player *p;
    extern camera cam;

    void load_wsv(const char * file);

    void draw();
    void update(float dt);
    uint32_t find_cluster_idx(const vec2<float>& position);
    std::vector<cluster*> get_surrounding_clusters(uint32_t cluster_idx);

} // namespace map
