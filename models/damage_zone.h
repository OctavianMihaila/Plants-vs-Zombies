#pragma once

#include "../assets/basic_objects.h"

class DamageZone {
public:
	DamageZone(const std::string& name, glm::vec3 center, float width, float length, glm::vec3 color);
	~DamageZone();

	Mesh* GetMesh() const;

	void RemoveLife();

private:
	Mesh* mesh_;
	int totalDamageTaken_;
};