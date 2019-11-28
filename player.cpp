#include "player.hpp"

PlayerController::PlayerController()
{
    controllerId = -2;
    color = RED;
}

void PlayerController::update()
{
}

void PlayerController::render()
{
    DrawCube({0, 0, 0}, 1.f, 1.f, 0.f, RED);
}

void PlayerController::normalizedToPlayerInput(NormalizedInput normInput)
{
    PlayerInput playerInput = PlayerInput();

    if (normInput.DIR_H == -1)
        setFlag(playerInput, PlayerInput::DIR_BACK);
    if (normInput.DIR_H == 1)
        setFlag(playerInput, PlayerInput::DIR_TOWARD);
    if (normInput.DIR_V == -1)
        setFlag(playerInput, PlayerInput::DIR_DOWN);
    if (normInput.DIR_V == 1)
        setFlag(playerInput, PlayerInput::DIR_UP);
    if (normInput.FACE_UP)
        setFlag(playerInput, PlayerInput::BTN_STRONG);
    if (normInput.FACE_DOWN)
        setFlag(playerInput, PlayerInput::BTN_SHORT);
    if (normInput.FACE_LEFT)
        setFlag(playerInput, PlayerInput::BTN_JAB);
    if (normInput.FACE_RIGHT)
        setFlag(playerInput, PlayerInput::BTN_FORWARD);
    if (normInput.SHOULDER_L)
        setFlag(playerInput, PlayerInput::BTN_MACRO1);
    if (normInput.SHOULDER_R)
        setFlag(playerInput, PlayerInput::BTN_FIERCE);
    if (normInput.TRIGGER_L)
        setFlag(playerInput, PlayerInput::BTN_MACRO2);
    if (normInput.TRIGGER_R)
        setFlag(playerInput, PlayerInput::BTN_ROUNDHOUSE);
    // if (normInput.BACK)
    //     setFlag(playerInput, PlayerInput::BACK);
    // if (normInput.START)
    //     setFlag(playerInput, PlayerInput::START);
    // if (normInput.HOME)
    //     setFlag(playerInput, PlayerInput::HOME);

    setInputs(playerInput);
};

void PlayerController::setInputs(PlayerInput playerInput)
{
    pd.input = playerInput;
    // std::cout << std::to_string((int)playerInput) << std::endl;
}
