#include "board_manager.h"

class ZombieManager {
public:
    ZombieManager(BoardManager* boardManager);

    void ZombieManager::UpdateZombie(Zombie* zombie, std::string zombieHash, float deltaTimeSeconds);
    void HandleZombieSpawn(float deltaTimeSeconds);

private:
    void UpdateZombieRemoval(Zombie* zombie, std::string& zombieHash, float deltaTimeSeconds);
    void UpdateZombieMovement(Zombie* zombie, float deltaTimeSeconds);
    void CheckAndRemoveLife(Zombie* zombie, std::string& zombieHash);
    void CheckAndRemovePlant(Zombie* zombie, std::vector<PlantSite*>& plantSites, int line);
    void HandleZombiePlantSpellCollision(Zombie* zombie, std::unordered_map<std::string,
                                            std::vector<PlantSpell*>>& plantSpells,
                                            std::string& zombieHash);

    BoardManager* boardManager;
};
