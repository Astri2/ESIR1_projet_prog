//
// Created by celia on 28/05/2024.
//

#include "item.h"

item::item(float x, float y, float width, float height, float interact_r)
    : entity(x, y, width, height), interactible(x, y, interact_r) {}

void item::interact(player * user) {
    // add_in_inventory()
}

