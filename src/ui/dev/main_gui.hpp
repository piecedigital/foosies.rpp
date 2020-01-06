#include "../../globals.hpp"
#include "../../player.hpp"
#include "../../deps/imgui/imgui.h"
#include "../../deps/imgui/imgui_impl_glfw.h"
#include "../../deps/imgui/imgui_impl_opengl3.h"

struct dgScene
{
    int targetFPS;
    int stageHalfWidth = 700;
    int stepAllowance = 0;
    bool willStep = true;
    Camera3D cam;
    PlayerController players[2];
};

class DevGui
{
public:
    RenderTexture renderTexture;

    void imguiInit(dgScene *scene, GameState *gs);
    void imguiUpdate();
    void beginRenderTexture();
    void endRenderTexture();
    void imguiShutdown();
    bool renderWindowIsFocused;

    static void _SixteenNineAspectRatio(ImGuiSizeCallbackData *data)
    {
        data->DesiredSize = ImVec2(data->DesiredSize.x, data->DesiredSize.x * (9.f / 16.f));
    };

private:
    dgScene *scene;
    GameState *gameState;
    int gsLen;
    unsigned char *gsBuffer;

    void _displayPlayerInfo(int playerId);
    void _displayStateManipButtons();
    void _displayPlayerInputHistory(int playerId);
    void _displayRenderWindow();

    void _saveGameState();
    void _loadGameState();
    void _toggleUpdate();
    void _stepUpdate(int allowance = 1);
};
