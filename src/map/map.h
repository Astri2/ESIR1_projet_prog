//
// Created by tomch on 28/05/2024.
//
#pragma once

#include <vector>

#include "camera.h"
#include "config.h"
#include "cluster.h"
#include "entity/player.h"

#include "utils/vec2.h"

namespace map {

    extern player *p;
    extern camera cam;

    void load_wsv(const char * file);

    void draw();
    void update(float dt);


    extern std::vector<cluster> clusters;
    uint32_t find_cluster_idx(const vec2<float>& position);
} // namespace map
