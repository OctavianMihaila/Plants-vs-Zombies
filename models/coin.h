#pragma once

#include "basic_star.h"

class Coin : public BasicStar {
public:
    Coin(const std::string& name, glm::vec3 center, float length, glm::vec3 color);

    bool IsCollected() const;
    void Collect();

private:
    bool isCollected_;
};