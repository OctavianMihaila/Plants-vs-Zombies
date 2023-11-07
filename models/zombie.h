#pragma once

#include "../assets/basic_objects.h"

class Zombie {
public:
	Zombie::Zombie(const std::string& name, glm::vec3 center, float length, glm::vec3 firstHexagonColor, glm::vec3 secondHexagonColor, int zombieType);
	~Zombie();

	Mesh* GetMesh() const;
private:
	Mesh* mesh_;
	int zombieType_;
	int totalDamageTaken_;
};