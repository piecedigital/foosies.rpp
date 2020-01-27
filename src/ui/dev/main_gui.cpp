#include "main_gui.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include "../../deps/raylib/raylib.h"

ImVec4 xGREEN = {(float)GREEN.r / 255 - 0.1, (float)GREEN.g / 255 - 0.1, (float)GREEN.b / 255 - 0.1, (float)GREEN.a / 255};
ImVec4 xGREENHover = {(float)GREEN.r / 255, (float)GREEN.g / 255, (float)GREEN.b / 255, (float)GREEN.a / 255};
ImVec4 xRED = {(float)RED.r / 255 - 0.1, (float)RED.g / 255 - 0.1, (float)RED.b / 255 - 0.1, (float)RED.a / 255};
ImVec4 xREDHover = {(float)RED.r / 255, (float)RED.g / 255, (float)RED.b / 255, (float)RED.a / 255};
ImVec4 xBLACK = {(float)BLACK.r / 255, (float)BLACK.g / 255, (float)BLACK.b / 255, (float)BLACK.a / 255};
ImVec4 xWHITE = {(float)WHITE.r / 255, (float)WHITE.g / 255, (float)WHITE.b / 255, (float)WHITE.a / 255};

void DevGui::imguiInit(void *g)
{
    game = (dgGame *)g;

    _saveGameState();

    renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    GLFWwindow *window = (GLFWwindow *)GetWindow();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(/*glsl_version*/);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void DevGui::imguiUpdate()
{
    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::AlignTextToFramePadding();

    // render your GUI
    _displayPlayerInfo(0);
    _displayPlayerInfo(1);
    _displayPlayerTweakers(0);
    _displayPlayerTweakers(1);
    _displayPlayerInputHistory(0);
    _displayPlayerInputHistory(1);
    _displayStateManipButtons();
    if (isRecording)
    {
        _record();
    }
    else if (isPlaying)
    {
        _play();
    }
    _displayAvailableControllers();
    _displayPlayerController(0);
    _displayPlayerController(1);
    _displayRecordingState();
    _displayRenderWindow();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DevGui::beginRenderTexture()
{
    BeginTextureMode(renderTexture);
}

void DevGui::endRenderTexture()
{
    EndTextureMode();
}

void DevGui::imguiShutdown()
{
    UnloadTexture(renderTexture.texture);
    UnloadRenderTexture(renderTexture);

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void DevGui::_displayPlayerInfo(int playerId)
{
    ImGui::Begin(std::string("Player ").append(std::to_string(playerId)).append(" info").c_str());

    ImGui::Text("Controller: %i", game->scene.players[playerId].controllerId);
    ImGui::Text("Action Face: %i", game->gameState.playerData[playerId].actionFace);
    ImGui::Text("Side Face: %i", game->gameState.playerData[playerId].sideFace);
    ImGui::Text("Physical:");
    ImGui::Text("       X: %i", game->gameState.playerData[playerId].physical.x);
    ImGui::Text("       Y: %i", game->gameState.playerData[playerId].physical.y);
    ImGui::Text("  HSpeed: %i", game->gameState.playerData[playerId].physical.HSpeed);
    ImGui::Text("  VSpeed: %i", game->gameState.playerData[playerId].physical.VSpeed);
    char buf[254] = "";
    ImGui::InputText("Test", buf, 254);

    ImGui::End();
}

void DevGui::_displayPlayerTweakers(int playerId)
{
    ImGui::Begin(std::string("Player ").append(std::to_string(playerId)).append(" Tweaker").c_str());

    ImGui::SliderInt("Body Width", &game->scene.players[playerId].charMan[0].model->bodyWidth, 100, 200);
    ImGui::SliderInt("Body Height", &game->scene.players[playerId].charMan[0].model->bodyHeight, 100, 400);
    // ImGui::SliderFloat("Light X", &game->scene.players[playerId].charMan[0].model->lightPos[0], -10.f, 10.f);
    // ImGui::SliderFloat("Light Y", &game->scene.players[playerId].charMan[0].model->lightPos[1], -10.f, 10.f);
    // ImGui::SliderFloat("Light Z", &game->scene.players[playerId].charMan[0].model->lightPos[2], -10.f, 10.f);
    ImGui::SliderInt("Animation", &game->scene.players[playerId].charMan[0].model->currentAnim, 0, game->scene.players[playerId].charMan[0].model->animCount);
    ImGui::SliderInt("Animation Frame", &game->scene.players[playerId].charMan[0].model->currentAnimFrame, 0, game->scene.players[playerId].charMan[0].model->currentAnimFrameCount);

    ImGui::End();
}

void DevGui::_displayStateManipButtons()
{
    ImGui::Begin("State Manipulation");
    ImGui::Columns(4);

    if(ImGui::Button("Save State") || IsKeyPressed(KEY_Z))
    {
        _saveGameState();
    }

    ImGui::NextColumn();

    if (ImGui::Button("Load State") || IsKeyPressed(KEY_X))
    {
        _loadGameState();
    }

    ImGui::NextColumn();

    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, game->scene.willStep ? xGREEN : xRED);
    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonHovered, game->scene.willStep ? xGREENHover : xREDHover);
    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, game->scene.willStep ? xBLACK : xWHITE);
    if (ImGui::Button("Toggle Update") || IsKeyPressed(KEY_C))
    {
        _toggleUpdate();
    }
    ImGui::PopStyleColor(3);

    ImGui::NextColumn();

    if (ImGui::Button("Step Update") || IsKeyPressed(KEY_V))
    {
        _stepUpdate();
    }

    ImGui::NextColumn();

    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, isRecording ? xGREEN : xRED);
    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonHovered, isRecording ? xGREENHover : xREDHover);
    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, isRecording ? xBLACK : xWHITE);
    if (ImGui::Button("Toggle Record") || IsKeyPressed(KEY_R))
    {
        _toggleRecording();
    }
    ImGui::PopStyleColor(3);

    ImGui::NextColumn();

    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, isPlaying ? xGREEN : xRED);
    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonHovered, isPlaying ? xGREENHover : xREDHover);
    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, isPlaying ? xBLACK : xWHITE);
    if (ImGui::Button("Toggle Playback") || IsKeyPressed(KEY_F))
    {
        _togglePlayback();
    }
    ImGui::PopStyleColor(3);

    ImGui::End();
}

void DevGui::_displayPlayerInputHistory(int playerId)
{
    ImGui::Begin(std::string("Player ").append(std::to_string(playerId)).append(" Input History").c_str());

    for (int i = 0; i < INPUT_HISTORY_MAX; i++)
    {
        ImGui::Text(std::to_string(game->gameState.inputHistory[playerId][i]).c_str());
    }

    ImGui::End();
}

void DevGui::_displayAvailableControllers()
{
    ImGui::Begin("Controllers");

    for (int i = 0; i < MAX_KEYBOARDS + MAX_GAMEPADS; i++)
    {
        ImGui::Text("(%d) %s", game->controllers[i].controllerType, game->controllers[i].name);
    }

    ImGui::End();
}

void DevGui::_displayPlayerController(int playerId)
{}

void DevGui::_displayRecordingState()
{
    ImGui::Begin("Recording/Playback");

    ImGui::Text("Recording: %d", isRecording);
    ImGui::Text("Playback: %d", isPlaying);

    ImGui::End();
}

void DevGui::_displayRenderWindow()
{
    ImGui::SetNextWindowSizeConstraints({50.f, 50.f}, {(float)GetScreenWidth(), (float)GetScreenHeight()}, _SixteenNineAspectRatio);
    ImGui::Begin("Render window");

    renderWindowIsFocused = ImGui::IsWindowFocused();
    ImVec2 wp = ImGui::GetWindowPos();

    if (!ImGui::IsWindowCollapsed())
    {
        DrawTexturePro(renderTexture.texture,
            {
                0.f,
                0.f,
                (float)renderTexture.texture.width,
                (float)-renderTexture.texture.height
            },
            {
                wp.x,
                wp.y + 20.f,
                (float)ImGui::GetWindowWidth(),
                (float)ImGui::GetWindowHeight() - 20
            },
            {
                0,
                0
            },
            0.f,
            WHITE);
    }

    ImGui::End();
}

void DevGui::_saveGameState()
{
    std::cout << "Clicked: Save State" << std::endl;
    gsLen = sizeof(game->gameState);
    gsBuffer = (unsigned char *)malloc(gsLen);
    if (!*gsBuffer)
    {
        return;
    }
    memcpy(gsBuffer, &game->gameState, gsLen);
    game->gameState.playerData[0].vitality -= 10;
    // std::ofstream file;
    // file.open("buffer.txt", std::ofstream::out | std::ofstream::binary);
    // file << (void *)*gsBuffer;
    // file.close();
}

void DevGui::_loadGameState()
{
    std::cout << "Clicked: Load State" << std::endl;

    std::ifstream file;
    // file.open("buffer.txt", std::ofstream::in | std::ofstream::binary);
    // int dataSize = file.tellg();
    // char *data = new char[dataSize];
    // file.read(data, dataSize);
    // file.close();
    memcpy(&game->gameState, gsBuffer, gsLen);
}

void DevGui::_toggleUpdate()
{
    game->scene.willStep = !game->scene.willStep;
}

void DevGui::_stepUpdate(int allowance)
{
    game->scene.willStep = false;
    game->scene.stepAllowance = allowance;
}

void DevGui::_toggleRecording()
{
    _stopPlayback();

    if (isRecording)
    {
        _stopRecording();
    }
    else
    {
        _startRecording();
    }
}

void DevGui::_togglePlayback()
{
    _stopRecording();

    if (isPlaying)
    {
        _stopPlayback();
    }
    else
    {
        _startPlayback();
    }
}

void DevGui::_startRecording()
{
    _stopPlayback();
    isRecording = true;
    recordingSize = 0;
    game->scene.players[1].controllerId = 0; // game->scene.players[0].controllerId;
    game->scene.players[0].controllerId = -1;
}

void DevGui::_record()
{
    PlayerInput input = game->gameState.playerData[1].input;

    PlayerInput currentInput;
    PlayerInput newInput = input;
    for (int i = 0; i < 60*60; i++)
    {
        currentInput = p2Recording[i];
        p2Recording[i] = newInput;
        newInput = currentInput;
    }
    recordingSize++;
    if (recordingSize > 60*60)
    {
        recordingSize = 60*60;
    }
}

void DevGui::_stopRecording()
{
    isRecording = false;
    game->scene.players[0].controllerId = 0; // game->scene.players[1].controllerId;
    game->scene.players[1].controllerId = -1;
}

void DevGui::_startPlayback()
{
    _stopRecording();
    isPlaying = true;
}

void DevGui::_play()
{
    game->scene.players[1].setInputs(p2Recording[recordingSize - 1 - playbackCursorReverse]);
    playbackCursorReverse++;
    if (playbackCursorReverse > recordingSize)
        playbackCursorReverse = 0;
}

void DevGui::_stopPlayback()
{
    isPlaying = false;
    playbackCursorReverse = 0;
    game->scene.players[1].setInputs((PlayerInput)0);
}
