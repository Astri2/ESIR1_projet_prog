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
    for (auto component: ui_components) delete component;
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

void game::update_game() {
    event::manager::update();

    uint32_t start_tick = SDL_GetTicks();
    float dt = static_cast<float>(static_cast<double>(start_tick - previous_tick)/1000.0);

    map::update(dt);
    for (auto component : ui_components) {
        component->update(dt);
    }

    uint32_t start_tick = SDL_GetTicks();
    float dt = static_cast<float>(static_cast<double>(start_tick - previous_tick) / 1000.0);

    event::manager::update();
    map::update(dt);
    for (auto component: ui_components) {
        component->update(dt);
    }

    /* Render Pass */
    renderer::clear(0, 0, 0);
    map::draw();
    for (auto component: ui_components) {
        component->draw(map::cam);
    }
    // menus

    renderer::present();

    previous_tick = start_tick;
    if (config::tick_time > dt) SDL_Delay((uint32_t) (config::tick_time - dt) * 1000);
    else std::cout << "can't keep it up (" << dt - config::tick_time << " seconds behind)\n";
}

void game::update_menu() {
    // no menus rn
    current_state = state::game;
}

void game::update_game_over() {
    for(uint8_t alpha = 0; alpha < 255; alpha++) {
        map::draw();
        renderer::draw_rect(0, 0, config::window::width, config::window::height, renderer::color{ 0, 0, 0, alpha });
        SDL_Texture* game_over_message = renderer::create_sdl_texture("../resources/failure_txt.png");
        const struct {
            float x, y;
        } ratio = {
                (970.0f / config::window::width),
                (98.0f / config::window::height),
        };
        float dest_text_width = ((float)config::window::width / 2.0f) * ratio.x;
        float dest_text_height = ((float)config::window::height / 2.0f) * ratio.y;
        renderer::draw_texture(
                {{ (((float)config::window::width / 2.0f) - (dest_text_width / 2.0f)), (((float)config::window::height / 2.0f) - (dest_text_height / 2.0f)) }},
                {{ dest_text_width, dest_text_height }},
                {{ 970, 98 }},
                game_over_message,
                {{0, 0}}
        );
        renderer::present();
        SDL_Delay(10);
    }
    current_state = state::quit;
}

void game::update_victory() {
    for(uint8_t alpha = 0; alpha < 255; alpha++) {
        map::draw();
        renderer::draw_rect(0, 0, config::window::width, config::window::height, renderer::color{ 0, 0, 0, alpha });
        SDL_Texture* game_over_message = renderer::create_sdl_texture("../resources/victory_txt.png");
        const struct {
            float x, y;
        } ratio = {
                (697.0f / config::window::width),
                (135.0f / config::window::height),
        };
        float dest_text_width = ((float)config::window::width / 2.0f) * ratio.x;
        float dest_text_height = ((float)config::window::height / 2.0f) * ratio.y;
        renderer::draw_texture(
                {{ (((float)config::window::width / 2.0f) - (dest_text_width / 2.0f)), (((float)config::window::height / 2.0f) - (dest_text_height / 2.0f)) }},
                {{ dest_text_width, dest_text_height }},
                {{ 697, 135 }},
                game_over_message,
                {{0, 0}}
        );
        renderer::present();
        SDL_Delay(10);
    }
    current_state = state::quit;
}
