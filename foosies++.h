// foosies++.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <string>
#include "bin/ggponet.h"
#include "bin/raylib.h"
#include "player.h"

struct Grid {
    int hCells;
    int vCells;
};

struct Scene {
    int targetFPS;
    Camera3D cam;
};

struct GameState
{
    Player players[2];
};

class Game
{
public:
    Grid grid;
    Scene scene;
    GameState gameState;
    Session session;
    Game();
    int init();
    void update();
    void render();
    void go();
private:
    void _drawScene();
    void _drawUI();
};
