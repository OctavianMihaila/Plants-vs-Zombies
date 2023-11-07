#include "basic_star.h"

BasicStar::BasicStar(const std::string& name, glm::vec3 center, float length, glm::vec3 color) {
    mesh_ = basic_objects::CreateStar(name, center, length, color);
    position_ = center;
}

BasicStar::~BasicStar() {
    delete mesh_;
}

Mesh* BasicStar::GetMesh() const {
    return mesh_;
}

glm::vec3 BasicStar::GetPosition() const {
    return position_;
}

void BasicStar::SetPosition(const glm::vec3& newPosition) {
    position_ = newPosition;
}
