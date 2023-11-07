#include "basic_square.h"

BasicSquare::BasicSquare(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill) {
	mesh_ = basic_objects::CreateRectangle(name, center, length, length, color, fill);
	position_ = center;
}

BasicSquare::~BasicSquare() {
	delete mesh_;
}

Mesh* BasicSquare::GetMesh() const {
	return mesh_;
}

glm::vec3 BasicSquare::GetPosition() const {
	return position_;
}

void BasicSquare::SetPosition(const glm::vec3& newPosition) {
	position_ = newPosition;
}