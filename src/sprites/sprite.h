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
    vec2 frame_resolution;
    vec2 position;
    float frame = 0.0f;
    int frames;
public:
    int load_texture();

    sprite(const char * src, vec2 position, vec2 size, vec2 frame_resolution, int frames) : image_src(src),position(position), size(size), frame_resolution(frame_resolution), frames(frames) {}

    void set_texture(SDL_Texture* texture);

    void draw() const;

    void update(float dt);

    ~sprite();
};