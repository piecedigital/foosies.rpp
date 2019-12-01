
#include "foosiespp.hpp"

Game::Game()
{
    scene.players[0].color = BLUE;
    scene.players[0].color = Color{50, 50, 50, 255};
    scene.players[0].controllerId = -1;
    scene.players[1].pd.face = -1;
}

int Game::init()
{
    int screenWidth = 800;
    int screenHeight = 450;

    scene.targetFPS = 60;

    scene.cam = Camera3D();
    scene.cam.position = Vector3{0.f, 4.f, 1.f};
    scene.cam.target = Vector3{0.f, 4.f, 0.f};
    scene.cam.up = Vector3{0.f, 1.f, 0.f};
    scene.cam.fovy = 10.f;
    // scene.cam.type = CAMERA_PERSPECTIVE;
    scene.cam.type = CAMERA_ORTHOGRAPHIC;

    InitWindow(screenWidth, screenHeight, "foosiespp");
    SetTargetFPS(scene.targetFPS);

    // @TODO: setup sessions correctly via user interface
    // startMultiplayerSession();

    while (!WindowShouldClose())
    {
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
    _aggregateGamepadInputs();

    for (PlayerController &player : scene.players)
    {
        _dispatchNormalizedInputs(player);

        player.update();
    }
}

void Game::render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    _drawScene();
    _drawUI();

    EndDrawing();
}

void Game::createMultiplayerSession()
{
    Game::session = &Session();

    /* Start a new session */
    // GGPOErrorCode result = session.start();
}

void Game::_drawScene()
{
    BeginMode3D(scene.cam);

    DrawGrid(10, 1.f);
    for (PlayerController &player : scene.players)
    {
        player.render();
    }

    EndMode3D();
}

void Game::_drawUI()
{
    GGPOPlayerType type = GGPOPlayerType::GGPO_PLAYERTYPE_REMOTE;
    std::string x = "This is a raylib->Foosies example, involving: ";
    std::string y = std::to_string((int)type);
    x.append(y);
    // DrawRectangle(0, 0, 1, 1, RED);

    DrawText(x.c_str(), 10, 40, 20, DARKGRAY);
    DrawFPS(10, 10);
};

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
