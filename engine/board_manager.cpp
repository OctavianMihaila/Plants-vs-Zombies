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

void BoardManager::AddCollectedCoin(BasicStar* collectedCoin) {
    collectedCoins_.push_back(collectedCoin);
    return;
}

void BoardManager::AddInventorySquare(BasicSquare* inventorySquare) {
	inventorySquares_.push_back(inventorySquare);
	return;
}

void BoardManager::AddInventoryStar(BasicStar* inventoryStar) {
	inventoryStars_.push_back(inventoryStar);
	return;
}

void BoardManager::AddInventoryPlant(Plant* inventoryPlant) {
    inventoryPlants_.push_back(inventoryPlant);
	return;
}

void BoardManager::RemovePlantSpell(PlantSpell* plantSpell, const std::string& spellHash) {
    auto iterator = plantSpells_.find(spellHash);

    if (iterator != plantSpells_.end()) {
        // Getting the vector of plant spells that corresponds to the key.
        auto& plantVector = iterator->second;
        plantVector.erase(std::remove(plantVector.begin(), plantVector.end(),
                            plantSpell), plantVector.end());

        delete plantSpell;

        if (plantVector.empty()) {
            plantSpells_.erase(iterator);
        }
    }
}

void BoardManager::RemoveZombie(Zombie* zombie, std::string zombieHash) {
    std::vector<Zombie*> zombies = zombies_[zombieHash];

    zombies.erase(std::remove(zombies.begin(), zombies.end(), zombie), zombies.end());
    zombies_[zombieHash] = zombies;
    delete zombie;

    return;
}

void BoardManager::RemoveLife() {
    lives_.pop_back();

    return;
}

void BoardManager::RemoveSpawnedCoin(Coin* coin) {
    spawnedCoins_.erase(std::remove(spawnedCoins_.begin(), spawnedCoins_.end(), coin),
                                        spawnedCoins_.end());
	return;
}

void BoardManager::RemoveCollectedCoins(int cost) {
    while (cost > 0) {
		collectedCoins_.pop_back();
		cost--;
	}
}

void BoardManager::InitializePlantSites() {
    for (int i = 0; i < NR_PLANT_SITES; i++) {
        float x = PLANT_SITE_SQUARE_LEFT_OFFSET + (i % 3) *
            (PLANT_SITE_SQUARE_SIDE + PLANT_SITE_SQUARE_OFFSET);
        float y = (2 - i / 3) * (PLANT_SITE_SQUARE_SIDE + PLANT_SITE_SQUARE_OFFSET);
        glm::vec3 center = glm::vec3(x, y, 0);
        glm::vec3 color = glm::vec3(0, 1, 0); // Green.
        PlantSite* plantSite = assetFactory_->
            CreatePlantSite("plantSite" + std::to_string(i),
                              center, PLANT_SITE_SQUARE_SIDE, color);
        
        AddPlantSite(plantSite);
    }
}

void BoardManager::InitializeLives() {
    float xLife = SCREEN_WIDTH - LIVES_RIGHT_OFFSET - LIVES_SQUARE_OFFSET;
    float yLife = SCREEN_HEIGHT - LIVES_TOP_OFFSET - LIVES_SQUARE_SIDE;
    glm::vec3 lifeCenter = glm::vec3(xLife, yLife, 0);
    glm::vec3 starCenter = glm::vec3(0, 0, 0);
    glm::vec3 lifeColor = glm::vec3(1, 0, 0); // Red.
    glm::vec3 starColor = glm::vec3(0.5f, 0.5f, 0.5f); // Grey

    for (int i = 0; i < NR_LIVES; i++) {
		BasicSquare* life = assetFactory_->
            CreateBasicSquare("life" + std::to_string(i), lifeCenter,
                                                        LIVES_SQUARE_SIDE, lifeColor, true);
		lives_.push_back(life);

		xLife -= LIVES_SQUARE_SIDE + LIVES_SQUARE_OFFSET;
		lifeCenter = glm::vec3(xLife, yLife, 0);

        // Also add star representing initial coin (one in each iteration).
        BasicStar* star = assetFactory_->CreateBasicStar("lifeStar" + std::to_string(i),
                                                            starCenter, STAR_SIDE, starColor);
        collectedCoins_.push_back(star);
	}

    return;
}

void BoardManager::InitializeDamageZone() {
    glm::vec3 center = glm::vec3(DAMAGE_ZONE_LEFT_OFFSET, 0, 0);
    glm::vec3 color = glm::vec3(1, 0, 0); // Red
    DamageZone* damageZone = assetFactory_->
        CreateDamageZone("damageZone", center, DAMAGE_ZONE_LENGTH,
                            DAMAGE_ZONE_HEIGHT, color);

    damageZone_ = damageZone;

    return;
}

void BoardManager::InitializeInventory() {
    glm::vec3 emptySquareColor = glm::vec3(0.5f, 0.35f, 0.05f); // Brown.
    glm::vec3 starColor = glm::vec3(0.5f, 0.5f, 0.5f); // Grey.
    glm::vec3 plantType1Color = glm::vec3(1, 0.5f, 0); // Orange.
    glm::vec3 plantType2Color = glm::vec3(0, 0, 1); // Blue.
    glm::vec3 plantType3Color = glm::vec3(1, 1, 0); // Yellow.
    glm::vec3 plantType4Color = glm::vec3(1, 0, 1); // Purple.
    float x = INVENTORY_SQUARE_LEFT_OFFSET;
    float y = SCREEN_HEIGHT - INVENTORY_SQUARE_TOP_OFFSET - INVENTORY_SQUARE_SIDE;
    glm::vec3 center = glm::vec3(x, y, 0);

    for (int i = 0; i < NR_INVENTORY_SLOTS; i++) {
        // Creating inventory square in which the plant will be placed.
        BasicSquare* inventorySquare = assetFactory_->
            CreateBasicSquare("inventorySquare" + std::to_string(i), center,
                                INVENTORY_SQUARE_SIDE, emptySquareColor, false);
        AddInventorySquare(inventorySquare);

        // Create plant inside square.
        int plantType = i + 1;
        float cost = CalculatePlantCost(plantType);
        glm::vec3 plantColor = FindPlantColor(plantType);

        center = glm::vec3(x + INVENTORY_SQUARE_SIDE / 4, y + INVENTORY_SQUARE_SIDE / 2, 0);
        Plant* plant = assetFactory_->
            CreatePlant("inventoryPlant" + std::to_string(i), center,
                            DIAMOND_WIDTH, DIAMOND_HEIGHT, plantColor, plantType, cost);
        AddInventoryPlant(plant);

        int nrStars = plantType;
        if (plantType == 3 || plantType == 4) {
            nrStars--;
        }

        // Display stars under the square (cost).
        glm::vec3 starCenter = glm::vec3(0, 0, 0);
        for (int j = 0; j < nrStars; j++) {
            BasicStar* star = assetFactory_->
                CreateBasicStar("inventoryStar" + std::to_string(i) + std::to_string(j),
                                    starCenter, STAR_SIDE, starColor);
            AddInventoryStar(star);
        }

        x += INVENTORY_SQUARE_SIDE + INVENTORY_SQUARE_OFFSET;
        center = glm::vec3(x, y, 0);
    }
}

void BoardManager::InitializeThreeCoins() {
    glm::vec3 color = glm::vec3(0.5f, 0.0f, 0.5f); // Purple
    glm::vec3 center = glm::vec3(0, 0, 10.0f);
    std::random_device rd;
    std::mt19937 mt(rd());
    int nrSpawnedCoins = GetNrCollectedCoins();

    for (int i = nrSpawnedCoins; i < nrSpawnedCoins + NR_COINS_TO_SPAWN; i++) {
        std::uniform_real_distribution<float> distX(0.f, 1280.f);
        std::uniform_real_distribution<float> distY(0.f, 720.f);
        float x = distX(mt);
        float y = distY(mt);
		Coin* coin = assetFactory_->
            CreateCoin("coin" + std::to_string(i), center, COIN_SIDE, color, x, y);

		spawnedCoins_.push_back(coin);
	}

    return;
}

void BoardManager::LaunchZombie() {
    std::random_device rd;
    std::mt19937 mt(rd());
    // Generating a randoom string for the key
    //  (first digit must be between 1 and 3 and the second between 1 and 4).
    std::uniform_int_distribution<int> distLine(1, 3);
    std::uniform_int_distribution<int> distZombieType(1, 4);

    int line = distLine(mt);
    int zombieType = distZombieType(mt);
    std::string zombieHash = std::to_string(line) + std::to_string(zombieType);
    glm::vec3 center = glm::vec3(SCREEN_WIDTH, (3 - line) *
                                    (PLANT_SITE_SQUARE_SIDE + PLANT_SITE_SQUARE_OFFSET) +
                                    PLANT_SITE_SQUARE_OFFSET / 2 + HEXAGON_CALIBRATION_OFFSET, 3.0f);
    glm::vec3 neutralHexagonColor = glm::vec3(0.5f, 0.5f, 0.5f); // Grey.
    // This function can be used for zombies as well.
    glm::vec3 zombieColor = FindPlantColor(zombieType);

    Zombie* zombie = assetFactory_->
        CreateZombie("zombie" + zombieHash, center, ZOMBIE_SIDE,
                        zombieColor, neutralHexagonColor, zombieType);
    AddZombie(zombie, zombieHash);

    return;
}

void BoardManager::LaunchSpell(int line, int plantType, glm::vec3 center) {
    std::string spellHash = std::to_string(line) + std::to_string(plantType);
    glm::vec3 color = FindPlantColor(plantType);
    PlantSpell* plantSpell = assetFactory_->
        CreatePlantSpell("spell" + spellHash, center, SPELL_STAR_SIDE, color, plantType);

    AddPlantSpell(plantSpell, spellHash);
}

void BoardManager::setCurrentlyDraggedPlant(Plant* plant) {
	currentlyDraggedPlant_ = plant;
}

GameAssetFactory* BoardManager::GetAssetFactory() const {
	return assetFactory_;
}

std::vector<PlantSite*> BoardManager::GetPlantSites() const {
    return plantSites_;
}

std::unordered_map<std::string, std::vector<PlantSpell*>> BoardManager::GetPlantSpells() const {
    return plantSpells_;
}

std::unordered_map<std::string, std::vector<Zombie*>> BoardManager::GetZombies() const {
    return zombies_;
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

int BoardManager::GetNrCollectedCoins() const {
	return collectedCoins_.size();
}

std::vector<BasicSquare*> BoardManager::GetInventorySquares() const {
	return inventorySquares_;
}

std::vector<BasicStar*> BoardManager::GetInventoryStars() const {
	return inventoryStars_;
}

std::vector<Plant*> BoardManager::GetInventoryPlants() const {
	return inventoryPlants_;
}