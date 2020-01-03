#include "../../globals.hpp"
#include "../../player.hpp"
#include "../../deps/imgui/imgui.h"
#include "../../deps/imgui/imgui_impl_glfw.h"
#include "../../deps/imgui/imgui_impl_opengl3.h"

struct dgScene
{
    int targetFPS;
    int stageHalfWidth = 700;
    // Camera3D cam;
    // PlayerController players[2];
    // Button _makeGameStateBufferBtn;
    // Button _loadGameStateBtn;
    // Button _toggleUpdateBtn;
    // Button _stepOneBtn;
};

class DevGui
{
public:
    RenderTexture renderTexture;

    void imguiInit(dgScene *scene, GameState *gs);
    void imguiUpdate();
    void begin();
    void end();
    void imguiShutdown();
    static void _SixteenNineAspectRatio(ImGuiSizeCallbackData *data)
    {
        data->DesiredSize = ImVec2(data->DesiredSize.x, data->DesiredSize.x * (9.f / 16.f));
    };

private:
    dgScene *scene;
    GameState *gameState;

    void _displayPlayerInfo(int playerId);
    void _displayRenderWindow();
};
