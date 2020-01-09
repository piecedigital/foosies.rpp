#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>
#include <vector>
#include "../bin/ggponet.h"
#include "deps/raylib/raylib.h"
#include "character.hpp"
#include "globals.hpp"

struct CommandTypes
{
    PlayerInput HCF_Precise[5];
    // PlayerInput HCF[5];
    PlayerInput HCB_Precise[5];
    // PlayerInput HCB[5];
    PlayerInput DPF_Precise[3];
    // PlayerInput DPF[3];
    PlayerInput DPB_Precise[3];
    // PlayerInput DPB[3];
    PlayerInput QCF_Precise[3];
    // PlayerInput QCF[3];
    PlayerInput QCB_Precise[3];
    // PlayerInput QCB[3];
    PlayerInput FF[3];
    PlayerInput BB[3];
    int HCSize = 5;
    int DPSize = 3;
    int QCSize = 3;
    int FFSize = 3;
    int BBSize = 3;
};

static CommandTypes commandsTypes = {
    {PlayerInput::DIR_BACK, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD}, // HCF_Precise
    {PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK}, // HCB_Precise
    {PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD},                                                   // DPF_Precise
    {PlayerInput::DIR_BACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK},                                                       // DPB_Precise
    {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD},                                                   // QCF_Precise
    {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK},                                                       // QCB_Precise
    {PlayerInput::DIR_TOWARD,  PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD},                                                          // FF
    {PlayerInput::DIR_BACK, PlayerInput::NO_DIR, PlayerInput::DIR_BACK},                                                               // BB
};

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
    bool _detectCommand();
    bool _noDirInput();
    bool _noBtnInput();
};

#endif
