#include "basic_objects.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

Mesh* basic_objects::CreateRectangle(const std::string& name, glm::vec3 leftBottomCorner,
                                    float length, float width, glm::vec3 color, bool fill)
{
    Mesh* rectangle = new Mesh(name);
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, width, 0), color),
        VertexFormat(corner + glm::vec3(0, width, 0), color)
    };

    std::vector<unsigned int> indices;

    if (fill)
    {
        indices = { 0, 1, 2, 3, 0, 2};
        rectangle->SetDrawMode(GL_TRIANGLES);
        rectangle->InitFromData(vertices, indices);
    }
    else
    {
        indices = { 0, 1, 1, 2, 2, 3, 3, 0 };
        rectangle->SetDrawMode(GL_LINES);
        rectangle->InitFromData(vertices, indices);
    }

    return rectangle;
}


Mesh* basic_objects::CreateStar(const std::string& name, glm::vec3 center,
                                float length, glm::vec3 color)
{
    Mesh* star = new Mesh(name);
    float innerRadius = length / 3.0f;
    glm::vec3 corner = center;

    // Define the vertices for the star.
    std::vector<VertexFormat> vertices;
    for (int i = 0; i < 5; i++) {
        float outerAngle = glm::radians(72.0f * i);
        float innerAngle = glm::radians(72.0f * i + 36.0f);

        // Add the outer point.
        vertices.push_back(VertexFormat(
            corner + glm::vec3(length * glm::cos(outerAngle),
                                length * glm::sin(outerAngle), 0),
            color
        ));

        // Add the inner point.
        vertices.push_back(VertexFormat(
            corner + glm::vec3(innerRadius * glm::cos(innerAngle),
                                innerRadius * glm::sin(innerAngle), 0),
            color
        ));
    }

    // Create indices to form the filled star.
    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < 10; i += 2) {
        indices.push_back(i + 1);
        indices.push_back((i + 2) % 10);
        indices.push_back((i + 3) % 10);

        // Fill the middle of the star (pentaghon).
        indices.push_back(i + 1);
        indices.push_back((i + 3) % 10);
        indices.push_back((i + 5) % 10);


        // Fill the middle of the star (pentaghon).
        indices.push_back(i + 1);
        indices.push_back((i + 5) % 10);
        indices.push_back((i + 7) % 10);
    }

    star->SetDrawMode(GL_TRIANGLES);
    star->InitFromData(vertices, indices);

    return star;
}

Mesh* basic_objects::CreateDiamond(const std::string& name, glm::vec3 center,
                                    float width, float height, glm::vec3 color)
{
    float halfWidth = width / 2;
    float halfHeight = height / 2;
    Mesh* diamond = new Mesh(name);
    glm::vec3 corner = center;

    std::vector<VertexFormat> vertices =
    {
        // Drawing the diamond.
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(halfWidth, halfHeight, 0), color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(halfWidth, -halfHeight, 0), color),

        // Drawing the rectangle
        VertexFormat(corner + glm::vec3(halfWidth, halfHeight / 4, 0), color),
        VertexFormat(corner + glm::vec3(width * 1.5f, halfHeight / 4, 0), color),
        VertexFormat(corner + glm::vec3(width * 1.5f, -halfHeight / 4, 0), color),
        VertexFormat(corner + glm::vec3(halfWidth, -halfHeight / 4, 0), color)

    };

    // Indices for the rectangle and the diamond.
    std::vector<unsigned int> indices = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };

    diamond->SetDrawMode(GL_TRIANGLES);
    diamond->InitFromData(vertices, indices);

    return diamond;
}

Mesh* basic_objects::CreateMergedHexagons(const std::string& name, glm::vec3 center, float length,
                                            glm::vec3 firstHexagonColor, glm::vec3 secondHexagonColor)
{
    float scale_factor = 0.75f;
    Mesh* hexagon = new Mesh(name);
    glm::vec3 corner = center;
    glm::vec3 translation = glm::vec3(0.5f * (1 - scale_factor) * length,
                                        (1 - scale_factor) * length * glm::sqrt(3) / 2, 0);

    std::vector<VertexFormat> vertices =
    {
        // Drawing first hexagon.
        VertexFormat(corner, firstHexagonColor),
        VertexFormat(corner + glm::vec3(length, 0, 0), firstHexagonColor),
        VertexFormat(corner + glm::vec3(length * 1.5f, length * glm::sqrt(3) / 2, 0), firstHexagonColor),
        VertexFormat(corner + glm::vec3(length, length * glm::sqrt(3), 0), firstHexagonColor),
        VertexFormat(corner + glm::vec3(0, length * glm::sqrt(3), 0), firstHexagonColor),
        VertexFormat(corner + glm::vec3(-length / 2, length * glm::sqrt(3) / 2, 0), firstHexagonColor),

        // Drawing second hexagon.
        VertexFormat(corner + translation, secondHexagonColor),
        VertexFormat(corner + glm::vec3(length * scale_factor + translation.x,
                                        translation.y, 0),
                                        secondHexagonColor),
        VertexFormat(corner + glm::vec3(length * 1.5f * scale_factor + translation.x,
                                        length * glm::sqrt(3) / 2 * scale_factor + translation.y, 0),
                                        secondHexagonColor),
        VertexFormat(corner + glm::vec3(length * scale_factor + translation.x,
                                        length * glm::sqrt(3) * scale_factor + translation.y, 0),
                                        secondHexagonColor),
        VertexFormat(corner + glm::vec3(translation.x,
                                        length * glm::sqrt(3) * scale_factor + translation.y, 0),
                                        secondHexagonColor),
        VertexFormat(corner + glm::vec3(-length / 2 * scale_factor + translation.x,
                                        length * glm::sqrt(3) / 2 * scale_factor + translation.y, 0.1f),
                                        secondHexagonColor)
    };

    std::vector<unsigned int> indices = {
        0, 1, 5, 1, 2, 5, 2, 3, 5, 3, 4, 5,  // First hexagon.
        6, 7, 11, 7, 8, 11, 8, 9, 11, 9, 10, 11  // Second hexagon.
    };

    hexagon->SetDrawMode(GL_TRIANGLES);
    hexagon->InitFromData(vertices, indices);

    return hexagon;
}


