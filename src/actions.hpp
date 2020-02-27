#ifndef ACTIONS_H
#define ACTIONS_H

#include "globals.hpp"
#include "moves.hpp"

namespace Actions
{
struct CommandTypes
{
    PlayerInput HCF_Precise[5]; // PlayerInput HCF[5];
    PlayerInput HCB_Precise[5]; // PlayerInput HCB[5];
    PlayerInput DPF_Precise[3];
    PlayerInput DPF[3];
    PlayerInput DPB_Precise[3];
    PlayerInput DPB[3];
    PlayerInput QCF_Precise[3]; // PlayerInput QCF[3];
    PlayerInput QCB_Precise[3]; // PlayerInput QCB[3];
    PlayerInput FF[4];
    PlayerInput BB[4];
    int HCSize;
    int DPSize;
    int QCSize;
    int FFSize;
    int BBSize;
};

static CommandTypes commandsTypes = {
    {PlayerInput::DIR_BACK, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD},
    {PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK},
    {PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD},
    {PlayerInput::DIR_ANY_TOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD},
    {PlayerInput::DIR_BACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK},
    {PlayerInput::DIR_ANY_BACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK},
    {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD},
    {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK},
    {PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD, PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD},
    {PlayerInput::NO_DIR, PlayerInput::DIR_BACK, PlayerInput::NO_DIR, PlayerInput::DIR_BACK},
    5,
    3,
    3,
    4,
    4,
};

bool checkMove(Move move, PlayerInput *);

Move *detectCommand(PlayerInput *, MoveList);
};

#endif
