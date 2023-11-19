#include "plant_manager.h"

PlantManager::PlantManager(BoardManager* boardManager) : boardManager(boardManager) {}

void PlantManager::PlantSpellPositionUpdate(PlantSpell* plantSpell, float deltaTimeSeconds,
                                            std::string& spellHash) {
    float oldXTravelDistance = plantSpell->GetXTravelDistance();
    float newXTravelDistance = oldXTravelDistance + deltaTimeSeconds * SPELL_MOVE_SPEED_RATE;

    plantSpell->IncreaseXTravelDistance(deltaTimeSeconds * SPELL_MOVE_SPEED_RATE);
    plantSpell->UpdatePosition(oldXTravelDistance, newXTravelDistance);

    if (plantSpell->GetPosition().x > SCREEN_WIDTH) {
        boardManager->RemovePlantSpell(plantSpell, spellHash);
    }

    plantSpell->IncreaseRotationValue(deltaTimeSeconds * ROTATION_SPEED_RATE);

    if (plantSpell->GetRotationValue() > 360.0f) {
        plantSpell->ResetRotationValue();
    }
}

void PlantManager::UpdatePlant(PlantSite* plantSite, Plant* plant, float deltaTimeSeconds,
                                int plantNumber) {
    if (plantSite->IsPlantReadyToBeRemoved()) {
        UpdatePlantRemoval(plantSite, plant, deltaTimeSeconds);
    }
    else {
        UpdatePlantBehavior(plantSite, plant, deltaTimeSeconds, plantNumber);
    }
}

void PlantManager::UpdatePlantRemoval(PlantSite* plantSite, Plant* plant,
                                        float deltaTimeSeconds) {
    float xScale = plant->GetXScale();
    float yScale = plant->GetYScale();
    float newXScale = xScale - deltaTimeSeconds * ANIMATION_SPEED_RATE;
    float newYScale = yScale - deltaTimeSeconds * ANIMATION_SPEED_RATE;

    plant->SetXScale(newXScale);
    plant->SetYScale(newYScale);

    // Ensure the scale doesn't go below zero.
    if (newXScale < 0.0f || newYScale < 0.0f) {
        plantSite->SetPlant(NULL);
        plantSite->SetPlantReadyToBeRemoved(false);
    }
}

void PlantManager::UpdatePlantBehavior(PlantSite* plantSite, Plant* plant, float deltaTimeSeconds,
                                        int plantNumber) {
    int line = plantNumber / 3 + 1;
    int type = plant->GetPlantType();
    std::string spellHash = std::to_string(line) + std::to_string(type);
    std::vector<Zombie*> zombies = boardManager->GetZombies()[spellHash];

    if (CheckZombieTypeInVector(type, zombies) && plant->GetLaunchCooldown() < 0.0f) {
        LaunchSpell(plantSite, plant, line);
    }
    else {
        plant->DecrementLaunchCooldown(deltaTimeSeconds);
    }
}

void PlantManager::LaunchSpell(PlantSite* plantSite, Plant* plant, int line) {
    glm::vec3 launchPosition = plantSite->GetPosition();

    launchPosition.z = 1.0f;
    boardManager->LaunchSpell(line, plant->GetPlantType(), launchPosition);
    plant->ResetLaunchCooldown();
}
