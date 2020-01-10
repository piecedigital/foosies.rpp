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

static CommandTypes commandsTypes = {
    {PlayerInput::DIR_BACK, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD}, // HCF_Precise
    {PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK}, // HCB_Precise
    {PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD},                              // DPF_Precise
    {PlayerInput::NO_DIR, PlayerInput::DIR_ANY_TOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD},                          // DPF
    {PlayerInput::NO_DIR, PlayerInput::DIR_BACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK},                                  // DPB_Precise
    {PlayerInput::NO_DIR, PlayerInput::DIR_ANY_BACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK},                              // DPB
    {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD},                                                   // QCF_Precise
    {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK},                                                       // QCB_Precise
    {PlayerInput::DIR_TOWARD,  PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD},                                                        // FF
    {PlayerInput::DIR_BACK, PlayerInput::NO_DIR, PlayerInput::DIR_BACK},                                                             // BB
};

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
