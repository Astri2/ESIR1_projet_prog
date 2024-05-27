 //
// Created by malo1 on 5/27/2024.
//
#include "game.h"

#include <iostream>

#include "physics/physics.h"
#include "renderer.h"
#include "event.h"
#include "sprites/sprite.h"

 game::game(unsigned int _width, unsigned int _height)
    : context(_width, _height), p(new player(0, 0, 5, 5, 5)) {}

game::~game() {
    delete p;
}

void game::run() {
    vec2 vec;
     vec.x=1;
     vec.y=1;

     vec2 vec1;
     vec1.x=100;
     vec1.y=100;

    sprite test("../resources/grumpy-cat.bmp",vec,vec1);

     int a = test.load_texture();
     std::cout<<a;

    while(running) {
        event::manager::update();

        p->update(0.1);
        renderer::clear(0, 0, 0);

        p->draw();

        test.draw();

        renderer::present();
    }
}

void game::handle_event(const SDL_Event &event) {
    switch (event.type) {
        case SDL_EventType::SDL_QUIT: {
            running = false;
        } break;
    }
}

interactible * game::perceive(const player * user){
    interactible * nearest = nullptr;

    float nearest_dist = 0;

    for (interactible * objet : interactibles){
        const float shared_dist = physics::shared_distance(user->get_interact_zone() , objet->get_interact_zone());

        if( shared_dist > nearest_dist ) {
            nearest = objet;
            nearest_dist = shared_dist;
        }
    }

    return nearest;
}