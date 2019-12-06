#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "bin/ggponet.h"
#include "bin/raylib.h"
#include "custom-types.hpp"

class PlayerController
{
public:
    GGPOPlayer ggpoPlayer;
    PlayerData *pd;
    NormalizedInput normalizedInput;
    Color color;
    Model model;
    /**
     * The id of the controller passing inputs to the player
     * -2 is the default, meaning no controller
     * -1 is the keyboard
     * 0 and up is a game pad
     */
    int controllerId;

    PlayerController();
    ~PlayerController();

    void update(PlayerController &otherPlayer);
    void render();
    void normalizedToPlayerInput(NormalizedInput input);
    void setInputs(PlayerInput playerInput);
    void unload();

private:
    void _convertTranslation();
    void _calcForces();
    void _applyForces();
    bool _isGrounded();
};

#endif
