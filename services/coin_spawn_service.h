#pragma once

#include <vector>
#include "../engine/board_manager.h"
#include "../models/coin.h"
#include "../models/zombie.h"

class CoinSpawnService {
public:
    CoinSpawnService();

    void HandleCoinSpawn(BoardManager *boardManager, float deltaTimeSeconds);
    void HandleCoinCollection(BoardManager *boardManager, int mouseX, int mouseYInScene, bool& wasCoinClicked);
private:
};
