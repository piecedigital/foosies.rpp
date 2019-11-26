
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

Controller::Controller()
{
    Controller::padId = -1;
    Controller::name = "Keyboard";
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
        (name == "Keyboard" && _IsKeyDown(KEY_W)) ||
        IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_UP) ||
        _axisTilted("up"))
    {
        cout << "[" + std::to_string(padId) + "]DIR_V += 1" << endl;
        keys.DIR_V += 1;
    }
    if (
        (name == "Keyboard" && _IsKeyDown(KEY_S)) ||
        IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_DOWN) ||
        _axisTilted("down"))
    {
        cout << "[" + std::to_string(padId) + "]DIR_V -= 1" << endl;
        keys.DIR_V -= 1;
    }

    if (
        (name == "Keyboard" && _IsKeyDown(KEY_A)) ||
        IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
        _axisTilted("left"))
    {
        cout << "[" + std::to_string(padId) + "]DIR_H -= 1" << endl;
        keys.DIR_H -= 1;
    }
    if (
        (name == "Keyboard" && _IsKeyDown(KEY_D)) ||
        IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
        _axisTilted("right"))
    {
        cout << "[" + std::to_string(padId) + "]DIR_H += 1" << endl;
        keys.DIR_H += 1;
    }
    // Y/Triangle
    if (
        (name == "Keyboard" && _IsKeyPressed(KEY_U)) ||
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_UP))
    {
        cout << "[" + std::to_string(padId) + "]FACE_UP = true" << endl;
        keys.FACE_UP = true;
    }
    // A/Cross
    if (
        (name == "Keyboard" && _IsKeyPressed(KEY_H)) ||
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
    {
        cout << "[" + std::to_string(padId) + "]FACE_DOWN = true" << endl;
        keys.FACE_DOWN = true;
    }
    // X/Square
    if (
        (name == "Keyboard" && _IsKeyPressed(KEY_Y)) ||
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
    {
        cout << "[" + std::to_string(padId) + "]FACE_LEFT = true" << endl;
        keys.FACE_LEFT = true;
    }
    // B/Circle
    if (
        (name == "Keyboard" && _IsKeyPressed(KEY_J)) ||
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
    {
        cout << "[" + std::to_string(padId) + "]FACE_RIGHT = true" << endl;
        keys.FACE_RIGHT = true;
    }
    if (
        (name == "Keyboard" && _IsKeyPressed(KEY_O)) ||
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_1))
    {
        cout << "[" + std::to_string(padId) + "]SHOULDER_L = true" << endl;
        keys.SHOULDER_L = true;
    }
    if (
        (name == "Keyboard" && _IsKeyPressed(KEY_I)) ||
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_1))
    {
        cout << "[" + std::to_string(padId) + "]SHOULDER_R = true" << endl;
        keys.SHOULDER_R = true;
    }
    if (
        (name == "Keyboard" && _IsKeyPressed(KEY_L)) ||
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_2))
    {
        cout << "[" + std::to_string(padId) + "]TRIGGER_L = true" << endl;
        keys.TRIGGER_L = true;
    }
    if (
        (name == "Keyboard" && _IsKeyPressed(KEY_K)) ||
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_2))
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
    if (
        (name == "Keyboard" && _IsKeyPressed(KEY_ESCAPE)) ||
        IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE_RIGHT))
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

bool Controller::_IsKeyDown(int key)
{
    // @TODO: filter through keyboard mapping
    return IsKeyDown(key);
};

bool Controller::_IsKeyPressed(int key)
{
    // @TODO: filter through keyboard mapping
    return IsKeyPressed(key);
};

bool Controller::_axisTilted(std::string direction)
{
    if (direction == "up")
        return (axisAbsoluteV < 0);
    if (direction == "down")
        return (axisAbsoluteV < 0);
    if (direction == "left")
        return (axisAbsoluteH < 0);
    if (direction == "right")
        return (axisAbsoluteH < 0);
    return false;
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
    return false;
}