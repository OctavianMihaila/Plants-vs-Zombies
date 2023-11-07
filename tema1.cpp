#include "lab_m1/lab4/lab4.h"

#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/tema1/tema1.h"
#include "lab_m1/tema1/assets/basic_objects.h"
#include "lab_m1/tema1/utils/transf2D.h"
#include "lab_m1/tema1/utils/game_asset_factory.h"
#include "lab_m1/tema1/engine/board_manager.h"

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    GameAssetFactory& assetFactory = GameAssetFactory::GetInstance();
    BoardManager boardManager = BoardManager(&assetFactory);

    boardManager.InitializePlantSites(&meshes);
    boardManager.InitializeDamageZone(&meshes);
    boardManager.InitializeLives(&meshes);
    boardManager.InitializeInventory(&meshes);

    //Mesh* square1 = basic_objects::CreateRectangle("square1", squareCorner, squareSide, squareSide, glm::vec3(1, 0, 0));
    //AddMeshToList(square1);

    //Mesh* rectangle1 = basic_objects::CreateRectangle("rectangle1", rectangleCorner, rectangleSide, rectangleSide / 2, glm::vec3(0, 1, 0));
    //AddMeshToList(rectangle1);

    //Mesh* star1 = basic_objects::CreateStar("star1", glm::vec3(0, 0, 0), 50, glm::vec3(0, 0, 1));
    //AddMeshToList(star1);
   
    //Mesh* diamond1 = basic_objects::CreateDiamond("diamond1", glm::vec3(400, 400, 0), 50, 100, glm::vec3(1, 1, 0));
    //AddMeshToList(diamond1);

    //Mesh* hexagon1 = basic_objects::CreateMergedHexagons("hexagon1", glm::vec3(500, 500, 0), 50, glm::vec3(1, 0, 1), glm::vec3(0, 1, 0));
    ////Mesh* hexagon1 = basic_objects::CreateDoubleHexagon("hexagon1", glm::vec3(500, 500, 0), 50, glm::vec3(1, 0, 1));
    //AddMeshToList(hexagon1);
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::RenderScene() {

}

void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    modelMatrix = glm::mat3(1);
    float xLife = SCREEN_WIDTH - LIVES_RIGHT_OFFSET - LIVES_SQUARE_OFFSET;
    float yLife = SCREEN_HEIGHT - LIVES_TOP_OFFSET - LIVES_SQUARE_SIDE;
    float xStar = xLife - LIVES_SQUARE_SIDE - LIVES_SQUARE_OFFSET + STAR_SYMMETRY_VALUE;
    float yStar = yLife - LIVES_SQUARE_SIDE / 2;

    for (int i = 0; i < NR_LIVES; i++) {
        RenderMesh2D(meshes["life" + std::to_string(i)], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["lifeStar" + std::to_string(i)], shaders["VertexColor"], modelMatrix * transf2D::Translate(xStar, yStar) * transf2D::Rotate(0.95));

        xStar -= (STAR_SIDE + STAR_OFFSET);
    }

    for (int i = 0; i < NR_INVENTORY_SLOTS; i++) {
		RenderMesh2D(meshes["inventorySquare" + std::to_string(i)], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["inventoryPlant" + std::to_string(i)], shaders["VertexColor"], modelMatrix);

        int nrStars = i + 1;

        for (int j = 0; j < nrStars; j++) {
            float x = INVENTORY_STAR_LEFT_OFFSET + i * (INVENTORY_SQUARE_SIDE + INVENTORY_SQUARE_OFFSET) + j * (STAR_SIDE + STAR_OFFSET) - STAR_SYMMETRY_VALUE;
            float y = SCREEN_HEIGHT - SQUARE_SIDE - INVENTORY_STAR_TOP_OFFSET;
            RenderMesh2D(meshes["inventoryStar" + std::to_string(i) + std::to_string(j)], shaders["VertexColor"], modelMatrix * transf2D::Translate(x, y) * transf2D::Rotate(0.95));
        }
	}

    for (int i = 0; i < NR_PLANT_SITES; i++) {
        RenderMesh2D(meshes["plantSite" + std::to_string(i)], shaders["VertexColor"], modelMatrix);
    }

    RenderMesh2D(meshes["damageZone"], shaders["VertexColor"], modelMatrix);

    //modelMatrix = glm::mat4(1); // Identity matrix (no transformations)
    //RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    //// draw a rectangle (no transformations)
    //modelMatrix = glm::mat3(1);
    //RenderMesh2D(meshes["rectangle1"], shaders["VertexColor"], modelMatrix);

    //// draw a star (no transormations)

    //modelMatrix = glm::mat3(1);
    // I want the star to be in the same position after rotation (i mean its center).
    //modelMatrix = glm::mat3(1);
    //RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix * transf2D::Translate(500, 500) * transf2D::Rotate(0.95));

    //modelMatrix = glm::mat3(1);
    //RenderMesh2D(meshes["diamond1"], shaders["VertexColor"], modelMatrix);

    //modelMatrix = glm::mat3(1);
    //RenderMesh2D(meshes["hexagon1"], shaders["VertexColor"], modelMatrix);
}


void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
