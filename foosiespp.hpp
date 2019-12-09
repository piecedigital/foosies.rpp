#ifndef FOOSIESPP_H
#define FOOSIESPP_H

#include <iostream>
#include <string>
#include <vector>
#include "bin/ggponet.h"
#include "bin/raylib.h"
#include "custom-types.hpp"
#include "button.hpp"
#include "controller.hpp"
#include "player.hpp"
#include "session.hpp"

struct Grid {
    int hCells;
    int vCells;
};

struct Scene {
    int targetFPS;
    Camera3D cam;
    PlayerController players[2];
    Button _makeGameStateBufferBtn;
    Button _loadGameStateBtn;
};

class Game
{
public:
    Grid grid;
    Scene scene;
    GameState gameState;
    Session *session;
    std::vector<Controller> controllers;
    Controller keyboard;

    Game();
    ~Game();
    int init();
    void update();
    void render();
    void createMultiplayerSession();
    void deleteSession();

private:
    void _drawScene();
    void _drawUI();
    void _aggregateGamepadInputs();
    void _dispatchNormalizedInputs(PlayerController &player);
};

void _saveGameState();
void _loadGameState();

#endif
