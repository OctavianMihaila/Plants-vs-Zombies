#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema1/assets/basic_objects.h"
#include "lab_m1/tema1/utils/transf2D.h"
#include "lab_m1/tema1/utils/game_asset_factory.h"
#include "lab_m1/tema1/engine/board_manager.h"

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
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        // TODO: MOVE THIS ONE FROM THERE
        bool IsPointInsideRect(const glm::vec3& point, const glm::vec3& rectPosition, float rectSize);
        int FindSelectedPlantType(std::vector<BasicSquare*> inventorySquares, int mouseX, int mouseY);

        void RenderScene();
    protected:
        glm::mat3 modelMatrix;
        BoardManager boardManager;
        float currentMouseX;
        float currentMouseY;
        
    };
}   // namespace m1

