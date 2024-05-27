//
// Created by malo1 on 5/27/2024.
//
#include "game.h"

#include "physics/physics.h"
#include "color.h"
#include "renderer.h"

game::game(unsigned int _width, unsigned int _height)
    : context(_width, _height), p(new player(0, 0, 5, 5, 5)) {}

game::~game() {
    delete p;
}

void game::run() {

    while(true) {
        p->update(0.1);
        renderer::clear(0, 0, 0);
        p->draw();
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