#pragma once

#include <string>
#include <glm/glm.hpp>
#include "../assets/basic_objects.h"

#define SPELL_LAUNCH_INTERVAL 3.0f

class Plant {
public:
    Plant::Plant(const std::string& name, glm::vec3 center, float width, float height, glm::vec3 color, int plantType, int cost);
    // create default constructor
    Plant::Plant();
    ~Plant();

    void SetXScale(float xScale);
    void SetYScale(float yScale);
    bool IsPlaced() const;
    void PlacePlant();
    void ResetLaunchCooldown();
    void DecrementLaunchCooldown(float deltaTime);
    float GetXScale() const;
    float GetYScale() const;
    float GetLaunchCooldown() const;
    int GetPlantType() const;
    int GetCost() const;
    glm::vec3 GetPosition() const;
    Mesh* GetMesh() const;

private:
    int plantType_;
    int cost_;
    float xScale_;
    float yScale_;
    float launchCooldown_;
    bool isPlaced_;
    Mesh* mesh_;
    glm::vec3 position_;

};
