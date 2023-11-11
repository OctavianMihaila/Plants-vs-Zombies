#include "plant_site.h"

PlantSite::PlantSite(const std::string& name, glm::vec3 corner, float length, glm::vec3 color)
    : BasicSquare(name, corner, length, color, true) {
    placedPlant_ = NULL;
    isEmpty_ = true;
    plantReadyToBeRemoved_ = false;
}

PlantSite::~PlantSite() {
    // BasicSquare's destructor will be called automatically.
}

void PlantSite::SetPlant(Plant* plant) {
    if (plant == NULL) {
		isEmpty_ = true;
		return;
	}

    placedPlant_ = plant;
    isEmpty_ = false;
}

void PlantSite::SetPlantReadyToBeRemoved(bool readyToBeRemoved) {
    plantReadyToBeRemoved_ = readyToBeRemoved;
}

Plant* PlantSite::GetPlant() const {
	return placedPlant_;
}

bool PlantSite::IsEmpty() const {
    return isEmpty_;
}

bool PlantSite::IsPlantReadyToBeRemoved() const {
    return plantReadyToBeRemoved_;
}
