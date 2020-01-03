#ifndef FOOSIESPP_H
#define FOOSIESPP_H

#include <iostream>
#include <string>
#include <vector>
#include "../bin/ggponet.h"
#include "deps/raylib/raylib.h"
#include "globals.hpp"
#include "button.hpp"
#include "controller.hpp"
#include "player.hpp"
#include "session.hpp"
#include "ui/dev/main_gui.hpp"

struct Grid {
    int hCells;
    int vCells;
};

struct Scene {
    int targetFPS;
    int stageHalfWidth = 700;
    Camera3D cam;
    PlayerController players[2];
    Button _makeGameStateBufferBtn;
    Button _loadGameStateBtn;
    Button _toggleUpdateBtn;
    Button _stepOneBtn;
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
    RenderTexture renderTexture;

    void _aggregateGamepadInputs();
    void _dispatchNormalizedInputs(PlayerController &player);
    void _drawScene();
    void _drawUI();

// dev stuff
#ifdef _DEBUG
    DevGui devGui;

    void _drawDevUI();
#endif
};

void _saveGameState();
void _loadGameState();

#endif
