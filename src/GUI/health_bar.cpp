//
// Created by celia on 27/05/2024.
//

#include "health_bar.h"

#include "health_bar.h"

health_bar::health_bar(player * p, const float x, const float y, const float width, const float height)
        : gui_component(x, y, width, height), p(p), current_health(100.0f), max_health(p->get_max_health()) {}

health_bar::~health_bar() {}

void health_bar::draw() {
    renderer::draw_rect(position.x, position.y, size.width, size.height, renderer::colors::red);
    float health_width = (current_health / max_health) * size.width;
    renderer::draw_rect(position.x, position.y, health_width, size.height, renderer::colors::red);
}

void health_bar::update(float dt) {
    current_health = p->get_current_health();
}

void health_bar::damage(int damage_value) {
    current_health -= static_cast<float>(damage_value);
    if (current_health < 0) {
        current_health = 0;
    }
}

void health_bar::benefit(int benefit_value) {
    current_health += benefit_value;
    if (current_health > max_health) {
        current_health = max_health;
    }
}

