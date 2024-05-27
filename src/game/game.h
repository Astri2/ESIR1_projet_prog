//
// Created by malo1 on 5/27/2024.
//

#pragma once

#include <vector>
#include "context.h"
#include "../entity/entity.h"
#include "../entity/interactible.h"


class game: public context {
public:
    game(unsigned int _width, unsigned int _height);

    void run();
private:

    std::vector<entity *> entities;
    std::vector<interactible *> interactibles;

    std::vector<interactible *> perceive(entity * user);

    void gameLoop();
};