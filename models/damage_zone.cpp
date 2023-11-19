#include "damage_zone.h"

DamageZone::DamageZone(const std::string& name, glm::vec3 center,
                        float length, float width, glm::vec3 color) {
    mesh_ = basic_objects::CreateRectangle(name, center, length, width, color, true);
}

DamageZone::~DamageZone() {
    delete mesh_;
}

Mesh* DamageZone::GetMesh() const {
    return mesh_;
}
