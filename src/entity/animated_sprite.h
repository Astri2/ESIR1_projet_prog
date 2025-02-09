//
// Created by malo1 on 5/28/2024.
//

#pragma once


#include "sprite.h"
#include <vector>

class animated_sprite : public sprite {
protected:
    float time;
    const float frame_time;
    std::vector<uint32_t> animation_lengths;
public:
    animated_sprite(vec2<float> _position, vec2<float> _size, vec2<uint32_t> _frame_resolution, vec2<float> _anchor,
                    const char *image_src, const std::vector<uint32_t> &_animation_lengths, float _frame_time,
                    uint32_t animation_id = 0);

    void update(float dt) override;
};
