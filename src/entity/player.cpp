//
// Created by celia on 27/05/2024.
//
#pragma once

#include "player.h"
#include "SDL2/SDL_rect.h"

player::player(float x, float y, float width, float height)
        : entity(x, y, width, height)  {}

player::~player(){}

void player::draw(SDL_Renderer * renderer){
    SDL_Rect rect{static_cast<int>(position.x),static_cast<int>(position.y),static_cast<int>(size.width),static_cast<int>(size.height)};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void player::update(float dt){
    move(position.x, position.y);
}