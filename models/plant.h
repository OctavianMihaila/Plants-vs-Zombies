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

    void SetXScale(float xScale);
    void SetYScale(float yScale);
    float GetXScale() const;
    float GetYScale() const;
    Mesh* GetMesh() const;
    int GetPlantType() const;
    int GetCost() const;
    glm::vec3 GetPosition() const;
    bool IsPlaced() const;
    void PlacePlant();
    void LaunchSpell();

private:
    int plantType_;
    int cost_;
    bool isPlaced_;
    float xScale_;
    float yScale_;
    Mesh* mesh_;
    glm::vec3 position_;

};
