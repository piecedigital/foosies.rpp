// main.cpp : Defines the entry point for the application.
//

#include "foosies++.h"
#include "session.h"

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

    InitWindow(screenWidth, screenHeight, "Foosies++");
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
}

void Game::render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    _drawScene();
    _drawUI();

    EndDrawing();
}

void Game::g()
{
    Session session;

    /* Start a new session */
    GGPOErrorCode result = ggpo_start_session(&session.ggpo, // the new session object
                                            &session.cb,     // our callbacks
                                            "test_app",      // application name
                                            2,               // 2 players
                                            sizeof(int),     // size of an input packet
                                            8001);           // our local udp port
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

int main()
{
    Game game = Game();
    return game.init();
}
