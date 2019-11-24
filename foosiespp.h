#include <iostream>
#include <string>
#include <vector>
#include "bin/ggponet.h"
#include "bin/raylib.h"
#include "player.h"
#include "session.h"
#include "custom-types.h"

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

struct InputNormalization
{
    int DIR_H = 0;
    int DIR_V = 0;
    bool FACE_UP = false;
    bool FACE_DOWN = false;
    bool FACE_LEFT = false;
    bool FACE_RIGHT = false;
    bool SHOULDER_L = false;
    bool SHOULDER_R = false;
    bool TRIGGER_L = false;
    bool TRIGGER_R = false;
    bool SELECT = false;
    bool START = false;
    bool HOME = false;
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
    void startMultiplayerSession();
private:
    void _drawScene();
    void _drawUI();
    std::vector<InputNormalization> _aggregateGamepadInputs();
    InputNormalization _getGamepadInputs(int padId);
};
