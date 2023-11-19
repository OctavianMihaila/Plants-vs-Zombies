#pragma once

#include <random>
#include "basic_star.h"

class Coin : public BasicStar {
public:
    Coin(const std::string& name, glm::vec3 center, float length,
            glm::vec3 color, float xTranslate, float yTranslate);

    float GetXTranslate() const;
    float GetYTranslate() const;
    bool IsCollected() const;
    static bool IsTimeToSpawn();
    static void IncreaseWithDeltaTime(float deltaTimeSeconds);
    static void UpdateSpawnTime();
    void Collect();

private:
    static float spawnInterval_; // Time interval for spawning a new coin.
    static float timeSinceLastSpawn_; // Time elapsed since the last coin spawn.
    float xTranslate_;
    float yTranslate_;
    bool isCollected_;
};
