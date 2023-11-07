#pragma once

#include "../assets/basic_objects.h"

class BasicSquare {
public:
	BasicSquare(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill);
	~BasicSquare();

	Mesh* GetMesh() const;
	glm::vec3 GetPosition() const;
	void SetPosition(const glm::vec3& newPosition);

private:
	Mesh* mesh_;
	glm::vec3 position_;
};