#pragma once

#include <string>
#include <glm/glm.hpp>
#include "../assets/basic_objects.h"

class Plant {
public:
    Plant::Plant(const std::string& name, glm::vec3 center, float width, float height, glm::vec3 color, int plantType, int cost);
    // create default constructor
    Plant::Plant();
    ~Plant();

    void LaunchSpell();
    int GetPlantType() const;
    int GetCost() const;
    Mesh* GetMesh() const;
    bool IsPlaced() const;
    void PlacePlant();

private:
    Mesh* mesh_;
    int plantType_;
    int cost_;
    bool isPlaced_;
};
