#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include "deps/raylib/raylib.h";
#include "globals.hpp"

#define MAX_KEYBOARDS 1
#define MAX_GAMEPADS 4

enum ControllerType
{
    gamepad = 0,
    keyboard,
};

class Controller
{
public:
    int padId = -1;
    ControllerType controllerType = ControllerType::keyboard;
    bool available = false;
    const char *name = "";
    NormalizedInput inputs = {0};

    Controller(unsigned int padId, ControllerType type, const char *name);
    Controller();
    ~Controller();
    void pollNormalizedInputs();

    bool _IsInputDown(std::string button);
    bool _IsInputPressed(std::string button);
    void _axisRecalculate();
    bool _IsAxisTilted(std::string direction);
    bool _IsAxisJustTilted(std::string direction);

private:
    float axisThresholdH;
    float axisThresholdV;
    float axisAbsoluteH;
    float axisAbsoluteV;
    float axisChangedH;
    float axisChangedV;

    void _resetInputs();
};

#endif
