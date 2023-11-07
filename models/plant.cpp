#include "plant.h"

Plant::Plant(const std::string& name, glm::vec3 center, float width, float height, glm::vec3 color, int plantType, int cost) {
    mesh_ = basic_objects::CreateDiamond(name, center, width, height, color);
    plantType_ = plantType;
    cost_ = cost;
    isPlaced_ = false;
}

Plant::Plant() {
	// Create default constructor.
}

Plant::~Plant() {
    // Clean up any resources if needed.
}

void Plant::LaunchSpell() {
    // Add logic to launch a spell or perform plant-related actions.
    // You can use plantType_ to determine what kind of spell to launch.
}

int Plant::GetPlantType() const {
    return plantType_;
}

int Plant::GetCost() const {
    return cost_;
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
