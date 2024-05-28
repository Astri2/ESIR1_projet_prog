//
// Created by tomch on 28/05/2024.
//

#include "map.h"

map::map(unsigned int _width, unsigned int _height){
    float cw = config::map::cluster_width;
    float ch = config::map::cluster_height;
    // ça devrait se baser sur la map, pas sur la fenetre de jeu
    this->nb_clusters_x = std::ceil(_width/cw);
    this->nb_clusters_y = std::ceil(_height/ch);
    for(unsigned int x = 0; x < this->nb_clusters_x ; x++) {
        for(unsigned int y = 0 ; y < this->nb_clusters_y ; y++) {
            this->clusters.push_back(cluster({y*ch,(x+1)*cw,(y+1)*ch,x*cw}));
        }
    }
    //might be worth storing it inside entity
    unsigned int player_cluster_idx = find_cluster_idx(p->get_position());
    clusters[player_cluster_idx].entities.insert(p);
}


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

std::vector<cluster *> map::get_cluster_to_blit(const camera & camera) const {

    // computes the rectangle of clusters that should be blit, given the top_left and bottom_right clusters
    const uint32_t top_left_cluster_idx = find_cluster_idx({camera.get_outer_range().top_left()});
    const uint32_t bottom_right_cluster_idx = find_cluster_idx({camera.get_outer_range().bottom_right()});
    const uint32_t dx = (bottom_right_cluster_idx-top_left_cluster_idx)/this->nb_clusters_x;
    const uint32_t dy = (bottom_right_cluster_idx-top_left_cluster_idx)%this->nb_clusters_x;

    std::vector<cluster*> res(dx*dy);
    for(uint32_t i = 0 ; i < dx ; i++) {
        for(uint32_t j = 0 ; j < dy ; j++) {
            uint32_t idx = top_left_cluster_idx + i * this->nb_clusters_x + j;
            res.emplace_back(&clusters[idx]);
        }
    }
    return res;
}