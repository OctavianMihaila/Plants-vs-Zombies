#pragma once

#include <random>
#include "basic_star.h"

class Coin : public BasicStar {
public:
    Coin(const std::string& name, glm::vec3 center, float length, glm::vec3 color, float xTranslate, float yTranslate);

    float GetXTranslate() const;
    float GetYTranslate() const;
    bool IsCollected() const;
    void Collect();

    // Method to check if it's time to spawn a new coin
    static bool IsTimeToSpawn();

    // Method to update the spawn time for the next coin
    static void UpdateSpawnTime();

    static void IncreaseWithDeltaTime(float deltaTimeSeconds);

private:
    float xTranslate_;
    float yTranslate_;
    bool isCollected_;
    static float spawnInterval_; // Time interval for spawning a new coin
    static float timeSinceLastSpawn_; // Time elapsed since the last coin spawn
};
