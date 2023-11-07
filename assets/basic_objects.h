#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace basic_objects
{

    // Create square with given bottom left corner, length and color
    //Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color);
    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner, float length, float width, glm::vec3 color, bool fill);
    Mesh* CreateStar(const std::string& name, glm::vec3 center, float length, glm::vec3 color);
    Mesh* CreateDiamond(const std::string& name, glm::vec3 center, float width, float height, glm::vec3 color);
    Mesh* CreateMergedHexagons(const std::string& name, glm::vec3 center, float length, glm::vec3 firstHexagonColor, glm::vec3 secondHexagonColor);



}
