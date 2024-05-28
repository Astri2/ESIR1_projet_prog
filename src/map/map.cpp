//
// Created by tomch on 28/05/2024.
//
#include <fstream>
#include <iostream>

#include <cstring> // memset 0
#include <cassert>

#include "map.h"
#include "entity/entity.h"

#include "serializer.h"

map::map(unsigned int _width, unsigned int _height) {
    serializer::map data = serializer::deserialize("../resources/test.map");

    constexpr uint16_t cw = config::map::cluster_width;
    constexpr uint16_t ch = config::map::cluster_height;

    this->nb_clusters_x = std::ceil((float)data.header.width/cw);
    this->nb_clusters_y = std::ceil((float)data.header.height/ch);
    for(unsigned int x = 0; x < this->nb_clusters_x ; x++) {
        for(unsigned int y = 0 ; y < this->nb_clusters_y ; y++) {
            this->clusters.push_back(
                    cluster({
                        static_cast<float>(y*ch),
                        static_cast<float>((x+1)*cw),
                        static_cast<float>((y+1)*ch),
                        static_cast<float>(x*cw)
                    })
            );
        }
    }

    for(serializer::map_row& row : data.data) {
        uint32_t idx = this->find_cluster_idx(row.position);
        switch (row.type) {
            case serializer::map_row::entity_type::tile: {
                this->clusters[idx].background.push_back(
                    new sprite(
                        row.position,
                        {{ config::map::tile_width, config::map::tile_height }},
                        {{ row.tile.i, row.tile.j }},
                        {{ 16, 16 }},
                        texture_manager::atlases_name[(size_t)row.tile.atlas_id].c_str()
                    )
                );
            } break;

            case serializer::map_row::entity_type::animated_tile: {
                // this->clusters[idx].background.push_back();
                std::cerr << "Not implemented yet !" << std::endl;
            } break;

            case serializer::map_row::entity_type::player: {
                player* p = new player(row.position, {{ 48, 48 }}, 100);
                this->clusters[idx].foreground.insert(p);
                this->clusters[idx].collidables.insert(p);
                // create the camera so we can see something
            } break;
        }
    }
}

void map::draw() {

}

void map::update() {

}

// protected utilities

uint32_t map::find_cluster_idx(const vec2<float>& position) const {
    return ((int)position.y/config::map::cluster_height)*this->nb_clusters_x + ((int)position.x/config::map::cluster_width);
}

std::vector<cluster*> map::get_surrounding_clusters(uint32_t cluster_idx) {
    std::vector<cluster*> res;
    for(int i = -1 ; i < 2 ; i++) {
        for(int j = -1 ; j < 2 ; j++) {
            uint32_t idx = cluster_idx + i * this->nb_clusters_x + j;
            // assuming negatives values aren't to negatives, could use boolean logic in for boundaries instead
            if(idx < this->nb_clusters_x * this->nb_clusters_y)
                res.push_back(&clusters[idx]);
        }
    }
    return res;
}

std::vector<cluster const*> map::get_cluster_to_blit(const camera & camera) const {

    // computes the rectangle of clusters that should be blit, given the top_left and bottom_right clusters
    const uint32_t top_left_cluster_idx = find_cluster_idx({camera.get_outer_range().top_left()});
    const uint32_t bottom_right_cluster_idx = find_cluster_idx({camera.get_outer_range().bottom_right()});
    const uint32_t dx = (bottom_right_cluster_idx-top_left_cluster_idx)/this->nb_clusters_x;
    const uint32_t dy = (bottom_right_cluster_idx-top_left_cluster_idx)%this->nb_clusters_x;

    std::vector<cluster const*> res(dx*dy);
    for(uint32_t i = 0 ; i < dx ; i++) {
        for(uint32_t j = 0 ; j < dy ; j++) {
            uint32_t idx = top_left_cluster_idx + i * this->nb_clusters_x + j;
            res.push_back(&clusters[idx]);
        }
    }
    return res;
}
