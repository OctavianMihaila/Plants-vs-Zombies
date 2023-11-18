#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/tema1/tema1.h"

using namespace std;
using namespace m1;

Tema1::Tema1() : boardManager(NULL), plantManager(NULL), zombieManager(NULL) {}
Tema1::~Tema1() {}

void Tema1::Init() {
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    coinSpawnService = CoinSpawnService();
    dragAndDropService = DragAndDropService();
    GameAssetFactory& assetFactory = GameAssetFactory::GetInstance();
    boardManager = BoardManager(&assetFactory);
    plantManager = PlantManager(&boardManager);
    zombieManager = ZombieManager(&boardManager);

    boardManager.InitializePlantSites();
    boardManager.InitializeDamageZone();
    boardManager.InitializeLives();
    boardManager.InitializeInventory();
}

void Tema1::FrameStart() {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {
    glm::ivec2 resolution = window->GetResolution();
    modelMatrix = glm::mat3(1);

    if (boardManager.GetLives().empty()) {
        std::cout << "Game over!" << std::endl;
        exit(0);
    }

    RenderLivesAndCollectedCoins();
    RenderInventory();
    RenderPlantSites(deltaTimeSeconds);
    RenderDamageZone();
    RenderDraggedPlant();
    RenderPlantSpells(deltaTimeSeconds);
    RenderZombies(deltaTimeSeconds);
    RenderSpawnedCoins();

    coinSpawnService.HandleCoinSpawn(&boardManager, deltaTimeSeconds);
    zombieManager.HandleZombieSpawn(deltaTimeSeconds);
}

void Tema1::RenderSpawnedCoins() {
    std::vector<Coin*> spawnedCoins = boardManager.GetSpawnedCoins();

    if (!(spawnedCoins.empty())) {
        for (auto coin : spawnedCoins) {
            float x = coin->GetXTranslate();
            float y = coin->GetYTranslate();

            RenderMesh2D(coin->GetMesh(), shaders["VertexColor"], modelMatrix * transf2D::Translate(x, y) * transf2D::Rotate(0.95));
        }
    }
}

void Tema1::RenderZombies(float deltaTimeSeconds) {
    std::unordered_map<std::string, std::vector<Zombie*>> zombies = boardManager.GetZombies();

    for (auto const& x : zombies) {
        std::vector<Zombie*> zombies = x.second;
        std::string zombieHash = x.first;
        int line = zombieHash[0] - '0';
        int zombieType = zombieHash[1] - '0';

        for (Zombie* zombie : zombies) {
            glm::vec3 zombieCenter = zombie->GetPosition();

            RenderMesh2D(zombie->GetMesh(), shaders["VertexColor"], modelMatrix
                * transf2D::Translate(zombieCenter.x, zombieCenter.y)
                * transf2D::Scale(zombie->GetXScale(), zombie->GetYScale())
                * transf2D::Translate(-zombieCenter.x, -zombieCenter.y)
                * transf2D::Translate(-zombie->GetXTravelDistance(), 0)
            );

            zombieManager.UpdateZombie(zombie, zombieHash, deltaTimeSeconds);

        }
    }
}

void Tema1::RenderPlantSpells(float deltaTimeSeconds) {
    std::unordered_map<std::string, std::vector<PlantSpell*>> plantSpells = boardManager.GetPlantSpells();
    
    for (auto const& x : plantSpells) {
        std::vector<PlantSpell*> plantSpells = x.second;
        std::string spellHash = x.first;
        int plantType = spellHash[1] - '0';
        glm::vec3 plantColor = FindPlantColor(plantType);

        // Spells with a specific plant type and row.
        for (PlantSpell* plantSpell : plantSpells) {
            glm::vec3 plantSpellCenter = plantSpell->GetPosition();

            RenderMesh2D(plantSpell->GetMesh(), shaders["VertexColor"], modelMatrix
                * transf2D::Translate(plantSpellCenter.x + INVENTORY_SQUARE_SIDE / 2, plantSpellCenter.y + INVENTORY_SQUARE_SIDE / 2) // Translate to the center of the plant site.
                * transf2D::Rotate(plantSpell->GetRotationValue()) // Rotate the plant spell.
                * transf2D::Translate(-plantSpellCenter.x + plantSpell->GetXTravelDistance(), -plantSpellCenter.y)); // Translate back to the center of the plant spell.

            plantManager.PlantSpellPositionUpdate(plantSpell, deltaTimeSeconds, spellHash);
        }
    }
}

void Tema1::RenderDraggedPlant() {
    Plant* currentlyDraggedPlant = boardManager.GetCurrentlyDraggedPlant();

    if (currentlyDraggedPlant != NULL) {

        glm::vec3 plantPosition = currentlyDraggedPlant->GetPosition();
        float xTranslate = currentMouseX - plantPosition.x - DIAMOND_WIDTH / 2;
        float yTranslate = currentMouseY - plantPosition.y;

        RenderMesh2D(currentlyDraggedPlant->GetMesh(), shaders["VertexColor"], modelMatrix * transf2D::Translate(xTranslate, yTranslate));
    }
}

void Tema1::RenderDamageZone() {
    DamageZone* damageZone = boardManager.GetDamageZone();

    RenderMesh2D(damageZone->GetMesh(), shaders["VertexColor"], modelMatrix);
}

void Tema1::RenderPlantSites(float deltaTimeSeconds) {
    std::vector<PlantSite*> plantSites = boardManager.GetPlantSites();

    for (int i = 0; i < NR_PLANT_SITES; i++) {
        PlantSite* plantSite = plantSites[i];
        Plant* plant = plantSite->GetPlant();
        RenderMesh2D(plantSite->GetMesh(), shaders["VertexColor"], modelMatrix);


        if (!plantSite->IsEmpty()) {
            glm::vec3 plantSitePosition = plantSite->GetPosition();
            glm::vec3 plantPosition = plantSite->GetPlant()->GetPosition();
            // Placing the plant in the center of the plant site.
            float xTranslate = plantSitePosition.x - plantPosition.x + PLANT_SITE_SQUARE_SIDE / 4;
            float yTranslate = plantSitePosition.y - plantPosition.y + PLANT_SITE_SQUARE_SIDE / 2;

            plantManager.UpdatePlant(plantSite, plant, deltaTimeSeconds, i);

            RenderMesh2D(plant->GetMesh(), shaders["VertexColor"], modelMatrix
                * transf2D::Translate(xTranslate, yTranslate)
                * transf2D::Translate(plantPosition.x, plantPosition.y)
                * transf2D::Scale(plant->GetXScale(), plant->GetYScale())
                * transf2D::Translate(-plantPosition.x, -plantPosition.y));
        }
    }
}

void Tema1::RenderInventory() {
    std::vector<BasicSquare*> inventorySquares = boardManager.GetInventorySquares();
    std::vector<BasicStar*> inventoryStars = boardManager.GetInventoryStars();
    std::vector<Plant*> inventoryPlants = boardManager.GetInventoryPlants();

    for (int i = 0; i < NR_INVENTORY_SLOTS; i++) {
        RenderMesh2D(inventorySquares[i]->GetMesh(), shaders["VertexColor"], modelMatrix);
        RenderMesh2D(inventoryPlants[i]->GetMesh(), shaders["VertexColor"], modelMatrix);

        int nrStars = i + 1;
        if (i == 2 || i == 3) {
            nrStars--;
        }

        for (int j = 0; j < nrStars; j++) {
            float x = INVENTORY_STAR_LEFT_OFFSET + i * (INVENTORY_SQUARE_SIDE + INVENTORY_SQUARE_OFFSET) + j * (STAR_SIDE + STAR_OFFSET) - STAR_SYMMETRY_VALUE;
            float y = SCREEN_HEIGHT - SQUARE_SIDE - INVENTORY_STAR_TOP_OFFSET;
            RenderMesh2D(inventoryStars[i]->GetMesh(), shaders["VertexColor"], modelMatrix * transf2D::Translate(x, y) * transf2D::Rotate(0.95));
        }
    }
}

void Tema1::RenderLivesAndCollectedCoins() {
    float xLife = SCREEN_WIDTH - LIVES_RIGHT_OFFSET - LIVES_SQUARE_OFFSET;
    float yLife = SCREEN_HEIGHT - LIVES_TOP_OFFSET - LIVES_SQUARE_SIDE;
    float xStar = xLife - LIVES_SQUARE_SIDE - STAR_SIDE + STAR_SYMMETRY_VALUE;
    float yStar = yLife - LIVES_SQUARE_SIDE / 2;

    std::vector<BasicSquare*> lives = boardManager.GetLives();

    for (int i = 0; i < lives.size(); i++) {
        RenderMesh2D(lives[i]->GetMesh(), shaders["VertexColor"], modelMatrix);

        xStar -= (STAR_SIDE + STAR_OFFSET);
    }

    int nrCollectedCoins = boardManager.GetNrCollectedCoins();
    xStar = xLife - 3 * (LIVES_SQUARE_SIDE)+STAR_SYMMETRY_VALUE + STAR_SIDE;

    for (int i = 0; i < nrCollectedCoins; i++) {
        // Scale the star.
        std::vector<BasicStar*> collectedCoins = boardManager.GetCollectedCoins();
        RenderMesh2D(collectedCoins[i]->GetMesh(), shaders["VertexColor"], modelMatrix * transf2D::Translate(xStar, yStar) * transf2D::Rotate(0.95));

        xStar += STAR_OFFSET + STAR_SIDE;
    }
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    int windowHeight = window->GetResolution().y;

    currentMouseX = mouseX;
    currentMouseY = windowHeight - mouseY;
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    bool wasCoinClicked = false;
    int windowHeight = window->GetResolution().y;
    int mouseYInScene = windowHeight - mouseY;

    if (button == GLFW_MOUSE_BUTTON_RIGHT) { // This is left click, but in the framework it is called right click.
        coinSpawnService.HandleCoinCollection(&boardManager, mouseX, mouseYInScene, wasCoinClicked);
    }

    if (button == GLFW_MOUSE_BUTTON_3) { // This is right click, but in the framework it is called left click.
        dragAndDropService.HandlePlantDespawning(&boardManager, mouseX, mouseYInScene);
    }

    if (!wasCoinClicked && button != GLFW_MOUSE_BUTTON_3) {
        dragAndDropService.HandleInventoryPlantClick(&boardManager, mouseX, mouseYInScene);
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    int windowHeight = window->GetResolution().y;
    int mouseYInScene = windowHeight - mouseY;

    dragAndDropService.HandlePlantRelease(&boardManager, mouseX, mouseYInScene);
}
