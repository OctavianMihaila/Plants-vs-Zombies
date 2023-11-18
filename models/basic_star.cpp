#include "basic_star.h"

BasicStar::BasicStar(const std::string& name, glm::vec3 center, float length, glm::vec3 color) {
    mesh_ = basic_objects::CreateStar(name, center, length, color);
    position_ = center;

    CalculateRadius();
}

BasicStar::~BasicStar() {
    delete mesh_;
}

Mesh* BasicStar::GetMesh() const {
    return mesh_;
}

float BasicStar::GetRadius() const {
    return radius_;
}

glm::vec3 BasicStar::GetPosition() const {
    return position_;
}

void BasicStar::SetPosition(const glm::vec3& newPosition) {
    position_ = newPosition;
}

void BasicStar::UpdatePosition(float oldXTravelDistance_, float newTravelDistance_) {
    position_.x += newTravelDistance_ - oldXTravelDistance_;
}

void BasicStar::CalculateRadius() {
    for (int i = 0; i < mesh_->vertices.size(); i++) {
		float distance = glm::distance(mesh_->vertices[i].position, position_);
        if (distance > radius_) {
			radius_ = distance;
		}
	}
}
