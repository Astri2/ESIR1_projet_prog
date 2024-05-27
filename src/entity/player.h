//
// Created by celia on 27/05/2024.
//
#pragma once

#include "entity.h"

class player : public entity {
public :
    player(float x, float y, float width, float height);
    ~player();
    void draw();
    void update(float dt) override;
};
