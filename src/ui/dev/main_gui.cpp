#include "main_gui.hpp"
#include <string>
#include "../../deps/raylib/raylib.h"

void DevGui::imguiInit(dgScene *s, GameState *gs)
{
    scene = s;
    gameState = gs;

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
    _displayRenderWindow();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void DevGui::begin()
{
    BeginTextureMode(renderTexture);
}
void DevGui::end()
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

    ImGui::Text("Action Face: %i", gameState->playerData[playerId].actionFace);
    ImGui::Text("Side Face: %i", gameState->playerData[playerId].sideFace);
    ImGui::Text("Physical:");
    ImGui::Text("       X: %i", gameState->playerData[playerId].physical.x);
    ImGui::Text("       Y: %i", gameState->playerData[playerId].physical.y);
    ImGui::Text("  HSpeed: %i", gameState->playerData[playerId].physical.HSpeed);
    ImGui::Text("  HSpeed: %i", gameState->playerData[playerId].physical.VSpeed);
    char buf[254] = "";
    ImGui::InputText("Test", buf, 254);

    ImGui::End();
}

void DevGui::_displayRenderWindow()
{
    ImGui::SetNextWindowSizeConstraints({50.f, 50.f}, {(float)GetScreenWidth(), (float)GetScreenHeight()}, _SixteenNineAspectRatio);
    ImGui::Begin("Render window");

    ImVec2 wp = ImGui::GetWindowPos();

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

    ImGui::End();
}