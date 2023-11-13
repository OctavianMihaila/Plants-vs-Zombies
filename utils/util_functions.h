#pragma once

#include <glm/glm.hpp>
#include <iostream>

#define COLLISION_DISTANCE_OFFSET 45.0f

inline int CalculatePlantCost(int plantType);
inline glm::vec3 FindPlantColor(int plantType);
inline bool CheckClickInSquare(float mouseX, float mouseY, float squareX, float squareY, float squareSide);
inline bool CheckCollision(glm::vec3 firstObjectPosition, glm::vec3 secondObjectPosition, float radius1, float radius2);
inline bool CheckZombieTypeInVector(int zombieType, std::vector<Zombie*> zombies);

inline int CalculatePlantCost(int plantType) {
    int cost = 0;

    switch (plantType) {
    case 1:
        cost = 1;
        break;
    case 2:
    case 3:
        cost = 2;
        break;
    case 4:
        cost = 3;
        break;
    default:
        std::cout << "Invalid plant type!" << std::endl;
        break;
    }

    return cost;
}

inline glm::vec3 FindPlantColor(int plantType) {
    glm::vec3 plantColor(0.0f, 0.0f, 0.0f);  // Default to black for unknown plant type

    switch (plantType) {
    case 1:
        plantColor = glm::vec3(1.0f, 0.5f, 0.0f);  // Orange
        break;
    case 2:
        plantColor = glm::vec3(0.0f, 0.0f, 1.0f);  // Blue
        break;
    case 3:
        plantColor = glm::vec3(1.0f, 1.0f, 0.0f);  // Yellow
        break;
    case 4:
        plantColor = glm::vec3(1.0f, 0.0f, 1.0f);  // Purple
        break;
    default:
        std::cout << "Invalid plant type!" << std::endl;
        break;
    }

    return plantColor;
}

inline bool CheckClickInSquare(float mouseX, float mouseY, float squareX, float squareY, float squareSide) {
    float xMin = squareX;
    float xMax = squareX + squareSide;
    float yMin = squareY;
    float yMax = squareY + squareSide;

    return (mouseX >= xMin && mouseX <= xMax && mouseY >= yMin && mouseY <= yMax);
}

inline bool CheckCollision(glm::vec3 firstObjectPosition, glm::vec3 secondObjectPosition, float radius1, float radius2) {
	float distance = glm::distance(firstObjectPosition, secondObjectPosition);
    std::cout<<"distance: "<<distance<<std::endl;
	float sumRadius = radius1 + radius2;
    std::cout<<"sumRadius: "<<sumRadius<<std::endl;

	return (distance - COLLISION_DISTANCE_OFFSET <= sumRadius);
}

inline bool CheckZombieTypeInVector(int zombieType, std::vector<Zombie*> zombies) {
    for (auto zombie : zombies) {
        if (zombie->GetZombieType() == zombieType) {
			return true;
		}
	}

	return false;
}

