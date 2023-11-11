#pragma once

#include "basic_square.h"
#include "plant.h"

class PlantSite : public BasicSquare {
public:
    PlantSite(const std::string& name, glm::vec3 corner, float length, glm::vec3 color);
    ~PlantSite();

    void SetPlant(Plant* plant);
    void SetPlantReadyToBeRemoved(bool readyToBeRemoved);
    bool IsEmpty() const;
    bool IsPlantReadyToBeRemoved() const;
    Plant* GetPlant() const;

private:
    Plant* placedPlant_;
    bool isEmpty_;
    bool plantReadyToBeRemoved_;
};
