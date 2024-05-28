//
// Created by viann on 27/05/2024.
//
#include "renderer.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace renderer {

    static SDL_Renderer* renderer = nullptr;

    bool initialize(void* window) {
        if(renderer) return true;

        renderer = SDL_CreateRenderer((SDL_Window*)window, -1, SDL_RENDERER_PRESENTVSYNC);
        if(!renderer) {
            std::cerr << "Error on SDL_CreateRenderer : " << SDL_GetError() << std::endl;
            return false;
        }

        if(auto code = SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND)) {
            std::cerr << "Warning(code: " << code << ") could not set blend mode to SDL_BLENDMODE_BLEND : " << SDL_GetError() << std::endl;
        }

        return true;
    }

    void clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        SDL_RenderClear(renderer);
    }

    void present() {
        SDL_RenderPresent(renderer);
    }

    void terminate() {
        SDL_DestroyRenderer(renderer);
    }

    void draw_rect(float x, float y, float width, float height, color c) {
        SDL_FRect rect { x, y, width, height };
        SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
        SDL_RenderFillRectF(renderer, &rect);
    }

    void draw_texture(float x, float y, float width, float height, const char* filepath) {
        SDL_Surface* img = IMG_Load(filepath);
        if(!img) {
            std::cerr << "Could not load image " << filepath << " : " << IMG_GetError() << std::endl;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, img);
        if(!texture) {
            std::cerr << "Could not create texture : " << IMG_GetError() << std::endl;
        }

        SDL_FRect rect { x, y, width, height };
        SDL_RenderCopyF(renderer, texture, nullptr, &rect);
    }

} // namespace renderer
