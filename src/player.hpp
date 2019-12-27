#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include "../bin/ggponet.h"
#include "../bin/raylib.h"
#include "character.hpp"
#include "globals.hpp"

class PlayerController
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
     * -2 is the default, meaning no controller
     * -1 is the keyboard
     * 0 and up is a game pad
     */
    int controllerId;
    std::vector<PlayerInput> history;
    int inputBufferLimit = 3;

    PlayerController();
    ~PlayerController();

    void init(PlayerData *pd, PlayerBoxes *pb, PlayerProjectiles *pp);
    void updateFacing(PlayerController *otherPlayer);
    void normalizedToPlayerInput(NormalizedInput input);
    void setInputs(PlayerInput playerInput);
    void processInputs();
    void updateBoxes();
    void checkCollisions(PlayerController *otherPlayer, int stageHalfWidth);
    void calcPhysics(PlayerController *otherPlayer, int stageHalfWidth);
    void updatePhysics();

private:
    void _applyForces(PlayerController *otherPlayer, int stageHalfWidth);
    void _recalcForces();
    bool _isGrounded();
    bool _isCrouched();
};

#endif
