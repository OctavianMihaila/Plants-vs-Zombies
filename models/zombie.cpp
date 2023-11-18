// zombie.cpp

#include "zombie.h"

float Zombie::spawnInterval_ = 0.0f;
float Zombie::timeSinceLastSpawn_ = 0.0f;

Zombie::Zombie(const std::string& name, glm::vec3 center, float length, glm::vec3 firstHexagonColor, glm::vec3 secondHexagonColor, int zombieType) {
    mesh_ = basic_objects::CreateMergedHexagons(name, center, length, firstHexagonColor, secondHexagonColor);
    position_ = center;
    radius_ = length / 2.0f;
    xScale_ = 1.0f;
    yScale_ = 1.0f;
    std::random_device rd; // Obtain a random number from hardware.
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<float> distribution(5.0f, 10.0f);
    spawnInterval_ = distribution(generator);
    zombieType_ = zombieType;
    totalDamageTaken_ = 0;
    timeSinceLastSpawn_ = 0.0f;
    xTravelDistance_ = 0.0f;
    readyToBeRemoved_ = false;
}

Zombie::~Zombie() {
    delete mesh_;
}

void Zombie::SetReadyToBeRemoved(bool readyToBeRemoved) {
	readyToBeRemoved_ = readyToBeRemoved;
}

void Zombie::SetXScale(float xScale) {
	xScale_ = xScale;
}

void Zombie::SetYScale(float yScale) {
	yScale_ = yScale;
}

float Zombie::GetXScale() const {
	return xScale_;
}

float Zombie::GetYScale() const {
	return yScale_;
}

int Zombie::GetZombieType() const {
	return zombieType_;
}

glm::vec3 Zombie::GetPosition() const {
	return position_;
}

float Zombie::GetXTravelDistance() const {
	return xTravelDistance_;
}

float Zombie::GetRadius() const {
	return radius_;
}

int Zombie::GetTotalDamageTaken() const {
	return totalDamageTaken_;
}

Mesh* Zombie::GetMesh() const {
    return mesh_;
}

bool Zombie::IsTimeToSpawn() {
    return timeSinceLastSpawn_ >= spawnInterval_;
}

bool Zombie::IsReadyToBeRemoved() const {
	return readyToBeRemoved_;
}

void Zombie::TakeDamage(int damage) {
	totalDamageTaken_ += damage;
}

void Zombie::AjustPosition(float x, float y) {
    position_.x += x;
    position_.y += y;
}

void Zombie::UpdatePosition(float oldXTravelDistance_, float newTravelDistance_) {
	position_.x -= newTravelDistance_ - oldXTravelDistance_;
}
void Zombie::UpdateSpawnTime() {
    timeSinceLastSpawn_ = 0.0f;
}

void Zombie::IncreaseWithDeltaTime(float deltaTimeSeconds) {
    timeSinceLastSpawn_ += deltaTimeSeconds;
}

void Zombie::IncreaseXTravelDistance(float xTravelDistance) {
	xTravelDistance_ += xTravelDistance;
}

