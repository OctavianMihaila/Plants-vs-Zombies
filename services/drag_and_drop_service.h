#pragma once

#include "../engine/board_manager.h"

class DragAndDropService {
public:
    DragAndDropService();

    void HandleInventoryPlantClick(BoardManager* boardManager, int mouseX, int mouseYInScene);
    void HandlePlantRelease(BoardManager* boardManager, int mouseX, int mouseYInScene);
    void HandlePlantDespawning(BoardManager* boardManager, int mouseX, int mouseYInScene);
};
