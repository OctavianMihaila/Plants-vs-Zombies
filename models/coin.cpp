#pragma once
#include "coin.h"

Coin::Coin(const std::string& name, glm::vec3 center, float length, glm::vec3 color)
    : BasicStar(name, center, length, color) {
    isCollected_ = false;
}

bool Coin::IsCollected() const {
    return isCollected_;
}

void Coin::Collect() {
    isCollected_ = true;
}