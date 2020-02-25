#include "actions.hpp"

bool Actions::checkMove(Action *action, PlayerInput *playerInputHistory)
{
    if (action == NULL || !action->active)
        return false;

    int inputCurser = 0;
    bool buttonWithinBuffer = false;

    int maxTravelDistance = 10;
    int spaceTravelled = 0;

    // int discrepencyMax = 2;
    // int discrepencies = 0;

    int inputsMatched = 0;

    int i = 0;
    // check for button press within buffer window
    for (i; i < INPUT_BUFFER_MAX; i++)
    {
        if (hasFlag(playerInputHistory[i], action->triggerBtn))
        {
            buttonWithinBuffer = true;
        }
    }

    if (buttonWithinBuffer)
    {
        for (i--; i < INPUT_HISTORY_MAX; i++)
        {
            if (hasFlag(playerInputHistory[i], action->commandSequence[(action->sequenceSize - 1) - inputCurser]))
            {
                inputsMatched++;

                inputCurser++;
                spaceTravelled = 0;
            }
            else
            {
                spaceTravelled++;
                if (spaceTravelled >= maxTravelDistance)
                {
                    break;
                }
            }

            if (inputsMatched == action->sequenceSize)
            {
                std::cout << "Triggered: " << action->name << std::endl;
                return true;
            }
        }
    }

    return false;
}

Action* Actions::detectCommand(PlayerInput *playerInputHistory, ActionList *movelist)
{
    if (checkMove(movelist->HCF_Precise, playerInputHistory))
        return movelist->HCF_Precise;
    if (checkMove(movelist->HCB_Precise, playerInputHistory))
        return movelist->HCB_Precise;
    if (checkMove(movelist->DPF_Precise, playerInputHistory))
        return movelist->DPF_Precise;
    if (checkMove(movelist->DPF, playerInputHistory))
        return movelist->DPF;
    if (checkMove(movelist->DPB_Precise, playerInputHistory))
        return movelist->DPB_Precise;
    if (checkMove(movelist->DPB, playerInputHistory))
        return movelist->DPB;
    if (checkMove(movelist->QCF_Precise, playerInputHistory))
        return movelist->QCF_Precise;
    if (checkMove(movelist->QCB_Precise, playerInputHistory))
        return movelist->QCB_Precise;
    if (checkMove(movelist->FF, playerInputHistory))
        return movelist->FF;
    if (checkMove(movelist->BB, playerInputHistory))
        return movelist->BB;

    return NULL;
}
