//
// Created by celia on 27/05/2024.
//
#include <algorithm>
#include "player.h"
#include "input.h"

#include "map/map.h"

player::player(vec2<float> pos, vec2<float> size, int max_health):
        entity(pos),
        animated_sprite(pos, size, {{48, 48}}, "../resources/test.bmp", {4}, 0.1),
        collidable_entity(pos, aabb{0.f, 0.f, size.width, size.height}),
        max_health(max_health), current_health(max_health)
{
}

circle player::get_interact_zone() const{
    circle interact_zone{15,size/2.0f};
    return interact_zone + get_position();
}

void player::update(float dt) {

    animated_sprite::update(dt);

    vec2<float> dir{{0, 0}};

    if(input::is_key_pressed(SDL_SCANCODE_A)) { dir.x -= 1; }
    if(input::is_key_pressed(SDL_SCANCODE_D)) { dir.x += 1; }
    if(input::is_key_pressed(SDL_SCANCODE_W)) { dir.y -= 1; }
    if(input::is_key_pressed(SDL_SCANCODE_S)) { dir.y += 1; }
    const float speed = 50;

    unsigned int idx = map::find_cluster_idx(get_position());
    move(dir.x * speed * dt, dir.y * speed * dt);
    unsigned int new_idx = map::find_cluster_idx(get_position());
    if(idx != new_idx) {
        map::clusters[idx].collidables.erase(this);
        map::clusters[idx].foreground.erase(this);
        map::clusters[new_idx].collidables.insert(this);
        map::clusters[new_idx].foreground.insert(this);
    }
}

void player::damage(int damage_value) {
    current_health = std::max(current_health-damage_value, static_cast<uint32_t>(0));
}

void player::benefit(int benefit_value) {
    current_health = std::min(benefit_value + current_health, max_health);
}

int player::get_max_health() const {
    return max_health;
}

int player::get_current_health() const {
    return current_health;
}
