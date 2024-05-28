//
// Created by malo1 on 5/28/2024.
//

#include "animated_sprite.h"

animated_sprite::animated_sprite(vec2<float> _position, vec2<float> _size, vec2<int> _frame_resolution,
                                 const char *image_src, const std::vector<int>& _animation_lengths, float _frame_time, int animation_id):
    entity(_position),
    sprite(_position, _size, {{0, animation_id}}, _frame_resolution, image_src),
    time(0), frame_time(_frame_time), animation_lengths(_animation_lengths)
{

}

void animated_sprite::update(float dt) {
    time += dt;
    if(time > frame_time) {
        time = 0;
        sprite_offset.x = (sprite_offset.x+1) % animation_lengths[sprite_offset.y];
    }
}
