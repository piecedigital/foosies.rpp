#ifndef ACTIONS_H
#define ACTIONS_H

#include "globals.hpp"

struct CommandTypes
{
    PlayerInput HCF_Precise[5]; // PlayerInput HCF[5];
    PlayerInput HCB_Precise[5]; // PlayerInput HCB[5];
    PlayerInput DPF_Precise[4];
    PlayerInput DPF[4];
    PlayerInput DPB_Precise[4];
    PlayerInput DPB[4];
    PlayerInput QCF_Precise[3]; // PlayerInput QCF[3];
    PlayerInput QCB_Precise[3]; // PlayerInput QCB[3];
    PlayerInput FF[4];
    PlayerInput BB[4];
    int HCSize = 5;
    int DPSize = 4;
    int QCSize = 3;
    int FFSize = 4;
    int BBSize = 4;
};

static CommandTypes commandsTypes = {
    {PlayerInput::DIR_BACK, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD}, // HCF_Precise
    {PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK}, // HCB_Precise
    {PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD},                              // DPF_Precise
    {PlayerInput::NO_DIR, PlayerInput::DIR_ANY_TOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD},                          // DPF
    {PlayerInput::NO_DIR, PlayerInput::DIR_BACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK},                                  // DPB_Precise
    {PlayerInput::NO_DIR, PlayerInput::DIR_ANY_BACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK},                              // DPB
    {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD},                                                   // QCF_Precise
    {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK},                                                       // QCB_Precise
    {PlayerInput::DIR_TOWARD, PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD},                                                         // FF
    {PlayerInput::DIR_BACK, PlayerInput::NO_DIR, PlayerInput::DIR_BACK},                                                             // BB
};

struct Move
{
    const char *name;
};

struct MoveList
{
    Move *HCF_Precise; // PlayerInput HCF;
    PlayerInput HCFTriggerBtn;
    Move *HCB_Precise; // PlayerInput HCB;
    PlayerInput HCBTriggerBtn;
    Move *DPF_Precise;
    Move *DPF;
    PlayerInput DPFTriggerBtn;
    Move *DPB_Precise;
    Move *DPB;
    PlayerInput DPBTriggerBtn;
    Move *QCF_Precise; // PlayerInput QCF;
    PlayerInput QCFTriggerBtn;
    Move *QCB_Precise; // PlayerInput QCB;
    PlayerInput QCBTriggerBtn;
    Move *FF;
    Move *BB;
};

namespace Rigmoc::Actions
{
    static bool checkMove(Move *move, PlayerInput *playerInputHistory, PlayerInput triggerBtn = PlayerInput::NONE)
    {
        int moveInputReverseCurser = 0;
        bool buttonWithinBuffer = false;

        for (int i = 0; i < INPUT_HISTORY_MAX; i++)
        {
            if (i >= INPUT_BUFFER_MAX)
            {
                return false;
            }

            if (hasFlag(playerInputHistory[i], triggerBtn))
            {
                std::cout << "Triggered: " << move->name << std::endl;
            }
        }
        return false;
    }

    static Move* detectCommand(PlayerInput *playerInputHistory, MoveList *movelist)
    {
        if (checkMove(movelist->HCF_Precise, playerInputHistory, movelist->HCFTriggerBtn))
            return movelist->HCF_Precise;
        if (checkMove(movelist->HCB_Precise, playerInputHistory, movelist->HCBTriggerBtn))
            return movelist->HCB_Precise;
        if (checkMove(movelist->DPF_Precise, playerInputHistory, movelist->DPFTriggerBtn))
            return movelist->DPF_Precise;
        if (checkMove(movelist->DPF, playerInputHistory, movelist->DPFTriggerBtn))
            return movelist->DPF;
        if (checkMove(movelist->DPB_Precise, playerInputHistory, movelist->DPBTriggerBtn))
            return movelist->DPB_Precise;
        if (checkMove(movelist->DPB, playerInputHistory, movelist->DPBTriggerBtn))
            return movelist->DPB;
        if (checkMove(movelist->QCF_Precise, playerInputHistory, movelist->QCFTriggerBtn))
            return movelist->QCF_Precise;
        if (checkMove(movelist->QCB_Precise, playerInputHistory, movelist->QCBTriggerBtn))
            return movelist->QCB_Precise;
        if (checkMove(movelist->FF, playerInputHistory))
            return movelist->FF;
        if (checkMove(movelist->BB, playerInputHistory))
            return movelist->BB;

        return NULL;
    }
}

#endif
