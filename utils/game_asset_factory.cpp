#pragma once

#include "game_asset_factory.h"

BasicStar* GameAssetFactory::CreateBasicStar(const std::string& name, glm::vec3 center, float length, glm::vec3 color) {
	BasicStar* star = new BasicStar(name, center, length, color);
	return star;
}

BasicSquare* GameAssetFactory::CreateBasicSquare(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill) {
	BasicSquare* square = new BasicSquare(name, center, length, color, fill);
	return square;
}

Coin* GameAssetFactory::CreateCoin(const std::string& name, glm::vec3 center, float length, glm::vec3 color) {
	Coin* coin = new Coin(name, center, length, color);
	return coin;
}

DamageZone* GameAssetFactory::CreateDamageZone(const std::string& name, glm::vec3 center, float length, float width, glm::vec3 color) {
	DamageZone* damageZone = new DamageZone(name, center, length, width, color);
	return damageZone;
}

PlantSite* GameAssetFactory::CreatePlantSite(const std::string& name, glm::vec3 center, float length, glm::vec3 color) {
	PlantSite* plantSite = new PlantSite(name, center, length, color);
	return plantSite;
}

PlantSpell* GameAssetFactory::CreatePlantSpell(const std::string& name, glm::vec3 center, float length, glm::vec3 color, int plantType) {
	PlantSpell* plantSpell = new PlantSpell(name, center, length, color, plantType);
	return plantSpell;
}

Zombie* GameAssetFactory::CreateZombie(const std::string& name, glm::vec3 center, float length, glm::vec3 firstHexagonColor, glm::vec3 secondHexagonColor, int zombieType) {
	Zombie* zombie = new Zombie(name, center, length, firstHexagonColor, secondHexagonColor, zombieType);
	return zombie;
}

Plant* GameAssetFactory::CreatePlant(const std::string& name, glm::vec3 center, float width, float height, glm::vec3 color, int plantType, int cost) {
	Plant* plant = new Plant(name, center, width, height, color, plantType, cost);
	return plant;
}

void GameAssetFactory::DestroyObject(Mesh* object) {
	delete object;
}
