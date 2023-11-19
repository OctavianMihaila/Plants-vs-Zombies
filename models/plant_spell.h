#pragma once

#include "basic_star.h"


class PlantSpell : public BasicStar {
public:
    PlantSpell::PlantSpell(const std::string& name, glm::vec3 center,
                            float length, glm::vec3 color, int plantType);

    int GetPlantType() const;
    float GetXTravelDistance() const;
    float GetRotationValue() const;
    void IncreaseXTravelDistance(float xTravelDistance);
    void IncreaseRotationValue(float rotationValue);
    void ResetRotationValue();
private:
    int plantType_; // Used to determinate what zombie can be destroyed.
    float xTravelDistance_; // Used to determinate how far the plant should be rendered.
    float rotationValue_;
};