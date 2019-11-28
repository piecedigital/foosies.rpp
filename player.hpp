#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include "bin/ggponet.h"
#include "bin/raylib.h"
#include "custom-types.hpp"

struct PlayerData
{
    PlayerInput input;
    Transform transform;
    Transform3 intTranslation;
};

class PlayerController
{
public:
    GGPOPlayer ggpoPlayer;
    PlayerData pd;
    Color color;
    /**
     * The id of the controller passing inputs to the player
     * -2 is the default, meaning no controller
     * -1 is the keyboard
     * 0 and up is a game pad
     */
    int controllerId;

    PlayerController();

    void update();
    void render();
    void normalizedToPlayerInput(NormalizedInput input);
    void setInputs(PlayerInput playerInput);
};

#endif
