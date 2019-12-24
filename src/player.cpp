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

void PlayerController::init(PlayerData *pd, PlayerBoxes *pb)
{
    playerData = pd;
    playerBoxes = pb;

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
}

void PlayerController::updateBoxes(PlayerController *otherPlayer)
{
    playerBoxes->pushBoxArray[0].updateBox(playerData->physical.x, playerData->physical.y + 100, 100, 200);
}

void PlayerController::checkCollisions(PlayerController *otherPlayer)
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

        int distance = 12 > intersection.x / 2 ? intersection.x / 2 : 12;
        if (playerData->physical.velocityH != 0 || otherPlayer->playerData->physical.velocityH != 0)
        {
            int selfVelocityH = std::abs(playerData->physical.velocityH);
            int otherVelocityH = std::abs(otherPlayer->playerData->physical.velocityH);
            int highestVelocity = std::max<int>(selfVelocityH, otherVelocityH);

            float selfPercentageOfHighest = selfVelocityH == 0 ? 0.f : (float)highestVelocity / (float)selfVelocityH;
            float otherPercentageOfHighest = otherVelocityH == 0 ? 0.f : (float)highestVelocity / (float)otherVelocityH;

            float multiplier = otherPercentageOfHighest - selfPercentageOfHighest;

            std::cout << "Distance before(" << controllerId <<"): " << distance << std::endl;
            distance += distance * multiplier;
            std::cout << "Distance After(" << controllerId <<"): " << distance << std::endl;
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

void PlayerController::updatePhysics(PlayerController *otherPlayer)
{
    _calcForces();
    _applyForces();
}

void PlayerController::normalizedToPlayerInput(NormalizedInput normInput)
{
    // PlayerInput playerInput = PlayerInput();
    PlayerInput *playerInput = &playerData->input;
    *playerInput = PlayerInput::NONE;

    if (normInput.DIR_H == -1)
    {
        setFlag(*playerInput, playerData->actionFace == 1 ? PlayerInput::DIR_BACK
                : PlayerInput::DIR_TOWARD);
        setFlag(*playerInput, PlayerInput::DIR_LEFT);
    }
    if (normInput.DIR_H == 1)
    {
        setFlag(*playerInput, playerData->actionFace == 1 ? PlayerInput::DIR_TOWARD
                : PlayerInput::DIR_BACK);
        setFlag(*playerInput, PlayerInput::DIR_RIGHT);
    }
    if (normInput.DIR_V == -1)
        setFlag(*playerInput, PlayerInput::DIR_DOWN);
    if (normInput.DIR_V == 1)
        setFlag(*playerInput, PlayerInput::DIR_UP);
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

void PlayerController::_calcForces()
{
    if (_isGrounded())
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

        if (hasFlag(playerData->input, PlayerInput::DIR_UP))
        {
            playerData->physical.velocityV = playerData->physical.jumpSpeed;
        }
    }

    if (playerData->physical.pushback != 0)
    {
        int sign = playerData->physical.pushback < 0 ? 1 : -1;

        int decrement = 2 * sign;
        if (std::abs(decrement) > std::abs(playerData->physical.pushback))
        {
            decrement = playerData->physical.pushback * -1;
        }

        playerData->physical.pushback += decrement;
    }
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
        playerData->physical.pushback -= 5 * (playerData->sideFace * -1);
    }
    else
    {
        playerData->physical.x += playerData->physical.velocityH;
    }

    playerData->physical.y += playerData->physical.velocityV;

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
