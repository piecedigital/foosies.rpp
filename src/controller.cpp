#include "controller.hpp"

Controller::Controller(unsigned int padId, ControllerType type, const char *name)
{
    this->padId = padId;
    this->name = name;
    this->controllerType = type;
    this->axisThresholdH = 0.5;
    this->axisThresholdV = 0.5;
    this->axisAbsoluteH = 0;
    this->axisAbsoluteV = 0;
    this->axisChangedH = false;
    this->axisChangedV = false;
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

Controller::~Controller()
{
    name = NULL;
}

void Controller::pollNormalizedInputs()
{
    _resetInputs();

    _axisRecalculate();

    if (_IsInputDown("up") || _IsAxisTilted("up"))
    {
        inputs.DIR_V += 1;
    }
    if (_IsInputDown("down") || _IsAxisTilted("down"))
    {
        inputs.DIR_V -= 1;
    }

    if (_IsInputDown("left") || _IsAxisTilted("left"))
    {
        inputs.DIR_H -= 1;
    }
    if (_IsInputDown("right") || _IsAxisTilted("right"))
    {
        inputs.DIR_H += 1;
    }
    if (_IsInputPressed("face_up"))
    {
        buttonPressed = true;
        inputs.FACE_UP = true;
    }
    if (_IsInputPressed("face_down"))
    {
        buttonPressed = true;
        inputs.FACE_DOWN = true;
    }
    if (_IsInputPressed("face_left"))
    {
        buttonPressed = true;
        inputs.FACE_LEFT = true;
    }
    if (_IsInputPressed("face_right"))
    {
        buttonPressed = true;
        inputs.FACE_RIGHT = true;
    }
    if (_IsInputPressed("shoulder_left"))
    {
        buttonPressed = true;
        inputs.SHOULDER_L = true;
    }
    if (_IsInputPressed("shoulder_right"))
    {
        buttonPressed = true;
        inputs.SHOULDER_R = true;
    }
    if (_IsInputPressed("trigger_left"))
    {
        buttonPressed = true;
        inputs.TRIGGER_L = true;
    }
    if (_IsInputPressed("trigger_right"))
    {
        buttonPressed = true;
        inputs.TRIGGER_R = true;
    }
    if (_IsInputPressed("back"))
    {
        buttonPressed = true;
        inputs.BACK = true;
    }
    if (_IsInputPressed("home"))
    {
        buttonPressed = true;
        inputs.HOME = true;
    }
    if (_IsInputPressed("start"))
    {
        buttonPressed = true;
        inputs.START = true;
    }
}

bool Controller::_IsInputDown(std::string btn)
{
    if (btn == "up")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_W) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_UP);
    if (btn == "down")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_S) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    if (btn == "left")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_A) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    if (btn == "right")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_D) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    if (btn == "face_up")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_U) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_FACE_UP);
    if (btn == "face_down")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_H) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    if (btn == "face_left")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_Y) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
    if (btn == "face_right")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_J) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
    if (btn == "shoulder_left")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_O) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_1);
    if (btn == "shoulder_right")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_I) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
    if (btn == "trigger_left")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_L) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_2);
    if (btn == "trigger_right")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_K) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_2);
    if (btn == "back")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_BACK) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_MIDDLE_LEFT);
    if (btn == "home")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_ESCAPE) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_MIDDLE);
    if (btn == "start")
        return (controllerType == ControllerType::keyboard) ? IsKeyDown(KEY_ENTER) : IsGamepadButtonDown(padId, GAMEPAD_BUTTON_MIDDLE_RIGHT);
    return false;
}

bool Controller::_IsInputPressed(std::string btn)
{
    // @TODO: Filter these checked keys/buttons through a map
    // Map should be separated by player side and device
    if (btn == "up")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_W) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_UP);
    if (btn == "down")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_S) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    if (btn == "left")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_A) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_LEFT);
    if (btn == "right")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_D) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_FACE_RIGHT);
    if (btn == "face_up")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_U) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_UP);
    if (btn == "face_down")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_H) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    if (btn == "face_left")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_Y) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
    if (btn == "face_right")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_J) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
    if (btn == "shoulder_left")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_O) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_1);
    if (btn == "shoulder_right")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_I) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);
    if (btn == "trigger_left")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_L) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_LEFT_TRIGGER_2);
    if (btn == "trigger_right")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_K) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_RIGHT_TRIGGER_2);
    if (btn == "back")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_BACK) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE_LEFT);
    if (btn == "home")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_ESCAPE) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE);
    if (btn == "start")
        return (controllerType == ControllerType::keyboard) ? IsKeyPressed(KEY_ENTER) : IsGamepadButtonPressed(padId, GAMEPAD_BUTTON_MIDDLE_RIGHT);
    return false;
}

bool Controller::_IsAxisTilted(std::string direction)
{
    if (direction == "up")
        return (axisAbsoluteV < -axisThresholdV);
    if (direction == "down")
        return (axisAbsoluteV > axisThresholdV);
    if (direction == "left")
        return (axisAbsoluteH < -axisThresholdH);
    if (direction == "right")
        return (axisAbsoluteH > axisThresholdH);
    return false;
}

bool Controller::_IsAxisJustTilted(std::string direction)
{
    if (direction == "up")
        return (axisAbsoluteV < -axisThresholdV && axisChangedV);
    if (direction == "down")
        return (axisAbsoluteV > axisThresholdV && axisChangedV);
    if (direction == "left")
        return (axisAbsoluteH < -axisThresholdH && axisChangedH);
    if (direction == "right")
        return (axisAbsoluteH > axisThresholdH && axisChangedH);
    return false;
}

void Controller::_resetInputs()
{
    buttonPressed = false;
    inputs.DIR_H = 0;
    inputs.DIR_V = 0;
    inputs.FACE_UP = false;
    inputs.FACE_DOWN = false;
    inputs.FACE_LEFT = false;
    inputs.FACE_RIGHT = false;
    inputs.SHOULDER_L = false;
    inputs.SHOULDER_R = false;
    inputs.TRIGGER_L = false;
    inputs.TRIGGER_R = false;
    inputs.BACK = false;
    inputs.START = false;
    inputs.HOME = false;
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
    else
    {
        axisChangedH = (axisAbsoluteH != 0);
        axisAbsoluteH = 0;
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
    else
    {
        axisChangedV = (axisAbsoluteV != 0);
        axisAbsoluteV = 0;
    }

}
