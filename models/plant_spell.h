#pragma once

#include "basic_star.h"

class PlantSpell : public BasicStar {
public:
    PlantSpell::PlantSpell(const std::string& name, glm::vec3 center, float length, glm::vec3 color, int plantType);

    void DestroyZombie();
    int GetPlantType() const;
private:
    int plantType_; // Used to determinate what zombie can be destroyed.
};