#include <iostream>
#include <string>
#include <vector>
#include "bin/ggponet.h"
#include "bin/raylib.h"
#include "controller.h"
#include "player.h"
#include "session.h"

struct Grid {
    int hCells;
    int vCells;
};

struct Scene {
    int targetFPS;
    Camera3D cam;
    PlayerController players[2];
};

struct GameState
{
};

class Game
{
public:
    Grid grid;
    Scene scene;
    GameState gameState;
    PlayerController player1, player2;
    Session session;
    std::vector<Controller> controllers;
    Controller keyboard;

    Game();
    int init();
    void update();
    void render();
    void startMultiplayerSession();
private:
    void _drawScene();
    void _drawUI();
    std::vector<NormalizedInput> _aggregateGamepadInputs();
};
