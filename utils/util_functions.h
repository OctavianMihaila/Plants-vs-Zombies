#pragma once

#include <glm/glm.hpp>
#include <iostream>

#define COLLISION_DISTANCE_OFFSET 45.0f

inline int CalculatePlantCost(int plantType);
inline glm::vec3 FindPlantColor(int plantType);
inline int FindSelectedPlantType(std::vector<BasicSquare*> inventorySquares,
                                    int mouseX, int mouseY);
inline bool CheckClickInSquare(float mouseX, float mouseY, float squareX,
                                float squareY, float squareSide);
inline bool CheckCollision(glm::vec3 firstObjectPosition, glm::vec3 secondObjectPosition,
                            float radius1, float radius2);
inline bool CheckZombieTypeInVector(int zombieType, std::vector<Zombie*> zombies);
inline bool IsPointInsideRect(const glm::vec3& point, const glm::vec3& rectPosition, float rectSize);

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
    glm::vec3 plantColor(0.0f, 0.0f, 0.0f);  // Default to black for unknown plant type.

    switch (plantType) {
    case 1:
        plantColor = glm::vec3(1.0f, 0.5f, 0.0f);  // Orange.
        break;
    case 2:
        plantColor = glm::vec3(0.0f, 0.0f, 1.0f);  // Blue.
        break;
    case 3:
        plantColor = glm::vec3(1.0f, 1.0f, 0.0f);  // Yellow.
        break;
    case 4:
        plantColor = glm::vec3(1.0f, 0.0f, 1.0f);  // Purple.
        break;
    default:
        std::cout << "Invalid plant type!" << std::endl;
        break;
    }

    return plantColor;
}

inline int FindSelectedPlantType(std::vector<BasicSquare*> inventorySquares, int mouseX,
                                    int mouseY, int invetorySquareSide) {
    for (int i = 0; i < inventorySquares.size(); i++) {
        BasicSquare* inventorySquare = inventorySquares[i];
        glm::vec3 inventorySquarePosition = inventorySquare->GetPosition();
        glm::vec3 clickPosition = glm::vec3(mouseX, mouseY, 0);

        if (CheckClickInSquare(mouseX, mouseY, inventorySquarePosition.x,
                                inventorySquarePosition.y, invetorySquareSide)) {
            return i + 1; // +1 because the plant types start from 1.
        }
    }

    return -1; // click was outside the inventory.
}


inline bool CheckClickInSquare(float mouseX, float mouseY, float squareX,
                                float squareY, float squareSide) {
    float xMin = squareX;
    float xMax = squareX + squareSide;
    float yMin = squareY;
    float yMax = squareY + squareSide;

    return (mouseX >= xMin && mouseX <= xMax && mouseY >= yMin && mouseY <= yMax);
}

inline bool IsPointInsideRect(const glm::vec3& point, const glm::vec3& rectPosition,
                                float rectSize) {
    float halfSize = rectSize / 2.0f;
    float left = rectPosition.x - halfSize;
    float right = rectPosition.x + halfSize;
    float top = rectPosition.y - halfSize;
    float bottom = rectPosition.y + halfSize;

    return (point.x >= left && point.x <= right && point.y >= top && point.y <= bottom);
}

inline bool CheckCollision(glm::vec3 firstObjectPosition, glm::vec3 secondObjectPosition,
                            float radius1, float radius2) {
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

