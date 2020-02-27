#ifndef ACTIONS_H
#define ACTIONS_H

#include "globals.hpp"
#include "moves.hpp"

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

struct Action
{
    const char *name;
    PlayerInput triggerBtn;
    PlayerInput *commandSequence;
    int sequenceSize;
};

struct ActionList
{
    Action *HCF_Precise; // PlayerInput HCF;
    Action *HCB_Precise; // PlayerInput HCB;
    Action *DPF_Precise;
    Action *DPF;
    Action *DPB_Precise;
    Action *DPB;
    Action *QCF_Precise; // PlayerInput QCF;
    Action *QCB_Precise; // PlayerInput QCB;
    Action *FF;
    Action *BB;
};

namespace Actions
{
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

bool checkMove(Move move, Action *, PlayerInput *);

Action *detectCommand(PlayerInput *, MoveList);

static ActionList actionList;
void initActions();
};

#endif
