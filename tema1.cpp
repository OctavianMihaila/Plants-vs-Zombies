#include <vector>
#include <string>
#include <iostream>

#include "lab_m1/tema1/tema1.h"


using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1() : boardManager(NULL){
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
    boardManager = BoardManager(&assetFactory);

    boardManager.InitializePlantSites(&meshes);
    boardManager.InitializeDamageZone(&meshes);
    boardManager.InitializeLives(&meshes);
    boardManager.InitializeInventory(&meshes);
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
    if (boardManager.GetLives().empty()) {
        // TODO: FREE RESOURCES !!!
		std::cout<<"Game over!"<<std::endl;
		exit(0);
	}

    glm::ivec2 resolution = window->GetResolution();
    modelMatrix = glm::mat3(1);
    float xLife = SCREEN_WIDTH - LIVES_RIGHT_OFFSET - LIVES_SQUARE_OFFSET;
    float yLife = SCREEN_HEIGHT - LIVES_TOP_OFFSET - LIVES_SQUARE_SIDE;
    float xStar = xLife - LIVES_SQUARE_SIDE - STAR_SIDE + STAR_SYMMETRY_VALUE;
    float yStar = yLife - LIVES_SQUARE_SIDE / 2;

    std::vector<BasicSquare*> lives = boardManager.GetLives();

    //std::cout<<lives.size()<<std::endl;

    for (int i = 0; i < lives.size(); i++) {
        RenderMesh2D(lives[i]->GetMesh(), shaders["VertexColor"], modelMatrix);

        xStar -= (STAR_SIDE + STAR_OFFSET);
    }

    int nrLifeStars = boardManager.GetNrLifeStars();
    xStar = xLife - 3 * (LIVES_SQUARE_SIDE) + STAR_SYMMETRY_VALUE + STAR_SIDE;

    for (int i = 0; i < nrLifeStars; i++) {
        // scale the star
        std::vector<BasicStar*> collectedCoins = boardManager.GetCollectedCoins();
        RenderMesh2D(collectedCoins[i]->GetMesh(), shaders["VertexColor"], modelMatrix * transf2D::Translate(xStar, yStar) * transf2D::Rotate(0.95));
	
        xStar += STAR_OFFSET + STAR_SIDE;
    }

    std::vector<BasicSquare*> inventorySquares = boardManager.GetInventorySquares();

    for (int i = 0; i < NR_INVENTORY_SLOTS; i++) {
        RenderMesh2D(inventorySquares[i]->GetMesh(), shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["inventoryPlant" + std::to_string(i)], shaders["VertexColor"], modelMatrix);

        int nrStars = i + 1;

        for (int j = 0; j < nrStars; j++) {
            float x = INVENTORY_STAR_LEFT_OFFSET + i * (INVENTORY_SQUARE_SIDE + INVENTORY_SQUARE_OFFSET) + j * (STAR_SIDE + STAR_OFFSET) - STAR_SYMMETRY_VALUE;
            float y = SCREEN_HEIGHT - SQUARE_SIDE - INVENTORY_STAR_TOP_OFFSET;
            RenderMesh2D(meshes["inventoryStar" + std::to_string(i) + std::to_string(j)], shaders["VertexColor"], modelMatrix * transf2D::Translate(x, y) * transf2D::Rotate(0.95));
        }
	}

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

            if (plantSite->IsPlantReadyToBeRemoved()) {
                float xScale = plant->GetXScale();
                float yScale = plant->GetYScale();
                float newXScale = xScale - deltaTimeSeconds * ANIMATION_SPEED_RATE;
                float newYScale = yScale - deltaTimeSeconds * ANIMATION_SPEED_RATE;

                plant->SetXScale(newXScale);
                plant->SetYScale(newYScale);

                // Ensure the scale doesn't go below zero.
                if (newXScale < 0.0f || newYScale < 0.0f) {
                    plantSite->SetPlant(NULL);
                    plantSite->SetPlantReadyToBeRemoved(false);
                }
            } else {
                int line = i / 3 + 1;
                int type = plant->GetPlantType();
                std::string spellHash = std::to_string(line) + std::to_string(type);
                std::vector<Zombie*> zombies = boardManager.GetZombies()[spellHash];

                if (CheckZombieTypeInVector(type, zombies) && plant->GetLaunchCooldown() < 0.0f) {
                    int line = i / 3 + 1;
                    glm::vec3 launchPosition = plantSite->GetPosition();

                    launchPosition.z = 1.0f;
                    boardManager.LaunchSpell(line, plant->GetPlantType(), launchPosition);
                    plant->ResetLaunchCooldown();
				}
                else {
					plant->DecrementLaunchCooldown(deltaTimeSeconds);
				}
            }

            RenderMesh2D(plant->GetMesh(), shaders["VertexColor"], modelMatrix
                * transf2D::Translate(xTranslate, yTranslate)
                * transf2D::Translate(plantPosition.x, plantPosition.y)
                * transf2D::Scale(plant->GetXScale(), plant->GetYScale())
                * transf2D::Translate(-plantPosition.x, -plantPosition.y));
		}
    }

    RenderMesh2D(meshes["damageZone"], shaders["VertexColor"], modelMatrix);

    // Render the dragged plant.
    Plant* currentlyDraggedPlant = boardManager.GetCurrentlyDraggedPlant();
    if (currentlyDraggedPlant != NULL) {

        glm::vec3 plantPosition = currentlyDraggedPlant->GetPosition();
        float xTranslate = currentMouseX - plantPosition.x - DIAMOND_WIDTH / 2;
        float yTranslate = currentMouseY - plantPosition.y;

        RenderMesh2D(currentlyDraggedPlant->GetMesh(), shaders["VertexColor"], modelMatrix * transf2D::Translate(xTranslate, yTranslate));
	}

    // ############################################# STARS AND HEXAGONS #############################################

    std::unordered_map<std::string, std::vector<PlantSpell*>> plantSpells = boardManager.GetPlantSpells();

    // Render the plant spells.
    for (auto const& x : plantSpells) {
		std::vector<PlantSpell*> plantSpells = x.second;
        std::string spellHash = x.first;
        int plantType = spellHash[1] - '0';
        glm::vec3 plantColor = FindPlantColor(plantType);

        // spells with a specific plant type and row.
        for (PlantSpell* plantSpell : plantSpells) {
			glm::vec3 plantSpellCenter = plantSpell->GetPosition();


            RenderMesh2D(plantSpell->GetMesh(), shaders["VertexColor"], modelMatrix
                * transf2D::Translate(plantSpellCenter.x + INVENTORY_SQUARE_SIDE / 2, plantSpellCenter.y + INVENTORY_SQUARE_SIDE / 2) // translate to the center of the plant site.
                * transf2D::Rotate(plantSpell->GetRotationValue()) // rotate the plant spell.
                * transf2D::Translate(-plantSpellCenter.x + plantSpell->GetXTravelDistance(), -plantSpellCenter.y)); // translate back to the center of the plant spell.

            float oldXTravelDistance = plantSpell->GetXTravelDistance();
            float newXTravelDistance = oldXTravelDistance + deltaTimeSeconds * SPELL_MOVE_SPEED_RATE;
            plantSpell->IncreaseXTravelDistance(deltaTimeSeconds * SPELL_MOVE_SPEED_RATE);
            plantSpell->UpdatePosition(oldXTravelDistance, newXTravelDistance);

            if (plantSpell->GetPosition().x > SCREEN_WIDTH) {
                std::cout<<"Plant spell center x: "<<plantSpellCenter.x<<std::endl;
                std::cout<<"Spell reached the end of the screen!"<<std::endl;
				boardManager.RemovePlantSpell(plantSpell, spellHash);
			}

            plantSpell->IncreaseRotationValue(deltaTimeSeconds * ROTATION_SPEED_RATE);

            if (plantSpell->GetRotationValue() > 360.0f) {
				plantSpell->ResetRotationValue();
            }
		}
	}

    // render the zombies.
    std::unordered_map<std::string, std::vector<Zombie*>> zombies = boardManager.GetZombies();

    for (auto const& x : zombies) {
        std::vector<Zombie*> zombies = x.second;
        std::string zombieHash = x.first;
        int line = zombieHash[0] - '0';
        int zombieType = zombieHash[1] - '0';
        int i = 0;
        for (Zombie* zombie : zombies) {
			glm::vec3 zombieCenter = zombie->GetPosition();
            i++;
            while (1) {
                //std::cout << "Zombie center " << i << " : " << zombieCenter.x << std::endl;
                // sleep 1 second
                //_sleep(100);
                break;
            }

            RenderMesh2D(zombie->GetMesh(), shaders["VertexColor"], modelMatrix
                * transf2D::Translate(zombieCenter.x, zombieCenter.y)
                * transf2D::Scale(zombie->GetXScale(), zombie->GetYScale())
                * transf2D::Translate(-zombieCenter.x, -zombieCenter.y)
                * transf2D::Translate(-zombie->GetXTravelDistance(), 0)
            );

            if (zombie->IsReadyToBeRemoved()) {
                float xScale = zombie->GetXScale();
                float yScale = zombie->GetYScale();
                float newXScale = xScale - deltaTimeSeconds * ANIMATION_SPEED_RATE;
                float newYScale = yScale - deltaTimeSeconds * ANIMATION_SPEED_RATE;

                zombie->SetXScale(newXScale);
                zombie->SetYScale(newYScale);

                // Ensure the scale doesn't go below zero.
                if (newXScale < 0.0f || newYScale < 0.0f) {
                    boardManager.RemoveZombie(zombie, zombieHash);
                    zombie->SetReadyToBeRemoved(false);
                }
            }

            // TODO: MAYBE MAKE A FUNCTION OUT OF THAT, BECAUSE IT IS USED IN THE PLANT SPELLS TOO.
            float oldXTravelDistance = zombie->GetXTravelDistance();
            float newXTravelDistance = oldXTravelDistance + deltaTimeSeconds * ZOMBIE_MOVE_SPEED_RATE;
            zombie->IncreaseXTravelDistance(deltaTimeSeconds * ZOMBIE_MOVE_SPEED_RATE);
            //std::cout<<"zombie poz: "<< zombie->GetPosition()<<std::endl; // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@
            zombie->UpdatePosition(oldXTravelDistance, newXTravelDistance);

            if (zombie->GetXTravelDistance() > SCREEN_WIDTH - DAMAGE_ZONE_LEFT_OFFSET - DAMAGE_ZONE_LENGTH) {
                boardManager.RemoveLife();
                boardManager.RemoveZombie(zombie, zombieHash);

                break;
            }

            int count = 0;
            // If zombie is one one of the plantSites and that plantSite has a plant on it, then the plant should be removed.
            for (PlantSite* plantSite : plantSites) {

                if (!plantSite->IsEmpty()) {
                    float plantSiteRightOffset = SCREEN_WIDTH - PLANT_SITE_SQUARE_LEFT_OFFSET - (count % 3) * (PLANT_SITE_SQUARE_SIDE + PLANT_SITE_SQUARE_OFFSET) - PLANT_SITE_SQUARE_SIDE;
                    if (line == ((count / 3) + 1) && zombie->GetXTravelDistance() > plantSiteRightOffset && zombie->GetXTravelDistance() < plantSiteRightOffset + PLANT_SITE_SQUARE_SIDE) {
                        std::cout << "LINE: " << line << std::endl;
                        std::cout << "COUT: " << count << std::endl;
                         plantSite->SetPlantReadyToBeRemoved(true);
                    }
                }

                count++;
            }

            // zombie and plantSpell collision handling.
            std::unordered_map<std::string, std::vector<PlantSpell*>> plantSpells = boardManager.GetPlantSpells();

            for (auto const& x : plantSpells) {
				std::vector<PlantSpell*> plantSpells = x.second;
				std::string spellHash = x.first;
				int plantType = spellHash[1] - '0';
				glm::vec3 plantColor = FindPlantColor(plantType);
                int i = 0;
				// spells with a specific plant type and row.
                for (PlantSpell* plantSpell : plantSpells) {
                    i++;
                    //std::cout << "Plant spell: " << i << " center: " << plantSpell->GetPosition().x << std::endl;
					glm::vec3 plantSpellCenter = plantSpell->GetPosition();
                    glm::vec3 zombieCenter = zombie->GetPosition();
                    float plantRadius = plantSpell->GetRadius();
                    float zombieRadius = zombie->GetRadius();

                   if (CheckCollision(plantSpellCenter, zombieCenter, plantRadius, zombieRadius) && spellHash == zombieHash) {
						    boardManager.RemovePlantSpell(plantSpell, spellHash);
                            if (zombie->GetTotalDamageTaken() == 2 && !zombie->IsReadyToBeRemoved()) {
                                //boardManager.RemoveZombie(zombie, zombieHash);
                                zombie->AjustPosition(zombie->GetRadius(), zombie->GetRadius());
                                zombie->SetReadyToBeRemoved(true);
                            } else {
								zombie->TakeDamage(1);
                            }
						    break;
				    }
				    
				}
			}

       /*    if (zombie->GetTotalDamageTaken() >= 3) {
				boardManager.RemoveZombie(zombie, zombieHash);
				break;
			}*/

        }
    }

    // ############################################# STARS AND HEXAGONS #############################################

    std::vector<Coin*> spawnedCoins = boardManager.GetSpawnedCoins();

    if (!(spawnedCoins.empty())) {
        for (auto coin : spawnedCoins) {
            float x = coin->GetXTranslate();
            float y = coin->GetYTranslate();

			RenderMesh2D(coin->GetMesh(), shaders["VertexColor"], modelMatrix * transf2D::Translate(x, y) * transf2D::Rotate(0.95));
		}
    }

    if (Coin::IsTimeToSpawn()) {
		boardManager.InitializeThreeCoins(&meshes);
		Coin::UpdateSpawnTime();
	}
    else {
		Coin::IncreaseWithDeltaTime(deltaTimeSeconds);
	}

    if (Zombie::IsTimeToSpawn()) {
        boardManager.LaunchZombie();
        Zombie::UpdateSpawnTime();
    }
    else {
        Zombie::IncreaseWithDeltaTime(deltaTimeSeconds);
    }
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

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    int windowHeight = window->GetResolution().y;

    //std::cout<<"MouseX: "<<mouseX<<" MouseY: "<<windowHeight - mouseY<<std::endl;

    currentMouseX = mouseX;
    currentMouseY = windowHeight - mouseY;
}

// TODO: MOVE THIS ONE FROM THERE (maybe in utils).
bool Tema1::IsPointInsideRect(const glm::vec3& point, const glm::vec3& rectPosition, float rectSize)
{
    float halfSize = rectSize / 2.0f;
    float left = rectPosition.x - halfSize;
    float right = rectPosition.x + halfSize;
    float top = rectPosition.y - halfSize;
    float bottom = rectPosition.y + halfSize;

    return (point.x >= left && point.x <= right && point.y >= top && point.y <= bottom);
}

int Tema1::FindSelectedPlantType(std::vector<BasicSquare*> inventorySquares, int mouseX, int mouseY) {

    for (int i = 0; i < NR_INVENTORY_SLOTS; i++) {
        BasicSquare* inventorySquare = inventorySquares[i];
        glm::vec3 inventorySquarePosition = inventorySquare->GetPosition();
        glm::vec3 clickPosition = glm::vec3(mouseX, mouseY, 0);

        if (CheckClickInSquare(mouseX, mouseY, inventorySquarePosition.x, inventorySquarePosition.y, INVENTORY_SQUARE_SIDE)) {
            return i + 1; // +1 because the plant types start from 1.
        }
    }

    return -1; // click was outside the inventory.
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    bool wasCoinClicked = false;
    int windowHeight = window->GetResolution().y;
    int mouseYInScene = windowHeight - mouseY;

    if (button == GLFW_MOUSE_BUTTON_RIGHT) { // this is left click, but in the framework it is called right click.
        std::vector<Coin*> spawnedCoins_ = boardManager.GetSpawnedCoins();

        for (Coin* coin : spawnedCoins_) {
            glm::vec3 coinPosition = glm::vec3(coin->GetXTranslate(), coin->GetYTranslate(), 0);

            // Define an imaginary rectangle around the coin
            glm::vec3 rectPosition = coinPosition;
            float rectSize = STAR_SIDE * 2;

            // Check if the mouse click is inside the imaginary rectangle around the star
            if (IsPointInsideRect(glm::vec3(mouseX, mouseYInScene, 0), rectPosition, rectSize)){
                int starIndex = boardManager.GetNrLifeStars();
                glm::vec3 starCenter = glm::vec3(0, 0, 0);
                glm::vec3 starColor = glm::vec3(0.5f, 0.5f, 0.5f); // 
                BasicStar *basicStar = boardManager.GetAssetFactory()->CreateBasicStar("lifeStar" + std::to_string(starIndex), starCenter, STAR_SIDE, starColor);

                boardManager.AddCollectedCoin(basicStar);
                boardManager.RemoveSpawnedCoin(coin);

                wasCoinClicked = true;
                break;
            }
        }
    }

    if (button == GLFW_MOUSE_BUTTON_3) { // this is right click, but in the framework it is called left click.
        // handle plant despawning
        std::vector<PlantSite*> plantSites = boardManager.GetPlantSites();

        for (PlantSite* plantSite : plantSites) {
			glm::vec3 plantSitePosition = plantSite->GetPosition();
			glm::vec3 clickPosition = glm::vec3(mouseX, mouseYInScene, 0);

			if (CheckClickInSquare(mouseX, mouseYInScene, plantSitePosition.x, plantSitePosition.y, PLANT_SITE_SQUARE_SIDE)) {
                if (!plantSite->IsEmpty()) {
                    //plantSite->SetPlant(NULL); // remove the plant from the plant site.
                    plantSite->SetPlantReadyToBeRemoved(true);
					break;
				}
			}
		}
    }

    if (!wasCoinClicked && button != GLFW_MOUSE_BUTTON_3) {
   	    int selectedPlantType = FindSelectedPlantType(boardManager.GetInventorySquares(), mouseX, mouseYInScene);

        if (selectedPlantType != -1) {
            int cost = CalculatePlantCost(selectedPlantType);
            glm::vec3 plantColor = FindPlantColor(selectedPlantType);

            Plant* draggedPlant = boardManager.GetAssetFactory()->CreatePlant("draggedPlant", glm::vec3(mouseX + DIAMOND_WIDTH / 2, mouseYInScene, 1), DIAMOND_WIDTH, DIAMOND_HEIGHT, plantColor, selectedPlantType, cost);
            boardManager.setCurrentlyDraggedPlant(draggedPlant);
        }
    }
}




void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    Plant* currentlyDraggedPlant = boardManager.GetCurrentlyDraggedPlant();
    int windowHeight = window->GetResolution().y;
    int mouseYInScene = windowHeight - mouseY;

    // check if the mouse was released on a plant site. If not then the plant should be removed. Otherwise, the plant should be placed on the plant site. Also set the currentDraggedPlant to NULL.
    if (currentlyDraggedPlant != NULL) {
		std::vector<PlantSite*> plantSites = boardManager.GetPlantSites();

        for (PlantSite* plantSite : plantSites) {
			glm::vec3 plantSitePosition = plantSite->GetPosition();
			glm::vec3 clickPosition = glm::vec3(mouseX, mouseYInScene, 0);

			if (CheckClickInSquare(mouseX, mouseYInScene, plantSitePosition.x, plantSitePosition.y, PLANT_SITE_SQUARE_SIDE)) {
                int cost = currentlyDraggedPlant->GetCost();
                int nrCoins = boardManager.GetCollectedCoins().size();
                // place the plant on the plant site.
                if (plantSite->IsEmpty() && cost <= nrCoins) {
                    plantSite->SetPlant(currentlyDraggedPlant);
                    boardManager.RemoveCollectedCoins(cost);
                    break;
				}
                
            }
            
        }

        boardManager.setCurrentlyDraggedPlant(NULL);
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
