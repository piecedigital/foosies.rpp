
#include <iostream>
#include "bin/raylib.h"
#include "controller.h"

using namespace std;

Controller::Controller(unsigned int padId, const char *name)
{
    Controller::padId = padId;
    Controller::name = name;
    Controller::axisThresholdH = 0.5;
    Controller::axisThresholdV = 0.5;
    Controller::axisAbsoluteH = 0;
    Controller::axisAbsoluteV = 0;
    Controller::axisChangedH = false;
    Controller::axisChangedV = false;
}

InputNormalization Controller::getNormalizedInputs()
{
    InputNormalization keys = InputNormalization();

    // @TODO: get axis working like "pressed"
    _axisRecalculate();

    if (
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_UP) ||
        _axisJustTilted("up"))
    {
        cout << "[" + std::to_string(padId) + "]DIR_V += 1" << endl;
        keys.DIR_V += 1;
    }
    if (
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_DOWN) ||
        _axisJustTilted("down"))
    {
        cout << "[" + std::to_string(padId) + "]DIR_V -= 1" << endl;
        keys.DIR_V -= 1;
    }

    if (
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
        _axisJustTilted("left"))
    {
        cout << "[" + std::to_string(padId) + "]DIR_H -= 1" << endl;
        keys.DIR_H -= 1;
    }
    if (
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
        _axisJustTilted("right"))
    {
        cout << "[" + std::to_string(padId) + "]DIR_H += 1" << endl;
        keys.DIR_H += 1;
    }
    // Y/Triangle
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_UP))
    {
        cout << "[" + std::to_string(padId) + "]FACE_UP = true" << endl;
        keys.FACE_UP = true;
    }
    // A/Cross
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
    {
        cout << "[" + std::to_string(padId) + "]FACE_DOWN = true" << endl;
        keys.FACE_DOWN = true;
    }
    // X/Square
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
    {
        cout << "[" + std::to_string(padId) + "]FACE_LEFT = true" << endl;
        keys.FACE_LEFT = true;
    }
    // B/Circle
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
    {
        cout << "[" + std::to_string(padId) + "]FACE_RIGHT = true" << endl;
        keys.FACE_RIGHT = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_1))
    {
        cout << "[" + std::to_string(padId) + "]SHOULDER_L = true" << endl;
        keys.SHOULDER_L = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
    {
        cout << "[" + std::to_string(padId) + "]SHOULDER_R = true" << endl;
        keys.SHOULDER_R = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_2))
    {
        cout << "[" + std::to_string(padId) + "]TRIGGER_L = true" << endl;
        keys.TRIGGER_L = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_2))
    {
        cout << "[" + std::to_string(padId) + "]TRIGGER_R = true" << endl;
        keys.TRIGGER_R = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE_LEFT))
    {
        cout << "[" + std::to_string(padId) + "]SELECT = true" << endl;
        keys.SELECT = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE))
    {
        cout << "[" + std::to_string(padId) + "]HOME = true" << endl;
        keys.HOME = true;
    }
    if (IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE_RIGHT))
    {
        cout << "[" + std::to_string(padId) + "]START = true" << endl;
        keys.START = true;
    }

    return keys;
}

void Controller::_axisRecalculate()
{
    float axisH = GetGamepadAxisMovement(padId, GAMEPAD_AXIS_LEFT_X);
    float axisV = GetGamepadAxisMovement(padId, GAMEPAD_AXIS_LEFT_Y);

    if (axisH < -axisThresholdH)
    {
        axisChangedH = (axisAbsoluteH != -1);
        axisAbsoluteH = -1;
    }
    else if (axisH > axisThresholdH)
    {
        axisChangedH = (axisAbsoluteH != 1);
        axisAbsoluteH = 1;
    }
    if (axisV < -axisThresholdV)
    {
        axisChangedV = (axisAbsoluteV != -1);
        axisAbsoluteV = -1;
    }
    else if (axisV > axisThresholdV)
    {
        axisChangedV = (axisAbsoluteV != 1);
        axisAbsoluteV = 1;
    }
}

bool Controller::_axisJustTilted(std::string direction)
{
    if (direction == "up")
        return (axisAbsoluteV < 0 && axisChangedV);
    if (direction == "down")
        return (axisAbsoluteV < 0 && axisChangedV);
    if (direction == "left")
        return (axisAbsoluteH < 0 && axisChangedH);
    if (direction == "right")
        return (axisAbsoluteH < 0 && axisChangedH);
}