//
// Created by tomch on 27/05/2024.
//

#include "sprite.h"
#include <cstdlib>
#include <iostream>

#include "renderer.h"

void sprite::draw() const {
    renderer::draw_texture(position.x,position.y,size.x,size.y,static_cast<int>(frame_resolution.x),static_cast<int>(frame_resolution.y),texture,static_cast<int>(frame));
}

sprite::~sprite() {
    SDL_DestroyTexture(texture);
}

void sprite::update(float dt)
{
    frame += dt;

    if (frame > static_cast<float>(frames))
    {
        frame -= static_cast<float>(frames);
    }
}

int sprite::load_texture() {
    return renderer::load_texture(image_src,this);
}

void sprite::set_texture(SDL_Texture* texture){
    this->texture = texture;
}