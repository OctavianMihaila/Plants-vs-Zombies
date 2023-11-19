#include "coin_spawn_service.h"

CoinSpawnService::CoinSpawnService() {}

void CoinSpawnService::HandleCoinSpawn(BoardManager *boardManager, float deltaTimeSeconds) {
    if (Coin::IsTimeToSpawn()) {
        boardManager->InitializeThreeCoins();
        Coin::UpdateSpawnTime();
    }
    else {
        Coin::IncreaseWithDeltaTime(deltaTimeSeconds);
    }
}

void CoinSpawnService::HandleCoinCollection(BoardManager *boardManager, int mouseX,
                                            int mouseYInScene, bool& wasCoinClicked) {
    std::vector<Coin*> spawnedCoins_ = boardManager->GetSpawnedCoins();

    for (Coin* coin : spawnedCoins_) {
        glm::vec3 coinPosition = glm::vec3(coin->GetXTranslate(), coin->GetYTranslate(), 0);

        // Define an imaginary rectangle around the coin.
        glm::vec3 rectPosition = coinPosition;
        float rectSize = STAR_SIDE * 2;

        // Check if the mouse click is inside the imaginary rectangle around the star.
        if (IsPointInsideRect(glm::vec3(mouseX, mouseYInScene, 0), rectPosition, rectSize)) {
            int starIndex = boardManager->GetNrCollectedCoins();
            glm::vec3 starCenter = glm::vec3(0, 0, 0);
            glm::vec3 starColor = glm::vec3(0.5f, 0.5f, 0.5f);
            BasicStar* basicStar = boardManager->
                GetAssetFactory()->CreateBasicStar("lifeStar" + std::to_string(starIndex),
                                                    starCenter, STAR_SIDE, starColor);

            boardManager->AddCollectedCoin(basicStar);
            boardManager->RemoveSpawnedCoin(coin);
            wasCoinClicked = true;

            break;
        }
    }
}