#include "plant.h"

Plant::Plant(const std::string& name, glm::vec3 center, float width, float height, glm::vec3 color, int plantType, int cost) {
    mesh_ = basic_objects::CreateDiamond(name, center, width, height, color);
    position_ = center;
    xScale_ = 1.0f;
    yScale_ = 1.0f;
    isPlaced_ = false;
    plantType_ = plantType;
    cost_ = cost;
}

Plant::Plant() {
	// Create default constructor.
}

Plant::~Plant() {
    // Clean up any resources if needed.
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

Mesh* Plant::GetMesh() const {
    return mesh_;
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

bool Plant::IsPlaced() const {
    return isPlaced_;
}

void Plant::PlacePlant() {
    isPlaced_ = true;
}

void Plant::LaunchSpell() {
    // Add logic to launch a spell or perform plant-related actions.
    // You can use plantType_ to determine what kind of spell to launch.
}
