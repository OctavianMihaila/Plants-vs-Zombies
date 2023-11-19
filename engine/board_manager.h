#pragma once

#include "iostream"
#include "../utils/game_asset_factory.h"
#include <unordered_map>
#include "components/simple_scene.h"
#include "random"
#include "lab_m1/tema1/utils/util_functions.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define NR_PLANT_SITES 9
#define NR_LIVES 3
#define NR_INVENTORY_SLOTS 4
#define NR_COINS_TO_SPAWN 3
#define STAR_SIDE 20.f
#define COIN_SIDE 40.f
#define SPELL_STAR_SIDE 30.f
#define ZOMBIE_SIDE 40.f
#define INVENTORY_SQUARE_SIDE 125.f
#define LIVES_SQUARE_SIDE 75.f
#define PLANT_SITE_SQUARE_SIDE 125.f
#define STAR_OFFSET 30.f // distance between stars in inventory and coins.
#define INVENTORY_SQUARE_OFFSET 100.f // distance between squares.
#define INVENTORY_STAR_LEFT_OFFSET 80.f
#define STAR_SYMMETRY_VALUE 10.f // used for inventory stars and coins.
#define INVENTORY_STAR_TOP_OFFSET 65.f
#define INVENTORY_SQUARE_TOP_OFFSET 30.f
#define INVENTORY_SQUARE_LEFT_OFFSET 60.f
#define PLANT_SITE_SQUARE_LEFT_OFFSET 80.f
#define PLANT_SITE_SQUARE_OFFSET 50.f
#define LIVES_RIGHT_OFFSET 100.f
#define LIVES_TOP_OFFSET 40.f
#define LIVES_SQUARE_OFFSET 30.f
#define DAMAGE_ZONE_LEFT_OFFSET 10.f
#define HEXAGON_CALIBRATION_OFFSET 3.0f
#define DIAMOND_WIDTH 50.f
#define DIAMOND_HEIGHT 100.f
#define DAMAGE_ZONE_LENGTH 50.f
#define DAMAGE_ZONE_HEIGHT 475.f
#define ANIMATION_SPEED_RATE 1.0f
#define SPELL_MOVE_SPEED_RATE 100.0f
#define ZOMBIE_MOVE_SPEED_RATE 65.0f
#define ROTATION_SPEED_RATE 5.0f

class BoardManager {
public:
	BoardManager(GameAssetFactory* assetFactory);
	~BoardManager();

	void AddPlantSite(PlantSite* plantSite);
	void AddPlantSpell(PlantSpell* plantSpell, std::string key);
	void AddZombie(Zombie* zombie, std::string key);
	void AddPlant(Plant* plant);
	void AddLife(BasicSquare* life);
	void AddCollectedCoin(BasicStar* collectedCoin);
	void AddInventorySquare(BasicSquare* inventorySquare);
	void AddInventoryStar(BasicStar* inventoryStar);
	void AddInventoryPlant(Plant* inventoryPlant);

	void RemovePlantSpell(PlantSpell* plantSpell, const std::string& spellHash);
	void RemoveZombie(Zombie* zombie, std::string zombieType);
	void RemoveLife();
	void RemoveSpawnedCoin(Coin* coin);
	void RemoveCollectedCoins(int cost);

	void InitializePlantSites();
	void InitializeLives();
	void InitializeDamageZone();
	void InitializeThreeCoins();
	void InitializeInventory();
	void LaunchZombie();
	void LaunchSpell(int line, int plantType, glm::vec3 center);
	void setCurrentlyDraggedPlant(Plant* plant);

	GameAssetFactory* GetAssetFactory() const;
	std::vector<PlantSite*> GetPlantSites() const;
	std::unordered_map<std::string, std::vector<PlantSpell*>> BoardManager::GetPlantSpells() const;
	std::unordered_map<std::string, std::vector<Zombie*>> BoardManager::GetZombies() const;
	std::vector<BasicSquare*> GetLives() const;
	std::vector<Coin*> GetSpawnedCoins() const;
	std::vector<BasicStar*> GetCollectedCoins() const;
	std::vector<BasicSquare*> GetInventorySquares() const;
	std::vector<BasicStar*> GetInventoryStars() const;
	std::vector<Plant*> GetInventoryPlants() const;
	DamageZone* GetDamageZone() const;
	Plant* GetCurrentlyDraggedPlant() const;
	int GetNrCollectedCoins() const;

private:
	GameAssetFactory* assetFactory_;
	std::vector<PlantSite*> plantSites_;
	std::vector<BasicStar*> collectedCoins_;
	std::vector<Coin*> spawnedCoins_; // Coins that are spawned but not collected yet.
	/* Those maps store the plants that are currently on the board, in a way that
	   facilitates collition handling. The key is composed of two numbers,
	   first representing the line and second the type(color). */
	std::unordered_map<std::string, std::vector<PlantSpell*>> plantSpells_;
	std::unordered_map<std::string, std::vector<Zombie*>> zombies_;
	std::vector<Plant*> plants_; // Plants from the upper part(those for drag and drop).
	std::vector<BasicSquare*> lives_;
	std::vector<BasicSquare*> inventorySquares_;
	std::vector<BasicStar*> inventoryStars_;
	std::vector<Plant*> inventoryPlants_;
	DamageZone* damageZone_;
	Plant* currentlyDraggedPlant_;
};