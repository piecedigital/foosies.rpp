#include "actions.hpp"

bool Actions::checkMove(Move move, PlayerInput *playerInputHistory)
{
    int inputCurser = 0;
    bool buttonWithinBuffer = false;

    int maxTravelDistance = 7;
    int spaceTravelled = 0;

    // int discrepencyMax = 2;
    // int discrepencies = 0;

    int inputsMatched = 0;

    int i = 0;
    // check for button press within buffer window
    for (i; i < INPUT_BUFFER_MAX; i++)
    {
        int triggerButtonsFound = 0;

        for (int j = 0; j < move.triggerBtnSize; j++)
        {
            if (hasFlag(playerInputHistory[i], move.triggerBtn[j]))
            {
                triggerButtonsFound++;
            }
        }

        if (triggerButtonsFound >= move.triggerBtnCombo)
        {
            buttonWithinBuffer = true;
        }
    }

    if (buttonWithinBuffer)
    {
        for (i--; i < INPUT_HISTORY_MAX; i++)
        {
            if (hasFlag(playerInputHistory[i], move.commandSequence[(move.commandSequenceSize - 1) - inputCurser]))
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

            if (inputsMatched == move.commandSequenceSize)
            {
                std::cout << "Triggered: " << move.name << std::endl;
                return true;
            }
        }
    }

    return false;
}

Move* Actions::detectCommand(PlayerInput *playerInputHistory, MoveList moveList, int meter)
{
    for (int i = 0; i < moveList.movesSize; i++)
    {
        if (meter >= moveList.moves[i].meterCost && checkMove(moveList.moves[i], playerInputHistory))
            return &moveList.moves[i];
    }

    return NULL;
}
