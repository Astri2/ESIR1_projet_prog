//
// Created by malo1 on 5/27/2024.
//
#include "game.h"
#include "physics/physics.h"

#include "color.h"
#include "renderer.h"

game::game(unsigned int _width, unsigned int _height)
    : context(_width, _height)
{}

void game::run() {

    while(true) {
        renderer::clear(0, 0, 0);
        renderer::draw_rect(0, 0, 50, 50, renderer::colors::red);
        renderer::present();
    }

}

std::vector<interactible *> game::perceive(player * user){
    std::vector<interactible *> interactibles_filtered;

    for (interactible * objet : interactibles){
        if (physics::are_colliding(user->get_interact_zone(), objet->get_interact_zone())){
            interactibles.push_back(objet);
        }
    }

    return interactibles;
}