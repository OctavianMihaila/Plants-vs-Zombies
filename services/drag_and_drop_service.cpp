#include "drag_and_drop_service.h"

DragAndDropService::DragAndDropService() {}

void DragAndDropService::HandleInventoryPlantClick(BoardManager* boardManager, int mouseX, int mouseYInScene) {
    int selectedPlantType = FindSelectedPlantType(boardManager->GetInventorySquares(), mouseX, mouseYInScene, INVENTORY_SQUARE_SIDE);

    if (selectedPlantType != -1) {
        int cost = CalculatePlantCost(selectedPlantType);
        glm::vec3 plantColor = FindPlantColor(selectedPlantType);

        Plant* draggedPlant = boardManager->GetAssetFactory()->CreatePlant("draggedPlant", glm::vec3(mouseX + DIAMOND_WIDTH / 2, mouseYInScene, 1), DIAMOND_WIDTH, DIAMOND_HEIGHT, plantColor, selectedPlantType, cost);
        boardManager->setCurrentlyDraggedPlant(draggedPlant);
    }
}

void DragAndDropService::HandlePlantRelease(BoardManager* boardManager, int mouseX, int mouseYInScene) {
    Plant* currentlyDraggedPlant = boardManager->GetCurrentlyDraggedPlant();

    if (currentlyDraggedPlant != NULL) {
        std::vector<PlantSite*> plantSites = boardManager->GetPlantSites();

        for (PlantSite* plantSite : plantSites) {
            glm::vec3 plantSitePosition = plantSite->GetPosition();
            glm::vec3 clickPosition = glm::vec3(mouseX, mouseYInScene, 0);

            if (CheckClickInSquare(mouseX, mouseYInScene, plantSitePosition.x, plantSitePosition.y, PLANT_SITE_SQUARE_SIDE)) {
                int cost = currentlyDraggedPlant->GetCost();
                int nrCoins = boardManager->GetCollectedCoins().size();

                // Place the plant on the plant site.
                if (plantSite->IsEmpty() && cost <= nrCoins) {
                    plantSite->SetPlant(currentlyDraggedPlant);
                    boardManager->RemoveCollectedCoins(cost);
                    break;
                }

            }

        }

        boardManager->setCurrentlyDraggedPlant(NULL);
    }
}

void DragAndDropService::HandlePlantDespawning(BoardManager* boardManager, int mouseX, int mouseYInScene) {
    std::vector<PlantSite*> plantSites = boardManager->GetPlantSites();

    for (PlantSite* plantSite : plantSites) {
        glm::vec3 plantSitePosition = plantSite->GetPosition();
        glm::vec3 clickPosition = glm::vec3(mouseX, mouseYInScene, 0);

        if (CheckClickInSquare(mouseX, mouseYInScene, plantSitePosition.x, plantSitePosition.y, PLANT_SITE_SQUARE_SIDE) && !plantSite->IsEmpty()) {
            plantSite->SetPlantReadyToBeRemoved(true);
            break;
        }
    }
}
