#include "plant_spell.h"

PlantSpell::PlantSpell(const std::string& name, glm::vec3 center, float length, glm::vec3 color, int plantType)
    : BasicStar(name, center, length, color),
      plantType_(plantType) {
    xTravelDistance_ = 0.0f;
    rotationValue_ = 0.0f;
}

void PlantSpell::DestroyZombie() {
    // Add logic to destroy zombies based on the plant type and other conditions
    // For example:
    if (plantType_) {
        // Destroy a specific type of zombie
    }
    else {
        // Destroy another type of zombie
    }
}

int PlantSpell::GetPlantType() const {
    return plantType_;
}

float PlantSpell::GetXTravelDistance() const {
	return xTravelDistance_;
}

float PlantSpell::GetRotationValue() const {
	return rotationValue_;
}

void PlantSpell::IncreaseXTravelDistance(float xTravelDistance) {
	xTravelDistance_ += xTravelDistance;
}

void PlantSpell::IncreaseRotationValue(float rotationValue) {
	rotationValue_ += rotationValue;
}

void PlantSpell::ResetRotationValue() {
	rotationValue_ = 0.0f;
}