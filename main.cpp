// main.cpp : Defines the entry point for the application.
//

#include "foosiespp.h"

using namespace std;

Game::Game()
{
    Game::grid = Grid();
    Game::scene = Scene();
    Game::gameState = GameState();
}

int Game::init()
{
    int screenWidth = 800;
    int screenHeight = 450;

    scene.targetFPS = 60;

    scene.cam = Camera3D();
    scene.cam.position = Vector3{0.f, 10.f, 8.f};
    scene.cam.target = Vector3{0.f, 0.f, 0.f};
    scene.cam.up = Vector3{0.f, 1.f, 0.f};
    scene.cam.fovy = 60.f;
    scene.cam.type = CAMERA_PERSPECTIVE;

    InitWindow(screenWidth, screenHeight, "foosiespp");
    SetTargetFPS(scene.targetFPS);

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
    std::vector<InputNormalization> inputList = _aggregateGamepadInputs();
}

void Game::render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    _drawScene();
    _drawUI();

    EndDrawing();
}

void Game::startMultiplayerSession()
{
    Game::session = Session();

    /* Start a new session */
    GGPOErrorCode result = session.start();
}

void Game::_drawScene()
{
    BeginMode3D(scene.cam);

    DrawGrid(10, 1.f);

    EndMode3D();
}

void Game::_drawUI()
{
    GGPOPlayerType type = GGPOPlayerType::GGPO_PLAYERTYPE_REMOTE;
    std::string x = "This is a raylib->Foosies example, involving: ";
    std::string y = std::to_string((int)type);
    x.append(y);

    DrawText(x.c_str(), 10, 40, 20, DARKGRAY);
    DrawFPS(10, 10);
};

std::vector<InputNormalization> Game::_aggregateGamepadInputs()
{
    unsigned int maxPads = 4;
    std::vector<InputNormalization> inputList;

    for (unsigned int padId = 0; padId < maxPads; padId++)
    {
        if(IsGamepadAvailable(padId))
        {
            inputList.push_back(_getGamepadInputs(padId));
        }
    }

    return inputList;
}

InputNormalization Game::_getGamepadInputs(int padId)
{
    InputNormalization keys = InputNormalization();

    // @TODO: get axis working like "pressed"
    // GetGamepadAxisMovement(AXIS_LEFT_V);

    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_UP))
    {
        cout << "DIR_V -= 1" << endl;
        keys.DIR_V -= 1;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_DOWN))
    {
        cout << "DIR_V += 1" << endl;
        keys.DIR_V += 1;
    }

    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_LEFT))
    {
        cout << "DIR_H -= 1" << endl;
        keys.DIR_H -= 1;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_RIGHT))
    {
        cout << "DIR_H += 1" << endl;
        keys.DIR_H += 1;
    }
    // Y/Triangle
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_UP))
    {
        cout << "FACE_UP = true" << endl;
        keys.FACE_UP = true;
    }
    // A/Cross
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
    {
        cout << "FACE_DOWN = true" << endl;
        keys.FACE_DOWN = true;
    }
    // X/Square
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
    {
        cout << "FACE_LEFT = true" << endl;
        keys.FACE_LEFT = true;
    }
    // B/Circle
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
    {
        cout << "FACE_RIGHT = true" << endl;
        keys.FACE_RIGHT = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_1))
    {
        cout << "SHOULDER_L = true" << endl;
        keys.SHOULDER_L = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
    {
        cout << "SHOULDER_R = true" << endl;
        keys.SHOULDER_R = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_2))
    {
        cout << "TRIGGER_L = true" << endl;
        keys.TRIGGER_L = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_2))
    {
        cout << "TRIGGER_R = true" << endl;
        keys.TRIGGER_R = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE_LEFT))
    {
        cout << "SELECT = true" << endl;
        keys.SELECT = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE))
    {
        cout << "HOME = true" << endl;
        keys.HOME = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE_RIGHT))
    {
        cout << "START = true" << endl;
        keys.START = true;
    }

    return keys;
}

int main()
{
    Game game = Game();
    return game.init();
}
