#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "bin/ggponet.h"
#include "bin/raylib.h"
#include "character.hpp"
#include "globals.hpp"

class PlayerController
{
public:
    GGPOPlayer ggpoPlayer;
    PlayerData *playerData;
    PlayerBoxes *playerBoxes;
    Character charMan[1];

    /**
     * The id of the controller passing inputs to the player
     * -2 is the default, meaning no controller
     * -1 is the keyboard
     * 0 and up is a game pad
     */
    int controllerId;

    PlayerController();
    ~PlayerController();

    void init(PlayerData *pd, PlayerBoxes *pb);
    void update(PlayerController &otherPlayer);
    void normalizedToPlayerInput(NormalizedInput input);
    void setInputs(PlayerInput playerInput);

private:
    void _calcForces();
    void _applyForces();
    bool _isGrounded();
};

#endif
