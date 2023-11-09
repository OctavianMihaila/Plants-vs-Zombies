#pragma once

#include "../models/basic_star.h"
#include "../models/coin.h"
#include "../models/damage_zone.h"
#include "../models/plant_site.h"
#include "../models/plant_spell.h"
#include "../models/zombie.h"

class GameAssetFactory {
public:
    static GameAssetFactory& GetInstance() {
        static GameAssetFactory instance;
        return instance;
    }

    BasicStar* CreateBasicStar(const std::string& name, glm::vec3 center, float length, glm::vec3 color);
    BasicSquare* CreateBasicSquare(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill);
    Coin* GameAssetFactory::CreateCoin(const std::string& name, glm::vec3 center, float length, glm::vec3 color, float xTranslation, float yTranslation);
    DamageZone* CreateDamageZone(const std::string& name, glm::vec3 center, float length, float width, glm::vec3 color);
    PlantSite* CreatePlantSite(const std::string& name, glm::vec3 center, float length, glm::vec3 color);
    PlantSpell* CreatePlantSpell(const std::string& name, glm::vec3 center, float length, glm::vec3 color, int plantType);
    Zombie* CreateZombie(const std::string& name, glm::vec3 center, float length, glm::vec3 firstHexagonColor, glm::vec3 secondHexagonColor, int zombieType);
    Plant* CreatePlant(const std::string& name, glm::vec3 center, float width, float height, glm::vec3 color, int plantType, int cost);
    void DestroyObject(Mesh* object);

    // Add any other public methods or members as needed

private:
    GameAssetFactory() {} // Private constructor

    // Prevent copy/move operations
    GameAssetFactory(const GameAssetFactory&) = delete;
    GameAssetFactory& operator=(const GameAssetFactory&) = delete;
};
