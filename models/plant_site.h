#pragma once

#include "basic_square.h"
#include "plant.h"

class PlantSite : public BasicSquare {
public:
    PlantSite(const std::string& name, glm::vec3 corner, float length, glm::vec3 color);
    ~PlantSite();

    void SetPlant(const Plant& plant);
    bool IsEmpty() const;

private:
    Plant placedPlant_;
    bool isEmpty_;
};
