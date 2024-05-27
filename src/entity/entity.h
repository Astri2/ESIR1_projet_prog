//
// Created by cejosso on 27/05/2024.
//
# pragma once

#include "SDL2/SDL_render.h"

class entity {
public :
    entity(float x, float y, float width, float height);

    virtual ~entity();

    virtual void draw(SDL_Renderer * renderer) = 0;
    virtual void update(float dt) = 0;

    void move(float dx, float dy);
    void move_to(float x, float y);

protected :
    struct {
        float x;
        float y;
    } position;
    struct {
        float width;
        float height;
    } size;
};
