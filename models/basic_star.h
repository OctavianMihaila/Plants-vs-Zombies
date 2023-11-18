#pragma once

#include "../assets/basic_objects.h"

class BasicStar {
public:
    BasicStar(const std::string& name, glm::vec3 center, float length, glm::vec3 color);
    ~BasicStar();

    Mesh* GetMesh() const;
    glm::vec3 GetPosition() const;
    float GetRadius() const;
    void SetPosition(const glm::vec3& newPosition);
    void CalculateRadius();
    void BasicStar::UpdatePosition(float oldXTravelDistance_, float newTravelDistance_);

private:
    float radius_;
    glm::vec3 position_;
    Mesh* mesh_;
};
