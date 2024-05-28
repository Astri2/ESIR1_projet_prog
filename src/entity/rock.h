//
// Created by celia on 28/05/2024.
//

#pragma once

#include "item.h"

class rock : public item {
    rock(float x, float y, float width, float height, float interact_r);
    ~rock();
};
