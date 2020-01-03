#include "foosiespp.hpp"

Game::Game()
{
    scene.players[0].init(&gameState.playerData[0], &gameState.playerBoxes[0], &gameState.playerProjectiles[0]);
    scene.players[1].init(&gameState.playerData[1], &gameState.playerBoxes[1], &gameState.playerProjectiles[1]);

    scene.players[0].charMan[0].color = Color{50, 50, 50, 255};
    scene.players[0].controllerId = -1;
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

#ifdef _DEBUG
    devGui.imguiInit((dgScene *)&scene, &gameState);
#endif
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
    if (scene.willStep || scene.stepAllowance > 0)
    {
        scene.stepAllowance--;

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
}

void Game::render()
{
    BeginDrawing();

#ifdef _DEBUG
    ClearBackground(GRAY);
#else
    ClearBackground(RAYWHITE);
#endif

#ifdef _DEBUG
    DrawFPS(10, 10);
    devGui.beginRenderTexture();
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
};

#ifdef _DEBUG
void Game::_drawDevUI()
{
    devGui.imguiUpdate();
}
#endif
