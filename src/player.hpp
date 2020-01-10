#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include "../bin/ggponet.h"
#include "globals.hpp"
#include "actions.hpp"
#include "character.hpp"
#include "entity.hpp"

class PlayerController : public Entity
{
public:
    bool crouched;
    GGPOPlayer ggpoPlayer;
    PlayerData *playerData;
    PlayerBoxes *playerBoxes;
    PlayerProjectiles *playerProjectiles;
    Character charMan[1];

    /**
     * The id of the controller passing inputs to the player
     * -1 is the default, meaning no controller
     * 0 is the keyboard, and 1+ is a gamepad
     */
    int controllerId = -1;
    PlayerInput *inputHistory;

    PlayerController();
    ~PlayerController();

    void init(PlayerInput *inputHistory, PlayerData *pd, PlayerBoxes *pb, PlayerProjectiles *pp);
    void updateFacing(PlayerController *otherPlayer);
    void normalizedToPlayerInput(NormalizedInput input);
    void setInputs(PlayerInput playerInput);
    void processInputs();
    void updateBoxes();
    void checkCollisions(PlayerController *otherPlayer, int stageHalfWidth);
    void calcPhysics(PlayerController *otherPlayer, int stageHalfWidth);
    void updatePhysics();

private:
    bool _isGrounded();
    bool _isCrouched();
    bool _noDirInput();
    bool _noBtnInput();
};

#endif
