// damage_zone.cpp

#include "damage_zone.h"

DamageZone::DamageZone(const std::string& name, glm::vec3 center, float length, float width, glm::vec3 color) {
    // Create the mesh for the damage zone using the provided parameters
    mesh_ = basic_objects::CreateRectangle(name, center, length, width, color, true);
    totalDamageTaken_ = 0;
}

DamageZone::~DamageZone() {
    // Clean up any resources if needed
    delete mesh_;
}

Mesh* DamageZone::GetMesh() const {
    return mesh_;
}

void DamageZone::RemoveLife() {
    // Implement logic to remove life or apply damage to entities within the damage zone.
    // You can increment the totalDamageTaken_ here.
    // For example:
    // totalDamageTaken_++;
}
