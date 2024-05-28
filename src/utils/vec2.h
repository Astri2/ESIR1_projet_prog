//
// Created by malo1 on 5/27/2024.
//

#pragma once

#include <cmath>

template <class T>
union vec2 {
    struct {
        T x, y;
    };
    struct {
        T width, height;
    };

    float distance(const vec2 & other) const {
        return (float)sqrt(pow(this->x-other.x, 2) + pow(this->y-other.y, 2));
    }
};

template <class T>
inline vec2<T> operator+ (const vec2<T>& lhs, const vec2<T> & rhs){
    vec2<T> nouveau{};
    nouveau.x = lhs.x + rhs.x;
    nouveau.y = lhs.y + rhs.y;

    return nouveau;
}