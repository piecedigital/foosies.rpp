#include "foosiespp.hpp"
#include "deps/imgui/imgui.h"
#include "deps/imgui/imgui_impl_glfw.h"
#include "deps/imgui/imgui_impl_opengl3.h"
// TEST CODE

int len;
unsigned char *buffer;
GameState *tempState;

void _saveGameState()
{
    std::cout << "Clicked: Save State" << std::endl;
    len = sizeof(*tempState);
    buffer = (unsigned char *)malloc(len);
    if (!*buffer)
    {
        return;
    }
    memcpy(buffer, tempState, len);
    tempState->playerData[0].vitality -= 10;
}

void _loadGameState()
{
    std::cout << "Clicked: Load State" << std::endl;
    memcpy(tempState, buffer, len);
}

static bool willStep = true;
int stepAllowance;

void _toggleUpdate()
{
    willStep = !willStep;
}

void _stepOne()
{
    willStep = false;
    stepAllowance = 1;
}

// END TEST CODE

Game::Game()
{
    tempState = &gameState;
    scene.players[0].init(&gameState.playerData[0], &gameState.playerBoxes[0], &gameState.playerProjectiles[0]);
    scene.players[1].init(&gameState.playerData[1], &gameState.playerBoxes[1], &gameState.playerProjectiles[1]);

    scene.players[0].charMan[0].color = Color{50, 50, 50, 255};
    scene.players[0].controllerId = -1;
    scene.players[1].playerData->sideFace = -1;
    scene.players[1].playerData->actionFace = -1;

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    scene._makeGameStateBufferBtn.init("Save State", {(float)((screenWidth / 2) - 100), (float)(screenHeight - 40)});
    scene._makeGameStateBufferBtn.callbacks.onClick = _saveGameState;
    scene._loadGameStateBtn.init("Load State", {(float)((screenWidth / 2) + 5), (float)(screenHeight - 40)});
    scene._loadGameStateBtn.callbacks.onClick = _loadGameState;

    const char *x;
    x = willStep ? "Pause update: yes" : "Pause update: no";
    scene._toggleUpdateBtn.init(x, {(float)((screenWidth / 2) + 100), (float)(screenHeight - 40)});
    scene._toggleUpdateBtn.callbacks.onClick = _toggleUpdate;
    scene._stepOneBtn.init("Step one frame", {(float)((screenWidth / 2) + 250), (float)(screenHeight - 40)});
    scene._stepOneBtn.callbacks.onClick = _stepOne;

    _saveGameState();
}

Game::~Game()
{
    UnloadTexture(renderTexture.texture);
    UnloadRenderTexture(renderTexture);
    // delete gameState.playerData;
    _imguiShutdown();
}

int Game::init()
{
    scene.targetFPS = 60;

    scene.cam = Camera3D();
    scene.cam.up = Vector3{0.f, 1.f, 0.f};

    scene.cam.position = Vector3{0.f, 3.f, 2.f};
    scene.cam.target = Vector3{0.f, 3.f, 0.f};
    scene.cam.fovy = 8.f;
    scene.cam.type = CAMERA_ORTHOGRAPHIC;

    // scene.cam.position = Vector3{0.f, 4.f, 80.f};
    // scene.cam.target = Vector3{0.f, 4.f, 0.f};
    // scene.cam.fovy = 40.f;
    // scene.cam.type = CAMERA_PERSPECTIVE;

    SetTargetFPS(scene.targetFPS);

    _imguiInit();

    renderTexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    while (!WindowShouldClose())
    {
        _aggregateGamepadInputs();

        // update the state
        update();
        // draw the state
        render();
    }

    CloseWindow();
    return 0;
}

void Game::update()
{
    if (willStep || stepAllowance > 0)
    {
        stepAllowance--;

        scene.players[0].updateFacing(&scene.players[1]);
        scene.players[1].updateFacing(&scene.players[0]);

        _dispatchNormalizedInputs(scene.players[0]);
        _dispatchNormalizedInputs(scene.players[1]);

        scene.players[0].processInputs();
        scene.players[1].processInputs();

        scene.players[0].calcPhysics(&scene.players[1], scene.stageHalfWidth);
        scene.players[1].calcPhysics(&scene.players[0], scene.stageHalfWidth);

        scene.players[0].updatePhysics();
        scene.players[1].updatePhysics();

        scene.players[0].updateBoxes();
        scene.players[1].updateBoxes();

        scene.players[0].checkCollisions(&scene.players[1], scene.stageHalfWidth);
        scene.players[1].checkCollisions(&scene.players[0], scene.stageHalfWidth);

        scene.players[0].updateBoxes();
        scene.players[1].updateBoxes();
    }

    scene._makeGameStateBufferBtn.update();
    scene._loadGameStateBtn.update();
    scene._toggleUpdateBtn.update();
    scene._stepOneBtn.update();
}

void Game::render()
{
    BeginDrawing();

    // ClearBackground(RAYWHITE);
    ClearBackground(GRAY);

    DrawFPS(10, 10);

    BeginTextureMode(renderTexture);

    // Vector2 mp = GetMousePosition();
    // BeginScissorMode(mp.x-50, mp.y-50, 100, 100);

    ClearBackground(RAYWHITE);

    _drawScene();

    _drawUI();

    // EndScissorMode();

    EndTextureMode();

    _drawDevUI();

    EndDrawing();
}

void Game::createMultiplayerSession()
{
    deleteSession();
    session = new Session();

    /* Start a new session */
    GGPOErrorCode result = session->start();
}

void Game::deleteSession()
{
    if (session != NULL)
    {
        delete &session;
        session = NULL;
    }
}

void Game::_aggregateGamepadInputs()
{
    unsigned int maxPads = 4;
    int padsAvailable = 0;

    // get input for keyboard
    keyboard.pollNormalizedInputs();

    // get input for gamepads
    for (unsigned int padId = 0; padId < maxPads; padId++)
    {
        if (IsGamepadAvailable(padId))
        {
            padsAvailable++;

            if (padId < controllers.size())
            {
                if (GetGamepadName(padId) != controllers.at(padId).name)
                {
                    controllers.erase(controllers.begin() + padId);
                    controllers.emplace(controllers.begin() + padId, Controller(padId, GetGamepadName(padId)));
                }
            }
            else
            {
                controllers.push_back(Controller(padId, GetGamepadName(padId)));
            }

            controllers.at(padId).pollNormalizedInputs();
        }
    }

    if (padsAvailable > 0)
    {
        controllers.erase(controllers.begin() + padsAvailable - 1, controllers.end());
    }
}

void Game::_dispatchNormalizedInputs(PlayerController &player)
{
    if (player.controllerId > -2)
    {
        if (player.controllerId == -1)
        {
            player.normalizedToPlayerInput(keyboard.inputs);
        }
        else
        {
            player.normalizedToPlayerInput(controllers[player.controllerId].inputs);
        }
    }
}

void Game::_drawScene()
{
    UpdateCamera(&scene.cam);

    BeginMode3D(scene.cam);

    DrawGrid(10, 1.f);
    for (PlayerController &player : scene.players)
    {
        player.charMan[0].render();
    }

    EndMode3D();
}

void Game::_drawUI()
{
    GGPOPlayerType type = GGPOPlayerType::GGPO_PLAYERTYPE_REMOTE;
    std::string player1Info = "Player 1: ";
    player1Info.append("\n")
        .append("- Face: ")
        .append("\n")
        .append("  - Action: ")
        .append(std::to_string(gameState.playerData[0].actionFace))
        .append("\n")
        .append("  - Side: ")
        .append(std::to_string(gameState.playerData[0].sideFace))
        .append("\n")
    //     .append("- Vitality: ")
    //     .append(std::to_string(gameState.playerData[0].vitality))
    //     .append("\n");
        .append("- Position: ")
        .append("\n")
        .append("  - X: ")
        .append(std::to_string(gameState.playerData[0].physical.x))
        .append("\n")
        .append("  - Y: ")
        .append(std::to_string(gameState.playerData[0].physical.y))
        .append("\n")
        .append("  - HSpeed: ")
        .append(std::to_string(gameState.playerData[0].physical.HSpeed))
        .append("\n")
        .append("  - PushBack: ")
        .append(std::to_string(gameState.playerData[0].physical.pushback))
        .append("\n");;

    std::string player2Info = "Player 2: ";
    player2Info.append("\n")
        .append("- Face: ")
        .append("\n")
        .append("  - Action: ")
        .append(std::to_string(gameState.playerData[1].actionFace))
        .append("\n")
        .append("  - Side: ")
        .append(std::to_string(gameState.playerData[1].sideFace))
        .append("\n")
    //     .append("- Vitality: ")
    //     .append(std::to_string(gameState.playerData[1].vitality))
    //     .append("\n")
        .append("- Position: ")
        .append("\n")
        .append("  - X: ")
        .append(std::to_string(gameState.playerData[1].physical.x))
        .append("\n")
        .append("  - Y: ")
        .append(std::to_string(gameState.playerData[1].physical.y))
        .append("\n")
        .append("  - HSpeed: ")
        .append(std::to_string(gameState.playerData[1].physical.HSpeed))
        .append("\n")
        .append("  - PushBack: ")
        .append(std::to_string(gameState.playerData[1].physical.pushback))
        .append("\n");;

    const char *player1InfoString = player1Info.c_str();
    DrawText(player1InfoString, 20, 46, -16, DARKGRAY);
    const char *player2InfoString = player2Info.c_str();
    DrawText(player2InfoString, 1280 - 20 - fGetTextWidth(player2InfoString), 46, 16, DARKGRAY);

    // DrawTextRecEx(GetFontDefault(), "Test", {400, 400, 2.f, 2.f}, 24.f, 5.f, false, GREEN, 0, 0, BLUE, RED);
    DrawRectangleRec({400, 400, 2.f, 2.f}, GREEN);
    DrawTexturePro(GetFontDefault().texture, {400, 400, 2.f, 2.f}, {400, 400, 2.f, 2.f}, {400, 400}, 0.f, RED);

    scene._makeGameStateBufferBtn.render();
    scene._loadGameStateBtn.render();
    scene._toggleUpdateBtn.render();
    scene._stepOneBtn.render();
};

void Game::_drawDevUI()
{
    _imguiUpdate();
}

void Game::_imguiInit()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    GLFWwindow *window = (GLFWwindow *)GetWindow();

    std::cout << "GLFW Window gotten" << std::endl;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(/*glsl_version*/);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
}

void Game::_imguiUpdate()
{
    GLFWwindow *window = (GLFWwindow *)GetWindow();
    // glfwPollEvents();
    // glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    // glClear(GL_COLOR_BUFFER_BIT);

    // feed inputs to dear imgui, start new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // render your GUI
    ImGui::Begin("Demo window");
    int x = gameState.playerData[0].physical.x;
    ImGui::SliderInt("Slider Test", &x, -scene.stageHalfWidth, scene.stageHalfWidth);
    gameState.playerData[0].physical.x = x;
    ImGui::End();

    ImGui::SetNextWindowSizeConstraints({1.f, 0.5}, {200.f, 100.f});
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
            wp.y+20.f,
            (float)ImGui::GetWindowWidth(),
            (float)ImGui::GetWindowHeight()-20
        },
        {
            0,
            0
        },
        0.f,
        WHITE);
    ImGui::End();

    // Render dear imgui into screen
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // int display_w, display_h;
    // glfwGetFramebufferSize(window, &display_w, &display_h);
    // glViewport(0, 0, display_w, display_h);
    // glfwSwapBuffers(window);
}

void Game::_imguiShutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
