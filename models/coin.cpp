#include "Coin.h"

float Coin::spawnInterval_ = 0.0f;
float Coin::timeSinceLastSpawn_ = 0.0f;

Coin::Coin(const std::string& name, glm::vec3 center, float length, glm::vec3 color, float xTranslate, float yTranslate)
    : BasicStar(name, center, length, color), isCollected_(false), xTranslate_(xTranslate), yTranslate_(yTranslate) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(7.0f, 12.0f); // Adjust the range as needed

    spawnInterval_ = dist(mt);
    timeSinceLastSpawn_ = 0.0f;
}

float Coin::GetXTranslate() const {
	return xTranslate_;
}

float Coin::GetYTranslate() const {
	return yTranslate_;
}

bool Coin::IsCollected() const {
    return isCollected_;
}

void Coin::Collect() {
    isCollected_ = true;
}

bool Coin::IsTimeToSpawn() {
    // Check if enough time has passed since the last spawn
    return timeSinceLastSpawn_ >= spawnInterval_;
}

void Coin::UpdateSpawnTime() {
    timeSinceLastSpawn_ = 0.0f;
}

void Coin::IncreaseWithDeltaTime(float deltaTimeSeconds) {
	timeSinceLastSpawn_ += deltaTimeSeconds;
}
