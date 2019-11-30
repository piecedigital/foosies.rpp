#include "player.hpp"

PlayerController::PlayerController()
{
    controllerId = -2;
    color = RED;
}

void PlayerController::update()
{

    if (hasFlag(pd.input, PlayerInput::DIR_TOWARD))
    {
        pd.physical.velocityH = 100 * pd.face;
    }
    else if (hasFlag(pd.input, PlayerInput::DIR_BACK))
    {
        pd.physical.velocityH = 100 * (pd.face * -1);
    }
    else
    {
        pd.physical.velocityH = 0;
    }

    pd.physical.x += pd.physical.velocityH / pd.physical.drag;
}

void PlayerController::render()
{
    _convertTranslation();
    DrawCube(pd.transform.translation, 1.f, 1.f, 0.f, color);
}

void PlayerController::normalizedToPlayerInput(NormalizedInput normInput)
{
    PlayerInput playerInput = PlayerInput();

    if (normInput.DIR_H == -1)
        setFlag(playerInput, pd.face == 1 ? PlayerInput::DIR_BACK
                : PlayerInput::DIR_TOWARD);
    if (normInput.DIR_H == 1)
        setFlag(playerInput, pd.face == 1 ? PlayerInput::DIR_TOWARD
                : PlayerInput::DIR_BACK);
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
}

void PlayerController::_convertTranslation()
{
    pd.transform.translation = Vector3{
        ((float)pd.physical.x) / 100,
        ((float)pd.physical.y) / 100,
        ((float)pd.physical.z) / 100,
    };
}
