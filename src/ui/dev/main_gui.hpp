#include "../../globals.hpp"
#include "../../player.hpp"
#include "../../controller.hpp"
#include "../../session.hpp"
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

class dgGame
{
public:
    dgScene scene;
    GameState gameState;
    Session *session;
    Controller controllers[MAX_KEYBOARDS + MAX_GAMEPADS];
    Controller keyboard;
};

class DevGui
{
public:
    RenderTexture renderTexture;

    void imguiInit(void *);
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
    int gsLen;
    unsigned char *gsBuffer;
    dgGame *game;

    void _displayPlayerInfo(int playerId);
    void _displayPlayerTweakers(int playerId);
    void _displayStateManipButtons();
    void _displayPlayerInputHistory(int playerId);
    void _displayAvailableControllers();
    void _displayPlayerController(int playerId);
    void _displayRecordingState();
    void _displayRenderWindow();

    void _saveGameState();
    void _loadGameState();
    void _toggleUpdate();
    void _stepUpdate(int allowance = 1);
    bool isRecording = false;
    bool isPlaying = false;
    PlayerInput p2Recording[60 * 60];
    int recordingSize = 0;
    int playbackCursorReverse = 0;
    void _toggleRecording();
    void _togglePlayback();
    void _startRecording();
    void _record();
    void _stopRecording();
    void _startPlayback();
    void _play();
    void _stopPlayback();
};
