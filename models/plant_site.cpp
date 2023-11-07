#include "plant_site.h"

PlantSite::PlantSite(const std::string& name, glm::vec3 corner, float length, glm::vec3 color)
    : BasicSquare(name, corner, length, color, true) {
    placedPlant_ = Plant();
    isEmpty_ = true;
}

PlantSite::~PlantSite() {
    // BasicSquare's destructor will be called automatically.
}

void PlantSite::SetPlant(const Plant& plant) {
    placedPlant_ = plant;
    isEmpty_ = false;
}

bool PlantSite::IsEmpty() const {
    return isEmpty_;
}
