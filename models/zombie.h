#pragma once

#include <random>
#include "../assets/basic_objects.h"

class Zombie {
public:
	Zombie::Zombie(const std::string& name, glm::vec3 center, float length,
					glm::vec3 firstHexagonColor, glm::vec3 secondHexagonColor, int zombieType);
	~Zombie();

	void SetReadyToBeRemoved(bool readyToBeRemoved);
	void SetXScale(float xScale);
	void SetYScale(float yScale);
	int GetZombieType() const;
	float GetXTravelDistance() const;
	float GetRadius() const;
	float GetXScale() const;
	float GetYScale() const;
	int GetTotalDamageTaken() const;
	glm::vec3 GetPosition() const;
	Mesh* GetMesh() const;
	static bool IsTimeToSpawn();
	bool IsReadyToBeRemoved() const;
	void UpdatePosition(float oldXTravelDistance_, float newTravelDistance_);
	void TakeDamage(int damage);
	void AjustPosition(float x, float y);
	static void UpdateSpawnTime();
	static void IncreaseWithDeltaTime(float deltaTimeSeconds);
	void IncreaseXTravelDistance(float xTravelDistance);

private:
	static float spawnInterval_;
	static float timeSinceLastSpawn_;
	float xTravelDistance_; // Used to determinate how far the plant should be rendered.
	float radius_;
	float xScale_;
	float yScale_;
	int zombieType_;
	int totalDamageTaken_;
	bool readyToBeRemoved_;
	glm::vec3 position_;
	Mesh* mesh_;
};