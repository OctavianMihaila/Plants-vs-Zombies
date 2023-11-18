#pragma once

#include "basic_square.h"
#include "plant.h"

class PlantSite : public BasicSquare {
public:
    PlantSite(const std::string& name, glm::vec3 corner, float length, glm::vec3 color);
    ~PlantSite();

    void SetPlant(Plant* plant);
    void SetPlantReadyToBeRemoved(bool readyToBeRemoved);
    Plant* GetPlant() const;
    bool IsEmpty() const;
    bool IsPlantReadyToBeRemoved() const;

private:
    bool isEmpty_;
    bool plantReadyToBeRemoved_;
    Plant* placedPlant_;

};
