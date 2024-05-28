//
// Created by celia on 28/05/2024.
//
#pragma once

#include "entity.h"
#include "interactible.h"

class item : public entity, public interactible {
public:
    item(float x, float y, float width, float height, float interact_r);

    void interact(player * user);

};
