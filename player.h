#pragma once

#include "bin/ggponet.h"
#include "bin/raylib.h"
#include "custom-types.h"

#ifndef PLAYER_H
#define PLAYER_H

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

    PlayerController();

    void update();
    void render();

    bool hasFlag(PlayerInput &flag)
    {
        return (pd.input & flag);
    };
};

#endif
