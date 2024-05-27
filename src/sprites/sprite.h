//
// Created by tomch on 27/05/2024.
//

#pragma once
#include <SDL2/SDL.h>
#include "utils/vec2.h"

class sprite {
protected:
    SDL_Texture* texture;
    const char * image_src;
    vec2 size;
    vec2 position;
public:
    int load_texture();

    sprite(const char * src, vec2 position, vec2 size) : image_src(src),position(position), size(size) {}

    void set_texture(SDL_Texture* texture);

    void draw() const;

    ~sprite();
};