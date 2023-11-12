#include "board_manager.h"

BoardManager::BoardManager(GameAssetFactory* assetFactory) : assetFactory_(assetFactory) {
    currentlyDraggedPlant_ = NULL;
}

BoardManager::~BoardManager() {}

void BoardManager::AddPlantSite(PlantSite* plantSite) {
    plantSites_.push_back(plantSite);
    return;

}

void BoardManager::AddPlantSpell(PlantSpell* plantSpell, std::string key) {
    plantSpells_[key].push_back(plantSpell);
    return;

}

void BoardManager::AddZombie(Zombie* zombie, std::string key) {
    zombies_[key].push_back(zombie);
    return;

}

void BoardManager::AddPlant(Plant* plant) {
    plants_.push_back(plant);
    return;
}

void BoardManager::AddLife(BasicSquare* life) {
    lives_.push_back(life);
    return;
}

void BoardManager::AddCoin(Coin* coin) {
    spawnedCoins_.push_back(coin);
    return;
}

void BoardManager::AddCollectedCoin(BasicStar* collectedCoin) {
    collectedCoins_.push_back(collectedCoin);
    return;
}

void BoardManager::AddInventorySquare(BasicSquare* inventorySquare) {
	inventorySquares_.push_back(inventorySquare);
	return;
}

void BoardManager::SetDamageZone(DamageZone* damageZone) {
    // Implementation for setting the damage zone
    return;
}

void BoardManager::RemovePlantSite(PlantSite* plantSite) {
    // Implementation for removing a plant site
    return;
}

void BoardManager::RemovePlantSpell(PlantSpell* plantSpell, const std::string& spellHash) {
    auto iterator = plantSpells_.find(spellHash);

    if (iterator != plantSpells_.end()) {
        auto& plantVector = iterator->second; // Getting the vector of plant spells that corresponds to the key.
        plantVector.erase(std::remove(plantVector.begin(), plantVector.end(), plantSpell), plantVector.end());

        delete plantSpell;

        if (plantVector.empty()) {
            plantSpells_.erase(iterator);
        }
    }
}

void BoardManager::RemoveZombie(Zombie* zombie) {
    // Implementation for removing a zombie
    return;
}

void BoardManager::RemovePlant(Plant* plant) {
    // Implementation for removing a plant
    return;
}

void BoardManager::RemoveLife(BasicSquare* life) {
    // Implementation for removing a life
    return;
}

void BoardManager::RemoveCoin(Coin* coin) {
    // Implementation for removing a coin
    return;
}

void BoardManager::RemoveDamageZone(DamageZone* damageZone) {
    // Implementation for removing the damage zone
    return;
}

void BoardManager::RemoveSpawnedCoin(Coin* coin) {
    spawnedCoins_.erase(std::remove(spawnedCoins_.begin(), spawnedCoins_.end(), coin), spawnedCoins_.end());
	return;
}

void BoardManager::RemoveCollectedCoins(int cost) {
    while (cost > 0) {
		collectedCoins_.pop_back();
		cost--;
	}
}

void BoardManager::InitializePlantSites(std::unordered_map<std::string, Mesh*>* meshes) {
    for (int i = 0; i < NR_PLANT_SITES; i++) {
        float x = PLANT_SITE_SQUARE_LEFT_OFFSET + (i % 3) * (PLANT_SITE_SQUARE_SIDE + PLANT_SITE_SQUARE_OFFSET);
        float y = (2 - i / 3) * (PLANT_SITE_SQUARE_SIDE + PLANT_SITE_SQUARE_OFFSET);
        glm::vec3 center = glm::vec3(x, y, 0);
        glm::vec3 color = glm::vec3(0, 1, 0); // green
        PlantSite* plantSite = assetFactory_->CreatePlantSite("plantSite" + std::to_string(i), center, PLANT_SITE_SQUARE_SIDE, color);
        
        AddPlantSite(plantSite);
    }
}

void BoardManager::InitializePlantSpells() {
    // Implementation for initializing plant spells
    return;
}

void BoardManager::InitializeZombies() {
    // Implementation for initializing zombies
    return;
}

void BoardManager::InitializePlants() {
    // Implementation for initializing plants
    return;
}

void BoardManager::InitializeLives(std::unordered_map<std::string, Mesh*>* meshes) {
    float xLife = SCREEN_WIDTH - LIVES_RIGHT_OFFSET - LIVES_SQUARE_OFFSET;
    float yLife = SCREEN_HEIGHT - LIVES_TOP_OFFSET - LIVES_SQUARE_SIDE;
    glm::vec3 lifeCenter = glm::vec3(xLife, yLife, 0);
    glm::vec3 starCenter = glm::vec3(0, 0, 0);
    glm::vec3 lifeColor = glm::vec3(1, 0, 0); // red
    glm::vec3 starColor = glm::vec3(0.5f, 0.5f, 0.5f); // grey


    for (int i = 0; i < NR_LIVES; i++) {
		BasicSquare* life = assetFactory_->CreateBasicSquare("life" + std::to_string(i), lifeCenter, LIVES_SQUARE_SIDE, lifeColor, true);
        Mesh* mesh = life->GetMesh();

		(*meshes)[mesh->GetMeshID()] = mesh;
		lives_.push_back(life);

		xLife -= LIVES_SQUARE_SIDE + LIVES_SQUARE_OFFSET;
		lifeCenter = glm::vec3(xLife, yLife, 0);

        // also add star representing initial coin (one in each iteration).
        BasicStar* star = assetFactory_->CreateBasicStar("lifeStar" + std::to_string(i), starCenter, STAR_SIDE, starColor);
        Mesh* starMesh = star->GetMesh();

        (*meshes)[starMesh->GetMeshID()] = starMesh;
        collectedCoins_.push_back(star);
	}

    return;
}

void BoardManager::InitializeCoins() {
    // Implementation for initializing coins
    return;
}

void BoardManager::InitializeCollectedCoins() {
    // Implementation for initializing collected coins
    return;
}

void BoardManager::InitializeDamageZone(std::unordered_map<std::string, Mesh*>* meshes) {
    glm::vec3 center = glm::vec3(DAMAGE_ZONE_LEFT_OFFSET, 0, 0);
    glm::vec3 color = glm::vec3(1, 0, 0); // red
    DamageZone* damageZone = assetFactory_->CreateDamageZone("damageZone", center, DAMAGE_ZONE_LENGTH, DAMAGE_ZONE_HEIGHT, color);
    Mesh * mesh = damageZone->GetMesh();

	(*meshes)[mesh->GetMeshID()] = mesh;
    damageZone_ = damageZone;

    return;
}

void BoardManager::InitializeInventory(std::unordered_map<std::string, Mesh*>* meshes) {
    glm::vec3 emptySquareColor = glm::vec3(0.5f, 0.35f, 0.05f); // brown
    glm::vec3 starColor = glm::vec3(0.5f, 0.5f, 0.5f); // grey
    glm::vec3 plantType1Color = glm::vec3(1, 0.5f, 0); // orange
    glm::vec3 plantType2Color = glm::vec3(0, 0, 1); // blue
    glm::vec3 plantType3Color = glm::vec3(1, 1, 0); // yellow
    glm::vec3 plantType4Color = glm::vec3(1, 0, 1); // purple


    float x = INVENTORY_SQUARE_LEFT_OFFSET;
    float y = SCREEN_HEIGHT - INVENTORY_SQUARE_TOP_OFFSET - INVENTORY_SQUARE_SIDE;
    glm::vec3 center = glm::vec3(x, y, 0);

    for (int i = 0; i < NR_INVENTORY_SLOTS; i++) {
        // Creating inventory square in which the plant will be placed.
        BasicSquare* inventorySquare = assetFactory_->CreateBasicSquare("inventorySquare" + std::to_string(i), center, INVENTORY_SQUARE_SIDE, emptySquareColor, false);
        AddInventorySquare(inventorySquare);

        // Create plant inside square
        int plantType = i + 1;
        float cost = CalculatePlantCost(plantType);
        glm::vec3 plantColor = FindPlantColor(plantType);

        center = glm::vec3(x + INVENTORY_SQUARE_SIDE / 4, y + INVENTORY_SQUARE_SIDE / 2, 0);
        Plant* plant = assetFactory_->CreatePlant("inventoryPlant" + std::to_string(i), center, DIAMOND_WIDTH, DIAMOND_HEIGHT, plantColor, plantType, cost);
        Mesh* plantMesh = plant->GetMesh();
        (*meshes)[plantMesh->GetMeshID()] = plantMesh;

        int nrStars = plantType;
        if (plantType == 3 || plantType == 4) {
            nrStars--;
		}
 
        // Display stars under the square (cost).
        glm::vec3 starCenter = glm::vec3(0, 0, 0);
        for (int j = 0; j < nrStars; j++) {
			BasicStar* star = assetFactory_->CreateBasicStar("inventoryStar" + std::to_string(i) + std::to_string(j), starCenter, STAR_SIDE, starColor);
			Mesh* starMesh = star->GetMesh();
			(*meshes)[starMesh->GetMeshID()] = starMesh;
		}

        x += INVENTORY_SQUARE_SIDE + INVENTORY_SQUARE_OFFSET;
        center = glm::vec3(x, y, 0);
    }
}

void BoardManager::InitializeThreeCoins(std::unordered_map<std::string, Mesh*>* meshes) {
    glm::vec3 color = glm::vec3(0.5f, 0.0f, 0.5f); // purple
    glm::vec3 center = glm::vec3(0, 0, 1.0f);
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 mt(rd()); // seed the generator

    // get nr of spawned coins
    int nrSpawnedCoins = GetNrLifeStars();

    for (int i = nrSpawnedCoins; i < nrSpawnedCoins + NR_COINS_TO_SPAWN; i++) {
        std::uniform_real_distribution<float> distX(0.f, 1280.f);
        std::uniform_real_distribution<float> distY(0.f, 720.f);
        float x = distX(mt);
        float y = distY(mt);
		Coin* coin = assetFactory_->CreateCoin("coin" + std::to_string(i), center, COIN_SIDE, color, x, y);

		spawnedCoins_.push_back(coin);
	}

    return;
}

void BoardManager::LaunchSpell(int line, int plantType, glm::vec3 center) {
    std::string spellHash = std::to_string(line) + std::to_string(plantType);
    glm::vec3 color = FindPlantColor(plantType);
    PlantSpell* plantSpell = assetFactory_->CreatePlantSpell("spell" + spellHash, center, SPELL_STAR_SIDE, color, plantType);

    AddPlantSpell(plantSpell, spellHash);
}

void BoardManager::setCurrentlyDraggedPlant(Plant* plant) {
	currentlyDraggedPlant_ = plant;
}

GameAssetFactory* BoardManager::GetAssetFactory() const {
	return assetFactory_;
}

std::vector<PlantSite*> BoardManager::GetPlantSites() const {
    // Implementation for getting plant sites
    return plantSites_;
}

std::unordered_map<std::string, std::vector<PlantSpell*>> BoardManager::GetPlantSpells() const {
    // Implementation for getting plant spells
    return plantSpells_;
}

std::unordered_map<std::string, std::vector<Zombie*>> BoardManager::GetZombies() const {
    return zombies_;
}

std::vector<Plant*> BoardManager::GetPlants() const {
    return plants_;
}

std::vector<BasicSquare*> BoardManager::GetLives() const {
    return lives_;
}

std::vector<Coin*> BoardManager::GetSpawnedCoins() const {
    return spawnedCoins_;
}

std::vector<BasicStar*> BoardManager::GetCollectedCoins() const {
    return collectedCoins_;
}

DamageZone* BoardManager::GetDamageZone() const {
	return damageZone_;
}

Plant* BoardManager::GetCurrentlyDraggedPlant() const {
	return currentlyDraggedPlant_;
}

int BoardManager::GetNrLifeStars() const {
	return collectedCoins_.size();
}

std::vector<BasicSquare*> BoardManager::GetInventorySquares() const {
	return inventorySquares_;
}

void BoardManager::ClearPlantSites() {
    // TODO
    return;
}

void BoardManager::ClearPlantSpells() {
    // TODO
    return;
}

void BoardManager::ClearZombies() {
    // TODO
    return;
}

void BoardManager::ClearPlants() {
    // TODO
    return;
}

void BoardManager::ClearLives() {
    // TODO
    return;
}

void BoardManager::ClearSpawnedCoins() {
    // TODO
    return;
}

void BoardManager::ClearCollectedCoins() {
    // TODO
    return;
}

void BoardManager::ClearDamageZone() {
    // TODO
    return;
}

void BoardManager::Update(float deltaTime) {
    // Implementation for the Update function
}

void BoardManager::Draw(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) {
    // Implementation for the Draw function
}
