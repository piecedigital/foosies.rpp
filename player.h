#ifndef PLAYER_H
#define PLAYER_H

#include "bin/ggponet.h"
#include "bin/raylib.h"
#include "custom-types.h"

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
    void normalizedToPlayerInput(NormalizedInput input);
    void setInputs(PlayerInput playerInput);
};

#endif
