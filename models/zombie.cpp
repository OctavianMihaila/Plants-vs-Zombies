// zombie.cpp

#include "zombie.h"

Zombie::Zombie(const std::string& name, glm::vec3 center, float length, glm::vec3 firstHexagonColor, glm::vec3 secondHexagonColor, int zombieType) {
    // Create the mesh for the zombie using the provided parameters
    mesh_ = basic_objects::CreateMergedHexagons(name, center, length, firstHexagonColor, secondHexagonColor);
    zombieType_ = zombieType;
    totalDamageTaken_ = 0;
}

Zombie::~Zombie() {
    // Clean up any resources if needed
    // You should delete the zombie's mesh here, if it wasn't deleted earlier.
    // delete zombieMesh;
}

Mesh* Zombie::GetMesh() const {
    // Return the zombie's mesh
    // Note: Make sure to store the mesh in a member variable if it's needed outside this function.
    return mesh_;
}
