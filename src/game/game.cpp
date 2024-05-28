//
// Created by malo1 on 5/27/2024.
//
#include "game.h"

#include "physics/physics.h"
#include "renderer.h"
#include "event.h"

game::game(unsigned int _width, unsigned int _height)
    : context(_width, _height), previous_tick(SDL_GetTicks())
{
    map::load_wsv("../resources/out.txt");
    // ui_components.push_back(new health_bar(m.player, 220, 20, 41, 7));
}

game::~game() {
    for (auto component : ui_components) delete component;
}

void game::run() {

    while(running) {
        uint32_t start_tick = SDL_GetTicks();
        float dt = static_cast<float>(static_cast<double>(start_tick - previous_tick)/1000.0);

        event::manager::update();
        map::update(dt);
        for (auto component : ui_components) {
            component->update(dt);
        }
        previous_tick = start_tick;

        /* Render Pass */
        renderer::clear(0, 0, 0);
        map::draw();
        for (auto component : ui_components) {
            component->draw();
        }
        // menus
        renderer::present();
    }
}

void game::handle_event(const SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_EventType::SDL_QUIT:
        {
            running = false;
        }
        break;
    }
}

/*
interactible * game::perceive(const player * user){
    interactible * nearest = nullptr;
    float nearest_dist = 0;

    for(cluster* c : get_surrounding_clusters(find_cluster_idx(user->get_position()))) {
        for (interactible * objet : c->interactibles){
            const float shared_dist = physics::shared_distance(user->get_interact_zone() , objet->get_interact_zone());

            if( shared_dist > nearest_dist ) {
                nearest = objet;
                nearest_dist = shared_dist;
            }
        }
    }

    return nearest;
}
*/
