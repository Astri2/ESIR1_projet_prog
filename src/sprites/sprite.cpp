//
// Created by tomch on 27/05/2024.
//

#include "sprite.h"
#include <cstdlib>
#include <iostream>

#include "renderer.h"

void sprite::draw() const {
    renderer::draw_texture(0,0,0,0,texture);
}

sprite::~sprite() {
    SDL_DestroyTexture(texture);
}

int sprite::load_texture() {
    return renderer::load_texture(image_src,this);
}

void sprite::set_texture(SDL_Texture* texture){
    this->texture = texture;
}