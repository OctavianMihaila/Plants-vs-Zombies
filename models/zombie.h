#pragma once

#include <random>
#include "../assets/basic_objects.h"

class Zombie {
public:
	Zombie::Zombie(const std::string& name, glm::vec3 center, float length, glm::vec3 firstHexagonColor, glm::vec3 secondHexagonColor, int zombieType);
	~Zombie();

	void SetReadyToBeRemoved(bool readyToBeRemoved);
	void SetXScale(float xScale);
	void SetYScale(float yScale);
	void AjustPosition(float x, float y);
	Mesh* GetMesh() const;
	glm::vec3 GetPosition() const;
	int GetZombieType() const;
	float GetXTravelDistance() const;
	float GetRadius() const;
	float GetXScale() const;
	float GetYScale() const;
	int GetTotalDamageTaken() const;
	static bool IsTimeToSpawn();
	bool IsReadyToBeRemoved() const;
	void UpdatePosition(float oldXTravelDistance_, float newTravelDistance_);
	void TakeDamage(int damage);
	static void UpdateSpawnTime();
	static void IncreaseWithDeltaTime(float deltaTimeSeconds);
	void IncreaseXTravelDistance(float xTravelDistance);

private:
	Mesh* mesh_;
	glm::vec3 position_;
	int zombieType_;
	int totalDamageTaken_;
	float xTravelDistance_; // Used to determinate how far the plant should be rendered.
	float radius_;
	float xScale_;
	float yScale_;
	static float spawnInterval_;
	static float timeSinceLastSpawn_;
	bool readyToBeRemoved_;

};