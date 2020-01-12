#include "actions.hpp"

// CommandTypes Actions::commandsTypes = {
//     {PlayerInput::DIR_BACK, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD},
//     {PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK},
//     {PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD},
//     {PlayerInput::NO_DIR, PlayerInput::DIR_ANY_TOWARD, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD},
//     {PlayerInput::NO_DIR, PlayerInput::DIR_BACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK},
//     {PlayerInput::NO_DIR, PlayerInput::DIR_ANY_BACK, PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK},
//     {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNTOWARD, PlayerInput::DIR_TOWARD},
//     {PlayerInput::DIR_DOWN, PlayerInput::DIR_DOWNBACK, PlayerInput::DIR_BACK},
//     {PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD, PlayerInput::NO_DIR, PlayerInput::DIR_TOWARD},
//     {PlayerInput::NO_DIR, PlayerInput::DIR_BACK, PlayerInput::NO_DIR, PlayerInput::DIR_BACK},
//     5,
//     4,
//     3,
//     4,
//     4,
// };

bool Actions::checkMove(Move *move, PlayerInput *playerInputHistory)
{
    if (move == NULL)
        return false;

    int inputCurser = 0;
    bool buttonWithinBuffer = false;

    // int inputSpacingMax = 5;
    int spaceTravelled = 0;

    // int discrepencyMax = 2;
    // int discrepencies = 0;

    int inputsMatched = 0;

    for (int i = 0; i < INPUT_HISTORY_MAX; i++)
    {
        if (!buttonWithinBuffer)
        {
            if (hasFlag(playerInputHistory[i], move->triggerBtn))
            {
                buttonWithinBuffer = true;
                std::cout << "btn" << std::endl;
            }

            if (i >= INPUT_BUFFER_MAX)
            {
                return false;
            }
        }

        if (hasFlag(playerInputHistory[i], move->commandSequence[move->sequenceSize - 1 - inputCurser]))
        {
            inputsMatched++;
            inputCurser++;
            spaceTravelled = 0;
            std::cout
                << "i: " << i
                << ", Cursor: " << inputCurser
                << " | "
                << playerInputHistory[i]
                << " & "
                << move->commandSequence[move->sequenceSize - 1 - inputCurser]
                << " = "
                << (playerInputHistory[i] & move->commandSequence[move->sequenceSize - 1 - inputCurser])
                << " | Match: " << inputsMatched
                << std::endl;
        }
        else
        {
            spaceTravelled++;
        }


        if (inputsMatched == move->sequenceSize)
        {
            std::cout << "Triggered: " << move->name << std::endl;
            return true;
        }
    }

    return false;
}

Move* Actions::detectCommand(PlayerInput *playerInputHistory, MoveList *movelist)
{
    // if (checkMove(movelist->HCF_Precise, playerInputHistory))
    //     return movelist->HCF_Precise;
    // if (checkMove(movelist->HCB_Precise, playerInputHistory))
    //     return movelist->HCB_Precise;
    // if (checkMove(movelist->DPF_Precise, playerInputHistory))
    //     return movelist->DPF_Precise;
    // if (checkMove(movelist->DPF, playerInputHistory))
    //     return movelist->DPF;
    // if (checkMove(movelist->DPB_Precise, playerInputHistory))
    //     return movelist->DPB_Precise;
    // if (checkMove(movelist->DPB, playerInputHistory))
    //     return movelist->DPB;
    if (checkMove(movelist->QCF_Precise, playerInputHistory))
        return movelist->QCF_Precise;
    // if (checkMove(movelist->QCB_Precise, playerInputHistory))
    //     return movelist->QCB_Precise;
    // if (checkMove(movelist->FF, playerInputHistory))
    //     return movelist->FF;
    // if (checkMove(movelist->BB, playerInputHistory))
    //     return movelist->BB;

    return NULL;
}
