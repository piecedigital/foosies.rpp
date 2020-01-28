#ifndef ACTIONS_H
#define ACTIONS_H

#include "globals.hpp"

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

struct Move
{
    const char *name;
    PlayerInput triggerBtn;
    PlayerInput *commandSequence;
    int sequenceSize;
};

struct MoveList
{
    Move *HCF_Precise; // PlayerInput HCF;
    Move *HCB_Precise; // PlayerInput HCB;
    Move *DPF_Precise;
    Move *DPF;
    Move *DPB_Precise;
    Move *DPB;
    Move *QCF_Precise; // PlayerInput QCF;
    Move *QCB_Precise; // PlayerInput QCB;
    Move *FF;
    Move *BB;
};

namespace Actions
{
static CommandTypes commandsTypes = {
    {PlayerInput::DIR_BACK, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD}, // HCF_Precise
    {PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK}, // HCB_Precise
    {PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD},                                                   // DPF_Precise
    {PlayerInput::DIR_ANY_TOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD},                                               // DPF
    {PlayerInput::DIR_BACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK},                                                       // DPB_Precise
    {PlayerInput::DIR_ANY_BACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK},                                                   // DPB
    {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD},                                                   // QCF_Precise
    {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK},                                                       // QCB_Precise
    {PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD, PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD},                                                         // FF
    {PlayerInput::NO_DIR, PlayerInput::DIR_BACK, PlayerInput::NO_DIR, PlayerInput::DIR_BACK},                                                             // BB
    5,
    3,
    3,
    4,
    4,
};

bool checkMove(Move *move, PlayerInput *playerInputHistory);

Move *detectCommand(PlayerInput *playerInputHistory, MoveList *movelist);
};

#endif
