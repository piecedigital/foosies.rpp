#include "player.hpp"

void PlayerController::init(Player *player, PlayerData *pd, PlayerBoxes *pb)
{
    player->controllerId = -2;
    player->playerData = pd;
    player->playerBoxes = pb;

    player->charMan[0].playerData = &player->playerData;
    player->charMan[0].playerBoxes = &player->playerBoxes;

    player->playerBoxes->pushBoxSize = 1;
    player->playerBoxes->grabBoxesSize = 0;
    player->playerBoxes->hitBoxesSize = 0;
    player->playerBoxes->hurtBoxesSize = 0;
    player->playerBoxes->proximityBoxesSize = 0;

    player->playerBoxes->pushBoxArray = new Box[player->playerBoxes->pushBoxSize];
    player->playerBoxes->grabBoxesArray = new Box[player->playerBoxes->grabBoxesSize];
    player->playerBoxes->hitBoxesArray = new Box[player->playerBoxes->hitBoxesSize];
    player->playerBoxes->hurtBoxesArray = new Box[player->playerBoxes->hurtBoxesSize];
    player->playerBoxes->proximityBoxesArray = new Box[player->playerBoxes->proximityBoxesSize];

    player->playerBoxes->pushBoxArray[0].type = BoxType::BOX_PUSH;
    player->playerBoxes->pushBoxArray[0].updateBoxShape(
        player->playerData->transform.translation.x,
        player->playerData->transform.translation.y + 1.f,
        1.f,
        2.f
    );
}

void PlayerController::unload(Player *player)
{
    player->playerData = NULL;
}

void PlayerController::update(Player *player, Player &otherPlayer)
{
    player->playerData->sideFace = (otherPlayer.playerData->physical.x < player->playerData->physical.x) ? -1 : 1;
    if (_isGrounded())
    {
        player->playerData->actionFace = (otherPlayer.playerData->physical.x < player->playerData->physical.x) ? -1 : 1;
    }

    if (player->playerBoxes->pushBoxArray[0].isColliding(otherPlayer.playerBoxes->pushBoxArray[0]))
    {
        int dirModifier = 0;
        if (otherPlayer.playerData->physical.x == player->playerData->physical.x)
        {
            dirModifier = otherPlayer.playerData->sideFace;
        }
        else if (otherPlayer.playerData->physical.x > player->playerData->physical.x)
        {
            dirModifier = 1;
        }
        else
        {
            dirModifier = -1;
        }

        otherPlayer.playerData->physical.velocityH = 10 * dirModifier;
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
}

void PlayerController::_applyForces()
{
    playerData->physical.x += playerData->physical.velocityH;
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
