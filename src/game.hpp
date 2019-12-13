#ifndef FOOSIESPP_H
#define FOOSIESPP_H

#include <iostream>
#include <string>
#include <vector>
#include "../bin/ggponet.h"
#include "../bin/raylib.h"
#include "globals.hpp"
#include "button.hpp"
#include "controller.hpp"
#include "player.hpp"
#include "session.hpp"

namespace Game
{
    struct Grid {
        int hCells;
        int vCells;
    };

    struct Scene {
        int targetFPS;
        Camera3D cam;
        PlayerController::Player players[2];
        Button _makeGameStateBufferBtn;
        Button _loadGameStateBtn;
    };

    Grid grid;
    extern Scene scene;
    extern GameState gameState;
    Session *session;
    std::vector<Controller> controllers;
    Controller keyboard;

    void init();
    void unload();

    void startLoop();
    void update();
    void render();
    void createMultiplayerSession();
    void deleteSession();

    void _drawScene();
    void _drawUI();
    void _aggregateGamepadInputs();
    void _dispatchNormalizedInputs(PlayerController::Player &player);
};

void _saveGameState();
void _loadGameState();

#endif
