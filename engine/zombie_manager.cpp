#include "zombie_manager.h"

ZombieManager::ZombieManager(BoardManager* boardManager) : boardManager(boardManager) {}

void ZombieManager::UpdateZombie(Zombie* zombie, std::string zombieHash, float deltaTimeSeconds) {
    int line = zombieHash[0] - '0';

    if (zombie->IsReadyToBeRemoved()) {
        UpdateZombieRemoval(zombie, zombieHash, deltaTimeSeconds);
    }
    else {
        UpdateZombieMovement(zombie, deltaTimeSeconds);
        CheckAndRemoveLife(zombie, zombieHash);
        CheckAndRemovePlant(zombie, boardManager->GetPlantSites(), line);
        HandleZombiePlantSpellCollision(zombie, boardManager->GetPlantSpells(), zombieHash);
    }
}

void ZombieManager::HandleZombieSpawn(float deltaTimeSeconds) {
    if (Zombie::IsTimeToSpawn()) {
        boardManager->LaunchZombie();
        Zombie::UpdateSpawnTime();
    }
    else {
        Zombie::IncreaseWithDeltaTime(deltaTimeSeconds);
    }
}

void ZombieManager::UpdateZombieRemoval(Zombie* zombie, std::string& zombieHash, float deltaTimeSeconds) {
    float xScale = zombie->GetXScale();
    float yScale = zombie->GetYScale();
    float newXScale = xScale - deltaTimeSeconds * ANIMATION_SPEED_RATE;
    float newYScale = yScale - deltaTimeSeconds * ANIMATION_SPEED_RATE;

    zombie->SetXScale(newXScale);
    zombie->SetYScale(newYScale);

    // Ensure the scale doesn't go below zero.
    if (newXScale < 0.0f || newYScale < 0.0f) {
        boardManager->RemoveZombie(zombie, zombieHash);
        zombie->SetReadyToBeRemoved(false);
    }
}

void ZombieManager::UpdateZombieMovement(Zombie* zombie, float deltaTimeSeconds) {
    float oldXTravelDistance = zombie->GetXTravelDistance();
    float newXTravelDistance = oldXTravelDistance + deltaTimeSeconds * ZOMBIE_MOVE_SPEED_RATE;
    zombie->IncreaseXTravelDistance(deltaTimeSeconds * ZOMBIE_MOVE_SPEED_RATE);
    zombie->UpdatePosition(oldXTravelDistance, newXTravelDistance);
}

void ZombieManager::CheckAndRemoveLife(Zombie* zombie, std::string& zombieHash) {
    // Zombie collision with damage zone.
    if (zombie->GetXTravelDistance() > SCREEN_WIDTH - DAMAGE_ZONE_LEFT_OFFSET - DAMAGE_ZONE_LENGTH) {
        boardManager->RemoveLife();
        boardManager->RemoveZombie(zombie, zombieHash);
    }
}

void ZombieManager::CheckAndRemovePlant(Zombie* zombie, std::vector<PlantSite*>& plantSites, int line) {
    int count = 0;

    for (PlantSite* plantSite : plantSites) {
        if (!plantSite->IsEmpty()) {
            float plantSiteRightOffset = SCREEN_WIDTH - PLANT_SITE_SQUARE_LEFT_OFFSET - (count % 3) * (PLANT_SITE_SQUARE_SIDE + PLANT_SITE_SQUARE_OFFSET) - PLANT_SITE_SQUARE_SIDE;
            if (line == ((count / 3) + 1) && zombie->GetXTravelDistance() > plantSiteRightOffset && zombie->GetXTravelDistance() < plantSiteRightOffset + PLANT_SITE_SQUARE_SIDE) {
                plantSite->SetPlantReadyToBeRemoved(true);
            }
        }

        count++;
    }
}

void ZombieManager::HandleZombiePlantSpellCollision(Zombie* zombie, std::unordered_map<std::string, std::vector<PlantSpell*>>& plantSpells, std::string& zombieHash) {
    for (auto const& x : plantSpells) {
        std::vector<PlantSpell*> plantSpells = x.second;
        std::string spellHash = x.first;
        int plantType = spellHash[1] - '0';
        glm::vec3 plantColor = FindPlantColor(plantType);

        for (PlantSpell* plantSpell : plantSpells) {
            glm::vec3 plantSpellCenter = plantSpell->GetPosition();
            glm::vec3 zombieCenter = zombie->GetPosition();
            float plantRadius = plantSpell->GetRadius();
            float zombieRadius = zombie->GetRadius();

            if (CheckCollision(plantSpellCenter, zombieCenter, plantRadius, zombieRadius) && spellHash == zombieHash) {
                boardManager->RemovePlantSpell(plantSpell, spellHash);

                if (zombie->GetTotalDamageTaken() == 2 && !zombie->IsReadyToBeRemoved()) {
                    zombie->AjustPosition(zombie->GetRadius(), zombie->GetRadius());
                    zombie->SetReadyToBeRemoved(true);
                }
                else {
                    zombie->TakeDamage(1);
                }

                break;
            }
        }
    }
}
