#include <algorithm>
#include "player.hpp"

PlayerController::PlayerController()
{
    controllerId = -2;
}

PlayerController::~PlayerController()
{
    playerData = NULL;
}

void PlayerController::init(PlayerInput *ih, PlayerData *pd, PlayerBoxes *pb, PlayerProjectiles *pp)
{
    inputHistory = ih;
    playerData = pd;
    playerBoxes = pb;
    playerProjectiles = pp;

    charMan[0].playerData = &playerData;
    charMan[0].playerBoxes = &playerBoxes;

    playerBoxes->pushBoxSize = 1;
    playerBoxes->grabBoxesSize = 0;
    playerBoxes->hitBoxesSize = 0;
    playerBoxes->hurtBoxesSize = 0;
    playerBoxes->proximityBoxesSize = 0;

    playerBoxes->pushBoxArray = new Box[playerBoxes->pushBoxSize];
    playerBoxes->grabBoxesArray = new Box[playerBoxes->grabBoxesSize];
    playerBoxes->hitBoxesArray = new Box[playerBoxes->hitBoxesSize];
    playerBoxes->hurtBoxesArray = new Box[playerBoxes->hurtBoxesSize];
    playerBoxes->proximityBoxesArray = new Box[playerBoxes->proximityBoxesSize];

    playerBoxes->pushBoxArray[0].type = BoxType::BOX_PUSH;
    playerBoxes->pushBoxArray[0].updateBox(
        playerData->physical.x,
        playerData->physical.y + 100,
        100,
        200
    );

    playerProjectiles->projectilesSize = 0;
    playerProjectiles->projectilesArray = new Box[playerProjectiles->projectilesSize];
}

void PlayerController::updateFacing(PlayerController *otherPlayer)
{
    playerData->sideFace = (otherPlayer->playerData->physical.x < playerData->physical.x) ? -1
        : (otherPlayer->playerData->physical.x > playerData->physical.x) ? 1
        : playerData->sideFace;

    if (_isGrounded())
    {
        playerData->actionFace = (otherPlayer->playerData->physical.x < playerData->physical.x) ? -1
            : (otherPlayer->playerData->physical.x > playerData->physical.x) ? 1
            : playerData->sideFace;
    }
}

void PlayerController::normalizedToPlayerInput(NormalizedInput normInput)
{
    PlayerInput *playerInput = &playerData->input;
    *playerInput = PlayerInput::NONE;

    if (normInput.DIR_H == -1)
    {
        setFlag(*playerInput, PlayerInput::DIR_LEFT);
        if (playerData->actionFace == 1)
        {
            setFlag(*playerInput, PlayerInput::DIR_BACK);
            setFlag(*playerInput, PlayerInput::DIR_ANY_BACK);
        }
        else
        {
            setFlag(*playerInput, PlayerInput::DIR_TOWARD);
            setFlag(*playerInput, PlayerInput::DIR_ANY_TOWARD);
        }
    }
    if (normInput.DIR_H == 1)
    {
        setFlag(*playerInput, PlayerInput::DIR_RIGHT);
        if (playerData->actionFace == 1)
        {
            setFlag(*playerInput, PlayerInput::DIR_TOWARD);
            setFlag(*playerInput, PlayerInput::DIR_ANY_TOWARD);
        }
        else
        {
            setFlag(*playerInput, PlayerInput::DIR_BACK);
            setFlag(*playerInput, PlayerInput::DIR_ANY_BACK);
        }
    }
    if (normInput.DIR_V == -1)
    {
        setFlag(*playerInput, PlayerInput::DIR_DOWN);
        setFlag(*playerInput, PlayerInput::DIR_ANY_DOWN);
    }
    if (normInput.DIR_V == 1)
    {
        setFlag(*playerInput, PlayerInput::DIR_UP);
        setFlag(*playerInput, PlayerInput::DIR_ANY_UP);
    }
    if (normInput.FACE_UP)
        setFlag(*playerInput, PlayerInput::BTN_STRONG);
    if (normInput.FACE_DOWN)
        setFlag(*playerInput, PlayerInput::BTN_SHORT);
    if (normInput.FACE_LEFT)
        setFlag(*playerInput, PlayerInput::BTN_JAB);
    if (normInput.FACE_RIGHT)
        setFlag(*playerInput, PlayerInput::BTN_FORWARD);
    if (normInput.SHOULDER_L)
        setFlag(*playerInput, PlayerInput::BTN_MACRO1);
    if (normInput.SHOULDER_R)
        setFlag(*playerInput, PlayerInput::BTN_FIERCE);
    if (normInput.TRIGGER_L)
        setFlag(*playerInput, PlayerInput::BTN_MACRO2);
    if (normInput.TRIGGER_R)
        setFlag(*playerInput, PlayerInput::BTN_ROUNDHOUSE);
    // if (normInput.BACK)
    //     setFlag(*playerInput, PlayerInput::BACK);
    // if (normInput.START)
    //     setFlag(*playerInput, PlayerInput::START);
    // if (normInput.HOME)
    //     setFlag(*playerInput, PlayerInput::HOME);
    setInputs(*playerInput);
};

void PlayerController::setInputs(PlayerInput playerInput)
{
    playerData->input = playerInput;

    PlayerInput currentInput;
    PlayerInput newInput = playerInput;
    for (int i = 0; i < INPUT_HISTORY_MAX; i++)
    {
        currentInput = inputHistory[i];
        inputHistory[i] = newInput;
        newInput = currentInput;
    }
}

void PlayerController::processInputs()
{
    if (_isGrounded())
    {
        crouched = false;

        if (hasFlag(playerData->input, PlayerInput::DIR_ANY_UP))
        {
            playerData->physical.VSpeed = playerData->physical.jumpSpeed;
        }
        else if (hasFlag(playerData->input, PlayerInput::DIR_ANY_DOWN))
        {
            crouched = true;
            playerData->physical.HSpeed = 0;
        }

        if (!_isCrouched())
        {
            int directionSign = (hasFlag(playerData->input, PlayerInput::DIR_LEFT) ? -1 : 1);

            if (hasFlag(playerData->input, PlayerInput::DIR_TOWARD))
            {
                playerData->physical.HSpeed = 10 * directionSign;
            }
            else if (hasFlag(playerData->input, PlayerInput::DIR_BACK))
            {
                playerData->physical.HSpeed = 6 * directionSign;
            }
            else
            {
                playerData->physical.HSpeed = 0;
            }
        }
    }
}

void PlayerController::updateBoxes()
{
    int crouchModifier = _isCrouched() ? 2 : 1;
    playerBoxes->pushBoxArray[0].updateBox(
        playerData->physical.x,
        playerData->physical.y + ((charMan[0].bodyHeight / 2) / (crouchModifier)),
        charMan[0].bodyWidth,
        charMan[0].bodyHeight / crouchModifier);
}

void PlayerController::checkCollisions(PlayerController *otherPlayer, int stageHalfWidth)
{
    if (playerBoxes->pushBoxArray[0].isColliding(otherPlayer->playerBoxes->pushBoxArray[0]))
    {
        BoxIntersection intersection = playerBoxes->pushBoxArray[0].getIntersections(otherPlayer->playerBoxes->pushBoxArray[0], playerData->sideFace);

        int dirModifier = 0;
        if (otherPlayer->playerData->physical.x == playerData->physical.x)
        {
            dirModifier = playerData->sideFace;
        }
        else if (otherPlayer->playerData->physical.x > playerData->physical.x)
        {
            dirModifier = -1;
        }
        else
        {
            dirModifier = 1;
        }

        int maxPush = 20;
        int distance = maxPush > intersection.x / 2 ? intersection.x / 2 : maxPush;

        if (playerData->physical.HSpeed != 0 || otherPlayer->playerData->physical.HSpeed != 0)
        {
            int selfHSpeed = std::abs(playerData->physical.HSpeed);
            int otherHSpeed = std::abs(otherPlayer->playerData->physical.HSpeed);
            int highestSpeed = std::max<int>(selfHSpeed, otherHSpeed);

            float selfPercentageOfHighest = selfHSpeed == 0 ? 0.f : (float)highestSpeed / (float)selfHSpeed;
            float otherPercentageOfHighest = otherHSpeed == 0 ? 0.f : (float)highestSpeed / (float)otherHSpeed;

            float multiplier = otherPercentageOfHighest - selfPercentageOfHighest;

            distance += distance * multiplier;
        }

        playerData->physical.x += distance * dirModifier;

        if (
            (playerData->physical.x < -stageHalfWidth)
            // || (playerData->physical.x > stageHalfWidth)
        )
        {
            int distanceBack = (playerData->physical.x - -stageHalfWidth) * -1;

            playerData->physical.x = -stageHalfWidth;
            otherPlayer->playerData->physical.x += distanceBack;
        }
        else if (
            (playerData->physical.x > stageHalfWidth)
        )
        {
            int distanceBack = (playerData->physical.x - stageHalfWidth) * -1;

            playerData->physical.x = stageHalfWidth;
            otherPlayer->playerData->physical.x += distanceBack;
        }
    }
}

void PlayerController::calcPhysics(PlayerController *otherPlayer, int stageHalfWidth)
{
    playerData->physical.x += playerData->physical.HSpeed;

    // if knockback value is non-zero, apply knockback
    if (playerData->physical.knockback != 0)
    {
    }
    // if pushback value is present, apply pushback
    else if (playerData->physical.pushback != 0)
    {
        playerData->physical.x += playerData->physical.pushback;
    }

    // don't let player go beyond boundary
    if (playerData->physical.x < -stageHalfWidth)
    {
        playerData->physical.x = -stageHalfWidth;
    }
    else if (playerData->physical.x > stageHalfWidth)
    {
        playerData->physical.x = stageHalfWidth;
    }

    playerData->physical.y += playerData->physical.VSpeed;
}

void PlayerController::updatePhysics()
{
    // std::cout << "(" << controllerId << ")" << "PB: " << playerData->physical.pushback << std::endl;
    if (playerData->physical.pushback != 0)
    {
        int sign = playerData->physical.pushback < 0 ? 1 : -1;

        int decrement = 20 * sign;
        if (std::abs(decrement) > std::abs(playerData->physical.pushback))
        {
            decrement = playerData->physical.pushback * -1;
        }

        playerData->physical.pushback += decrement;
    }

    if (!_isGrounded())
    {
        playerData->physical.VSpeed -= playerData->physical.gravity / playerData->physical.drag;
        if (playerData->physical.VSpeed < -playerData->physical.jumpSpeed)
        {
            playerData->physical.VSpeed = playerData->physical.jumpSpeed;
        }
    }
    else
    {
        playerData->physical.VSpeed = 0;
        playerData->physical.y = 0;
    }
}

bool PlayerController::_isGrounded()
{
    return playerData->physical.y <= 0;
}

bool PlayerController::_isCrouched()
{
    return _isGrounded() && crouched;//hasFlag(playerData->input, PlayerInput::DIR_ANY_DOWN);
}
