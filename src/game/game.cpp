//
// Created by malo1 on 5/27/2024.
//
#include <iostream>
#include "game.h"

#include "physics/physics.h"
#include "renderer.h"
#include "event.h"

std::vector<gui_component *> game::ui_components;

game::game(unsigned int _width, unsigned int _height)
    : context(_width, _height), current_state(state::game)
{
    map::load("../resources/map.map");
}

game::~game() {
    for (auto component : ui_components) delete component;
}

void game::run() {
    // init ticks
    previous_tick = SDL_GetTicks();

    while(running) {
        switch(current_state) {
            case state::game: update_game(); break;
            case state::menu: update_menu(); break;
            case state::victory: update_victory(); break;
            case state::game_over: update_game_over(); break;
            case state::quit: return;
        }
    }
}

void game::handle_event(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_EventType::SDL_QUIT: {
        running = false;
    } break;
    case SDL_EventType ::SDL_USEREVENT: {
        if(event.user.code == player::event::died) current_state = state::game_over;
    } break;
    }
}

void game::update_game() {
    event::manager::update();

    uint32_t start_tick = SDL_GetTicks();
    float dt = static_cast<float>(static_cast<double>(start_tick - previous_tick)/1000.0);

    map::update(dt);
    for (auto component : ui_components) {
        component->update(dt);
    }

    /* Render Pass */
    renderer::clear(0, 0, 0);
    map::draw();
    for (auto component : ui_components) {
        component->draw(map::cam);
    }

    renderer::present();

    previous_tick = start_tick;
    if(config::tick_time > dt) SDL_Delay((uint32_t)(config::tick_time - dt)*1000);
    else std::cout << "can't keep it up (" << dt-config::tick_time << " seconds behind)\n";
}

void game::update_menu() {
    // no menus rn
    current_state = state::game;
}

void game::update_game_over() {
    current_state = state::quit;
}

void game::update_victory() {
    current_state = state::quit;
}
