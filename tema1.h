#pragma once

#include "components/simple_scene.h"
#include "assets/basic_objects.h"
#include "utils/transf2D.h"
#include "utils/game_asset_factory.h"
#include "engine/board_manager.h"
#include "engine/plant_manager.h"
#include "engine/zombie_manager.h"
#include "services/coin_spawn_service.h"
#include "services/drag_and_drop_service.h"

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void RenderSpawnedCoins();
        void RenderZombies(float deltaTimeSeconds);
        void RenderPlantSpells(float deltaTimeSeconds);
        void RenderDraggedPlant();
        void RenderDamageZone();
        void RenderPlantSites(float deltaTimeSeconds);
        void RenderInventory();
        void RenderLivesAndCollectedCoins();
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
    protected:
        float currentMouseX;
        float currentMouseY;
        glm::mat3 modelMatrix;
        BoardManager boardManager;
        PlantManager plantManager;
        ZombieManager zombieManager;
        CoinSpawnService coinSpawnService;
        DragAndDropService dragAndDropService;
    };
}

