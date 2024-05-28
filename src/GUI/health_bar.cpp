//
// Created by celia on 27/05/2024.
//

#include "health_bar.h"
#include "renderer.h"

health_bar::health_bar(vec2<float> _position, vec2<float> _size, vec2<int> _sprite_offset , vec2<int> _sprite_resolution, const char* image_src, player * p)
        : entity(_position),gui_component(_position, _size, _sprite_offset, _sprite_resolution, image_src), p(p), current_health(100.0f), max_health(p->get_max_health()) {}

void health_bar::draw(const camera& cam) const {
    // green rectangle : area of the bar (const)
    renderer::draw_rect(position.x, position.y, size.width, size.height, renderer::colors::red);

    // red rectangle : area of the bar (not const)
    float health_width = (current_health / max_health) * size.width;
    renderer::draw_rect(position.x, position.y, health_width, size.height, renderer::colors::green);
    renderer::draw_texture(position, size,sprite_resolution, texture, sprite_offset);
}

void health_bar::update(float dt) {
    current_health = p->get_current_health();
}

