#include "controller.hpp"

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

NormalizedInput Controller::getNormalizedInputs()
{
    NormalizedInput keys = NormalizedInput();

    _axisRecalculate();

    if (_IsInputDown("up") || _IsAxisTilted("up"))
    {
        // std::cout << "[" + std::to_string(padId) + "]DIR_V += 1" << std::endl;
        keys.DIR_V += 1;
    }
    if (_IsInputDown("down") || _IsAxisTilted("down"))
    {
        // std::cout << "[" + std::to_string(padId) + "]DIR_V -= 1" << std::endl;
        keys.DIR_V -= 1;
    }

    if (_IsInputDown("left") || _IsAxisTilted("left"))
    {
        // std::cout << "[" + std::to_string(padId) + "]DIR_H -= 1" << std::endl;
        keys.DIR_H -= 1;
    }
    if (_IsInputDown("right") || _IsAxisTilted("right"))
    {
        // std::cout << "[" + std::to_string(padId) + "]DIR_H += 1" << std::endl;
        keys.DIR_H += 1;
    }
    if (_IsInputPressed("face_up"))
    {
        // std::cout << "[" + std::to_string(padId) + "]FACE_UP = true" << std::endl;
        keys.FACE_UP = true;
    }
    if (_IsInputPressed("face_down"))
    {
        // std::cout << "[" + std::to_string(padId) + "]FACE_DOWN = true" << std::endl;
        keys.FACE_DOWN = true;
    }
    if (_IsInputPressed("face_left"))
    {
        // std::cout << "[" + std::to_string(padId) + "]FACE_LEFT = true" << std::endl;
        keys.FACE_LEFT = true;
    }
    if (_IsInputPressed("face_right"))
    {
        // std::cout << "[" + std::to_string(padId) + "]FACE_RIGHT = true" << std::endl;
        keys.FACE_RIGHT = true;
    }
    if (_IsInputPressed("shoulder_left"))
    {
        // std::cout << "[" + std::to_string(padId) + "]SHOULDER_L = true" << std::endl;
        keys.SHOULDER_L = true;
    }
    if (_IsInputPressed("shoulder_right"))
    {
        // std::cout << "[" + std::to_string(padId) + "]SHOULDER_R = true" << std::endl;
        keys.SHOULDER_R = true;
    }
    if (_IsInputPressed("trigger_left"))
    {
        // std::cout << "[" + std::to_string(padId) + "]TRIGGER_L = true" << std::endl;
        keys.TRIGGER_L = true;
    }
    if (_IsInputPressed("trigger_right"))
    {
        // std::cout << "[" + std::to_string(padId) + "]TRIGGER_R = true" << std::endl;
        keys.TRIGGER_R = true;
    }
    if (_IsInputPressed("back"))
    {
        // std::cout << "[" + std::to_string(padId) + "]BACK = true" << std::endl;
        keys.BACK = true;
    }
    if (_IsInputPressed("home"))
    {
        // std::cout << "[" + std::to_string(padId) + "]HOME = true" << std::endl;
        keys.HOME = true;
    }
    if (_IsInputPressed("start"))
    {
        // std::cout << "[" + std::to_string(padId) + "]START = true" << std::endl;
        keys.START = true;
    }

    return keys;
}

bool Controller::_IsInputDown(std::string btn)
{
    if (btn == "up")
        return (name == "Keyboard") ? IsKeyDown(KEY_W) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_UP);
    if (btn == "down")
        return (name == "Keyboard") ? IsKeyDown(KEY_S) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    if (btn == "left")
        return (name == "Keyboard") ? IsKeyDown(KEY_A) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    if (btn == "right")
        return (name == "Keyboard") ? IsKeyDown(KEY_D) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    if (btn == "face_up")
        return (name == "Keyboard") ? IsKeyDown(KEY_U) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_FACE_UP);
    if (btn == "face_down")
        return (name == "Keyboard") ? IsKeyDown(KEY_H) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    if (btn == "face_left")
        return (name == "Keyboard") ? IsKeyDown(KEY_Y) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
    if (btn == "face_right")
        return (name == "Keyboard") ? IsKeyDown(KEY_J) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
    if (btn == "shoulder_left")
        return (name == "Keyboard") ? IsKeyDown(KEY_O) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_1);
    if (btn == "shoulder_right")
        return (name == "Keyboard") ? IsKeyDown(KEY_I) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
    if (btn == "trigger_left")
        return (name == "Keyboard") ? IsKeyDown(KEY_L) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_2);
    if (btn == "trigger_right")
        return (name == "Keyboard") ? IsKeyDown(KEY_K) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_2);
    if (btn == "back")
        return (name == "Keyboard") ? IsKeyDown(KEY_BACK) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_MIDDLE_LEFT);
    if (btn == "home")
        return (name == "Keyboard") ? IsKeyDown(KEY_ESCAPE) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_MIDDLE);
    if (btn == "start")
        return (name == "Keyboard") ? IsKeyDown(KEY_ENTER) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_MIDDLE_RIGHT);
    return false;
}

bool Controller::_IsInputPressed(std::string btn)
{
    // @TODO: Filter these checked keys/buttons through a map
    // Map should be separated by player side and device
    if (btn == "up")
        return (name == "Keyboard") ? IsKeyPressed(KEY_W) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_UP);
    if (btn == "down")
        return (name == "Keyboard") ? IsKeyPressed(KEY_S) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    if (btn == "left")
        return (name == "Keyboard") ? IsKeyPressed(KEY_A) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    if (btn == "right")
        return (name == "Keyboard") ? IsKeyPressed(KEY_D) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    if (btn == "face_up")
        return (name == "Keyboard") ? IsKeyPressed(KEY_U) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_UP);
    if (btn == "face_down")
        return (name == "Keyboard") ? IsKeyPressed(KEY_H) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    if (btn == "face_left")
        return (name == "Keyboard") ? IsKeyPressed(KEY_Y) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
    if (btn == "face_right")
        return (name == "Keyboard") ? IsKeyPressed(KEY_J) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
    if (btn == "shoulder_left")
        return (name == "Keyboard") ? IsKeyPressed(KEY_O) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_1);
    if (btn == "shoulder_right")
        return (name == "Keyboard") ? IsKeyPressed(KEY_I) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
    if (btn == "trigger_left")
        return (name == "Keyboard") ? IsKeyPressed(KEY_L) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_2);
    if (btn == "trigger_right")
        return (name == "Keyboard") ? IsKeyPressed(KEY_K) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_2);
    if (btn == "back")
        return (name == "Keyboard") ? IsKeyPressed(KEY_BACK) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE_LEFT);
    if (btn == "home")
        return (name == "Keyboard") ? IsKeyPressed(KEY_ESCAPE) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE);
    if (btn == "start")
        return (name == "Keyboard") ? IsKeyPressed(KEY_ENTER) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE_RIGHT);
    return false;
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

bool Controller::_IsAxisTilted(std::string direction)
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

bool Controller::_IsAxisJustTilted(std::string direction)
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

void Controller::setPlayer(int player)
{
    Controller::player = player;
}
