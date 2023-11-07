#pragma once

#include "iostream"
#include "../utils/game_asset_factory.h"
#include <unordered_map>
#include "components/simple_scene.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define NR_PLANT_SITES 9
#define NR_LIVES 3
#define NR_INVENTORY_SLOTS 4
#define STAR_SIDE 20.f
#define INVENTORY_SQUARE_SIDE 125.f
#define STAR_OFFSET 30.f // distance between stars
#define INVENTORY_SQUARE_OFFSET 100.f // distance between squares
#define INVENTORY_STAR_LEFT_OFFSET 80.f
#define STAR_SYMMETRY_VALUE 10.f
#define INVENTORY_STAR_TOP_OFFSET 65.f
#define INVENTORY_SQUARE_TOP_OFFSET 30.f
#define INVENTORY_SQUARE_LEFT_OFFSET 60.f
#define DIAMOND_WIDTH 50.f
#define DIAMOND_HEIGHT 100.f
#define LIVES_RIGHT_OFFSET 100.f
#define LIVES_TOP_OFFSET 40.f
#define LIVES_SQUARE_OFFSET 30.f
#define LIVES_SQUARE_SIDE 75.f
#define DAMAGE_ZONE_LEFT_OFFSET 10.f
#define DAMAGE_ZONE_LENGTH 50.f
#define DAMAGE_ZONE_HEIGHT 400.f

class BoardManager {
public:
	BoardManager(GameAssetFactory* assetFactory);
	~BoardManager();

	void AddPlantSite(PlantSite* plantSite);
	void AddPlantSpell(PlantSpell* plantSpell, std::string key);
	void AddZombie(Zombie* zombie, std::string key);
	void AddPlant(Plant* plant);
	void AddLife(BasicSquare* life);
	void AddCoin(Coin* coin);
	void AddCollectedCoin(BasicStar* collectedCoin);
	void SetDamageZone(DamageZone* damageZone);

	void RemovePlantSite(PlantSite* plantSite);
	void RemovePlantSpell(PlantSpell* plantSpell);
	void RemoveZombie(Zombie* zombie);
	void RemovePlant(Plant* plant);
	void RemoveLife(BasicSquare* life);
	void RemoveCoin(Coin* coin);
	void RemoveCollectedCoin(BasicStar* collectedCoin);
	void RemoveDamageZone(DamageZone* damageZone);

	void InitializePlantSites(std::unordered_map<std::string, Mesh*>* meshes);
	void InitializePlantSpells();
	void InitializeZombies();
	void InitializePlants();
	void InitializeLives(std::unordered_map<std::string, Mesh*>* meshes);
	void InitializeCoins();
	void InitializeCollectedCoins();
	void InitializeDamageZone(std::unordered_map<std::string, Mesh*>* meshes);
	void InitializeInventory(std::unordered_map<std::string, Mesh*>* meshes);

	std::vector<PlantSite*> GetPlantSites() const;
	std::unordered_map<std::string, std::vector<PlantSpell*>> BoardManager::GetPlantSpells() const;
	std::unordered_map<std::string, std::vector<Zombie*>> BoardManager::GetZombies() const;
	std::vector<Plant*> GetPlants() const;
	std::vector<BasicSquare*> GetLives() const;
	std::vector<Coin*> GetSpawnedCoins() const;
	std::vector<BasicStar*> GetCollectedCoins() const;
	DamageZone* GetDamageZone() const;

	void ClearPlantSites();
	void ClearPlantSpells();
	void ClearZombies();
	void ClearPlants();
	void ClearLives();
	void ClearSpawnedCoins();
	void ClearCollectedCoins();
	void ClearDamageZone();

	void Update(float deltaTime);
	void Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix);

private:
	GameAssetFactory* assetFactory_;
	std::vector<PlantSite*> plantSites_;
	std::vector<BasicStar*> collectedCoins_;
	std::vector<Coin*> spawnedCoins_; // coins that are spawned but not collected yet.
	/* Those maps store the plants that are currently on the board, in a way that
	   facilitates collition handling. The key is composed of two numbers,
	   first representing the line and second the type(color). */
	std::unordered_map<std::string, std::vector<PlantSpell*>> plantSpells_;
	std::unordered_map<std::string, std::vector<Zombie*>> zombies_;
	std::vector<Plant*> plants_; // Plants from the upper part(those for drag and drop).
	std::vector<BasicSquare*> lives_; // The lives of the player.
	DamageZone* damageZone_;
};