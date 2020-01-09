#ifndef FOOSIESPP_H
#define FOOSIESPP_H

#include <iostream>
#include <string>
#include <vector>
#include "../bin/ggponet.h"
#include "deps/raylib/raylib.h";
#include "globals.hpp"
#include "button.hpp"
#include "controller.hpp"
#include "player.hpp"
#include "session.hpp"

#ifdef _DEBUG
#include "ui/dev/main_gui.hpp"
#endif

struct Scene {
    int targetFPS;
    int stageHalfWidth = 700;
    int stepAllowance = 0;
    bool willStep = true;
    Camera3D cam;
    PlayerController players[2];
};

class Game
{
public:
    Scene scene;
    GameState gameState;
    Session *session;
    // std::vector<Controller> controllers;
    Controller controllers[MAX_KEYBOARDS + MAX_GAMEPADS];
    Controller keyboard;

    Game();
    ~Game();
    int init();
    void update();
    void render();
    void createMultiplayerSession();
    void deleteSession();

private:
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

void _toggleUpdate();
void _stepOne();

#endif
