#include "foosiespp.hpp"
#include "actions.hpp"

Game::Game()
{
    for (int i = 0; i < MAX_KEYBOARDS + MAX_GAMEPADS; i++)
    {
        controllers[i].name = "";
        controllers[i].padId = i - MAX_KEYBOARDS;
        controllers[i].controllerType = ControllerType::gamepad;

        if (i < MAX_KEYBOARDS)
        {
            controllers[i].name = "Keyboard";
            controllers[i].controllerType = ControllerType::keyboard;
        }
    }

    scene.players[0].init(gameState.inputHistory[0], &gameState.playerData[0], &gameState.playerBoxes[0], &gameState.playerProjectiles[0]);
    scene.players[1].init(gameState.inputHistory[1], &gameState.playerData[1], &gameState.playerBoxes[1], &gameState.playerProjectiles[1]);

    scene.players[1].playerData->sideFace = -1;
    scene.players[1].playerData->actionFace = -1;

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
}

Game::~Game()
{
    // delete gameState.playerData;
#ifdef _DEBUG
    devGui.imguiShutdown();
#endif
}

int Game::init(ConnectionInfo ci)
{
    scene.targetFPS = 60;

    scene.cam = Camera3D();
    scene.cam.up = {0.f, 1.f, 0.f};

    scene.cam.position = {0.f, 3.f, 2.f};
    scene.cam.target = {0.f, 3.f, 0.f};
    scene.cam.fovy = 8.f;
    scene.cam.type = CAMERA_ORTHOGRAPHIC;

    // scene.cam.position = {0.f, 4.f, 80.f};
    // scene.cam.target = {0.f, 4.f, 0.f};
    // scene.cam.fovy = 40.f;
    // scene.cam.type = CAMERA_PERSPECTIVE;

    SetTargetFPS(scene.targetFPS);

#ifdef _DEBUG
    devGui.imguiInit(this);
#endif
    createMultiplayerSession(ci);
    while (!WindowShouldClose())
    {
        _pollControllerInputs();

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
    if (scene.willStep || scene.stepAllowance > 0)
    {
        scene.stepAllowance--;

        scene.players[0].updatePhysics();
        scene.players[1].updatePhysics();

        scene.players[0].updateFacing(&scene.players[1]);
        scene.players[1].updateFacing(&scene.players[0]);

        _insureControllerAssignment(scene.players[0], scene.players[1]);

        _dispatchNormalizedInputs(scene.players[0]);
        _dispatchNormalizedInputs(scene.players[1]);

        session->synchronizeInputs();

        scene.players[0].processInputs();
        scene.players[1].processInputs();

        scene.players[0].calcPhysics(&scene.players[1], scene.stageHalfWidth);
        scene.players[1].calcPhysics(&scene.players[0], scene.stageHalfWidth);

        scene.players[0].updateBoxes();
        scene.players[1].updateBoxes();

        scene.players[0].checkCollisions(&scene.players[1], scene.stageHalfWidth);
        scene.players[1].checkCollisions(&scene.players[0], scene.stageHalfWidth);

        scene.players[0].advanceLocalFrame();
        scene.players[1].advanceLocalFrame();
    }

    scene.players[0].updateBoxes();
    scene.players[1].updateBoxes();

    _updateCamera();
}

void Game::render()
{
    BeginDrawing();

#ifdef _DEBUG
    ClearBackground(GRAY);
    DrawFPS(10, 10);
    devGui.beginRenderTexture();
    ClearBackground(RAYWHITE);
#else
    ClearBackground(RAYWHITE);
#endif
    _drawScene();

    _drawUI();
#ifdef _DEBUG
    devGui.endRenderTexture();
    _drawDevUI();
#endif

    EndDrawing();
}

void Game::createMultiplayerSession(ConnectionInfo ci)
{
    deleteSession();
    session = new Session(&gameState);

    /* Start a new session */
    GGPOErrorCode result = session->start();

    if (ci.local)
    {
        session->addPlayer(&scene.players[0], GGPO_PLAYERTYPE_LOCAL);
        session->addPlayer(&scene.players[1], GGPO_PLAYERTYPE_REMOTE);
    }
    else
    {
        session->addPlayer(&scene.players[1], GGPO_PLAYERTYPE_LOCAL);
        session->addPlayer(&scene.players[0], GGPO_PLAYERTYPE_REMOTE);
    }
}

void Game::deleteSession()
{
    if (session != NULL)
    {
        delete &session;
        session = NULL;
    }
}

void Game::saveGameState()
{
    std::cout << "Clicked: Save State" << std::endl;
    gsLen = sizeof(gameState);
    gsBuffer = (unsigned char *)malloc(gsLen);
    if (!*gsBuffer)
    {
        return;
    }
    memcpy(gsBuffer, &gameState, gsLen);
    gameState.playerData[0].vitality -= 10;
    // std::ofstream file;
    // file.open("buffer.txt", std::ofstream::out | std::ofstream::binary);
    // file << (void *)*gsBuffer;
    // file.close();
}

void Game::loadGameState()
{
    std::cout << "Clicked: Load State" << std::endl;

    std::ifstream file;
    // file.open("buffer.txt", std::ofstream::in | std::ofstream::binary);
    // int dataSize = file.tellg();
    // char *data = new char[dataSize];
    // file.read(data, dataSize);
    // file.close();
    memcpy(&gameState, gsBuffer, gsLen);
}

void Game::toggleUpdate()
{
    scene.willStep = !scene.willStep;
}

void Game::stepUpdate(int allowance)
{
    scene.willStep = false;
    scene.stepAllowance = allowance;
}


void Game::_pollControllerInputs()
{
    unsigned int maxPads = MAX_KEYBOARDS + MAX_GAMEPADS;

    // get input for gamepads
    for (unsigned int controllerId = 0; controllerId < maxPads; controllerId++)
    {
        if (controllers[controllerId].controllerType == ControllerType::keyboard)
        {
            controllers[controllerId].pollNormalizedInputs();
        }
        else if (IsGamepadAvailable(controllers[controllerId].padId))
        {
            controllers[controllerId].available = true;
            controllers[controllerId].name = GetGamepadName(controllers[controllerId].padId);
            controllers[controllerId].pollNormalizedInputs();
        }
        else
        {
            controllers[controllerId].available = false;
            controllers[controllerId].name = "";
            for (int i = 0; i < 2; i++)
            {
                if (scene.players[i].controllerId == controllerId)
                {
                    scene.players[i].controllerId = -1;
                    break;
                }
            }
        }
    }
}

void Game::_insureControllerAssignment(PlayerController &player1, PlayerController &player2)
{
    unsigned int maxPads = MAX_KEYBOARDS + MAX_GAMEPADS;

    if (player1.controllerId < 0)
    {
        for (unsigned int controllerId = 0; controllerId < maxPads; controllerId++)
        {
            if (controllerId != player2.controllerId && controllers[controllerId].buttonPressed)
            {
                player1.controllerId = controllerId;
                break;
            }
        }
    }

    if (player2.controllerId < 0)
    {
        for (unsigned int controllerId = 0; controllerId < maxPads; controllerId++)
        {
            if (controllerId != player1.controllerId && controllers[controllerId].buttonPressed)
            {
                player2.controllerId = controllerId;
                break;
            }
        }
    }
}

void Game::_dispatchNormalizedInputs(PlayerController &player)
{
    if (player.controllerId > -1)
    {
#ifdef _DEBUG
        if (devGui.renderWindowIsFocused)
        {
            player.normalizedToPlayerInput(controllers[player.controllerId].inputs);
        }
        else
        {
            player.normalizedToPlayerInput({0});
        }
#else
        player.normalizedToPlayerInput(controllers[player.controllerId].inputs);
#endif
    }
}

void Game::_updateCamera()
{
#ifdef _DEBUG
    if (IsKeyDown(KEY_UP))
    {
        scene.cam.fovy -= .2;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        scene.cam.fovy += .2;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        scene.cam.position.x -= .2;
        scene.cam.target.x -= .2;
    }
    if (IsKeyDown(KEY_RIGHT))
    {
        scene.cam.position.x += .2;
        scene.cam.target.x += .2;
    }
    if (IsKeyDown(KEY_PAGE_UP))
    {
        scene.cam.position.y += .2;
        scene.cam.target.y += .2;
    }
    if (IsKeyDown(KEY_PAGE_DOWN))
    {
        scene.cam.position.y -= .2;
        scene.cam.target.y -= .2;
    }
#else
    // calculate camera position based on player position
#endif
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
};

#ifdef _DEBUG
void Game::_drawDevUI()
{
    devGui.imguiUpdate();
}
#endif
