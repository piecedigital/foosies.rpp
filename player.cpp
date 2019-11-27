#include "player.h"

PlayerController::PlayerController()
{
    pd.input = PlayerInput();
    pd.transform = Transform();
    pd.intTranslation = Transform3();

    ggpoPlayer = GGPOPlayer();
}

void PlayerController::update()
{
}

void PlayerController::render()
{
}

void PlayerController::normalizedToPlayerInput(NormalizedInput normInput)
{
    PlayerInput playerInput = PlayerInput();

    if (normInput.DIR_H == -1)
        setFlag(&playerInput, PlayerInput::DIR_BACK);
    if (normInput.DIR_H == 1)
        setFlag(&playerInput, PlayerInput::DIR_TOWARD);
    if (normInput.DIR_V == -1)
        setFlag(&playerInput, PlayerInput::DIR_DOWN);
    if (normInput.DIR_V == 1)
        setFlag(&playerInput, PlayerInput::DIR_UP);

    if (normInput.FACE_UP)
        true;
    if (normInput.FACE_DOWN)
        true;
    if (normInput.FACE_LEFT)
        true;
    if (normInput.FACE_RIGHT)
        true;
    if (normInput.SHOULDER_L)
        true;
    if (normInput.SHOULDER_R)
        true;
    if (normInput.TRIGGER_L)
        true;
    if (normInput.TRIGGER_R)
        true;
    if (normInput.BACK)
        true;
    if (normInput.START)
        true;
    if (normInput.HOME)
        true;

    setInputs(playerInput);
};

void PlayerController::setInputs(PlayerInput playerInput)
{
    pd.input = playerInput;
}
