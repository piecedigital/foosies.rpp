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

struct Move
{
};

struct MoveList
{
    Move *HCF_Precise; // PlayerInput HCF[5];
    Move *HCB_Precise; // PlayerInput HCB[5];
    Move *DPF_Precise;
    Move *DPF;
    Move *DPB_Precise;
    Move *DPB;
    Move *QCF_Precise; // PlayerInput QCF[3];
    Move *QCB_Precise; // PlayerInput QCB[3];
    Move *FF;
    Move *BB;
    const char *processOrder[10] = {"HCF_Precise","HCB_Precise","DPF_Precise","DPF","DPB_Precise","DPB","QCF_Precise","QCB_Precise","FF","BB"};
};

namespace Rigmoc::Actions
{
    static Move detectCommand(PlayerInput *playerInputHistory, MoveList *movelist)
    {
        switch (expression)
            {
            case /* constant-expression */:
                /* code */
                break;

            default:
                break;
            }

        for (int i = 0; i < INPUT_HISTORY_MAX; i++)
        {
        }

        return Move{};
    }
}

#endif
