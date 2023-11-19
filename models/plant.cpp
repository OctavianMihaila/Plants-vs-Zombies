#include "plant.h"

Plant::Plant(const std::string& name, glm::vec3 center, float width, float height,
                glm::vec3 color, int plantType, int cost) {
    mesh_ = basic_objects::CreateDiamond(name, center, width, height, color);
    position_ = center;
    xScale_ = 1.0f;
    yScale_ = 1.0f;
    isPlaced_ = false;
    plantType_ = plantType;
    launchCooldown_ = SPELL_LAUNCH_INTERVAL;
    cost_ = cost;
}

Plant::~Plant() {
    delete mesh_;
}

void Plant::SetXScale(float xScale) {
	xScale_ = xScale;
}

void Plant::SetYScale(float yScale) {
	yScale_ = yScale;
}

float Plant::GetXScale() const {
	return xScale_;
}

float Plant::GetYScale() const {
	return yScale_;
}

float Plant::GetLaunchCooldown() const {
    return launchCooldown_;
}

int Plant::GetPlantType() const {
    return plantType_;
}

int Plant::GetCost() const {
    return cost_;
}

glm::vec3 Plant::GetPosition() const {
    return position_;
}

Mesh* Plant::GetMesh() const {
    return mesh_;
}

bool Plant::IsPlaced() const {
    return isPlaced_;
}

void Plant::PlacePlant() {
    isPlaced_ = true;
}

void Plant::DecrementLaunchCooldown(float deltaTime) {
	launchCooldown_ -= deltaTime;
}

void Plant::ResetLaunchCooldown() {
	launchCooldown_ = SPELL_LAUNCH_INTERVAL;
}