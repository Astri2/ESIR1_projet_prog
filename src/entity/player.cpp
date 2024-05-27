//
// Created by celia on 27/05/2024.
//
#include "player.h"
#include "renderer.h"

player::player(float x, float y, float width, float height, int max_health, float interact_r)
        : entity(x, y, width, height), max_health(max_health), current_health(max_health)    {
    interact_zone.rayon = interact_r;
    interact_zone.position = entity::position;
}

const circle & player::get_interact_zone() const{
    return interact_zone;
}

player::~player(){}

void player::draw(){
    renderer::draw_rect(position.x, position.y, size.width, size.height, renderer::colors::red);
}

void player::update(float dt){
    const float speed = 10;
    move(speed * dt, 0);
}

int player::get_max_health() const {
    return max_health;
}

int player::get_current_health() const {
    return current_health;
}
