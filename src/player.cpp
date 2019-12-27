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

void PlayerController::init(PlayerData *pd, PlayerBoxes *pb, PlayerProjectiles *pp)
{
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
    // PlayerInput playerInput = PlayerInput();
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
};

void PlayerController::setInputs(PlayerInput playerInput)
{
    playerData->input = playerInput;
}

void PlayerController::processInputs()
{
    if (_isGrounded())
    {
        crouched = false;

        if (hasFlag(playerData->input, PlayerInput::DIR_ANY_UP))
        {
            playerData->physical.velocityV = playerData->physical.jumpSpeed;
        }
        else if (hasFlag(playerData->input, PlayerInput::DIR_ANY_DOWN))
        {
            crouched = true;
            playerData->physical.velocityH = 0;
        }

        if (!_isCrouched())
        {
            int directionSign = (hasFlag(playerData->input, PlayerInput::DIR_LEFT) ? -1 : 1);

            if (hasFlag(playerData->input, PlayerInput::DIR_TOWARD))
            {
                playerData->physical.velocityH = 10 * directionSign;
            }
            else if (hasFlag(playerData->input, PlayerInput::DIR_BACK))
            {
                playerData->physical.velocityH = 6 * directionSign;
            }
            else
            {
                playerData->physical.velocityH = 0;
            }
        }
    }
}

void PlayerController::updateBoxes()
{
    int crouchModifierA = _isCrouched() ? 2 : 1;
    int crouchModifierB = !_isCrouched() ? 2 : 1;
    playerBoxes->pushBoxArray[0].updateBox(playerData->physical.x, playerData->physical.y + (100 / crouchModifierA), 100, 100 * crouchModifierB);
}

void PlayerController::checkCollisions(PlayerController *otherPlayer)
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

        int maxPush = 10;
        int distance = maxPush > intersection.x / 2 ? intersection.x / 2 : maxPush;
        if (playerData->physical.velocityH != 0 || otherPlayer->playerData->physical.velocityH != 0)
        {
            int selfVelocityH = std::abs(playerData->physical.velocityH);
            int otherVelocityH = std::abs(otherPlayer->playerData->physical.velocityH);
            int highestVelocity = std::max<int>(selfVelocityH, otherVelocityH);

            float selfPercentageOfHighest = selfVelocityH == 0 ? 0.f : (float)highestVelocity / (float)selfVelocityH;
            float otherPercentageOfHighest = otherVelocityH == 0 ? 0.f : (float)highestVelocity / (float)otherVelocityH;

            float multiplier = otherPercentageOfHighest - selfPercentageOfHighest;

            distance += distance * multiplier;
        }

        playerData->physical.pushback = distance * dirModifier;
    }

    /** @TODO: collisions
     * Push to respective sides of colliding
     * e.g., p1.x = 1 and p2.x = 0, p1 should be pushed to right side
     * This is regardless of grounded or air positioning
     *
     * But what if they occupy the same space, the same X coord? This situation would happen in the corner often
     * To start, if they're facing different directions, push one towards the direction they're facing
     * There should be two different kinds of "facing": the original face set based on player side, and another face that stays static when the player jumps
     * This is so special moves don't swap direction when jumping
     * All call these:
     * - face
     * - actionFace
     *
     * Pushback should be exchanged based on h.speed (i.e., the faster player gives the most push back)
     *
     * Calculate the initial pushback required to move a player (shared or not)
     * After that, if there's no room remaining for a player if they're in the corner, apply the remainder to the opponent
     */
}

void PlayerController::updatePhysics()
{
    _applyForces();
    _recalcForces();
}

void PlayerController::_applyForces()
{
    // if knockback value is non-zero, apply knockback
    if (playerData->physical.knockback != 0)
    {
    }
    // if pushback value is present, apply pushback
    else if (playerData->physical.pushback != 0)
    {
        playerData->physical.x += playerData->physical.pushback;
    }
    else
    {
        playerData->physical.x += playerData->physical.velocityH;
    }

    playerData->physical.y += playerData->physical.velocityV;
}

void PlayerController::_recalcForces()
{
    if (playerData->physical.pushback != 0)
    {
        int sign = playerData->physical.pushback < 0 ? 1 : -1;

        int decrement = 5 * sign;
        if (std::abs(decrement) > std::abs(playerData->physical.pushback))
        {
            decrement = playerData->physical.pushback * -1;
        }

        playerData->physical.pushback += decrement;
    }

    if (!_isGrounded())
    {
        playerData->physical.velocityV -= playerData->physical.gravity / playerData->physical.drag;
        if (playerData->physical.velocityV < -playerData->physical.jumpSpeed)
        {
            playerData->physical.velocityV = playerData->physical.jumpSpeed;
        }
    }
    else
    {
        playerData->physical.velocityV = 0;
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
