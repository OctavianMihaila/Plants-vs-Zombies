#include "board_manager.h"

class PlantManager {
public:
    PlantManager(BoardManager* boardMgr);
    void PlantSpellPositionUpdate(PlantSpell* plantSpell, float deltaTimeSeconds, std::string& spellHash);
    void UpdatePlant(PlantSite* plantSite, Plant* plant, float deltaTimeSeconds, int plantNumber);
private:
    void UpdatePlantRemoval(PlantSite* plantSite, Plant* plant, float deltaTimeSeconds);
    void UpdatePlantBehavior(PlantSite* plantSite, Plant* plant, float deltaTimeSeconds, int plantNumber);
    void LaunchSpell(PlantSite* plantSite, Plant* plant, int line);

    BoardManager* boardManager;
};
