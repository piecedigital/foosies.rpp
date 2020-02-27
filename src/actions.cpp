#include "actions.hpp"

bool Actions::checkMove(Action *action, PlayerInput *playerInputHistory)
{
    if (action == NULL)
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

Action* Actions::detectCommand(PlayerInput *playerInputHistory, MoveList moveList)
{
    if (checkMove(actionList.HCF_Precise, playerInputHistory))
        return actionList.HCF_Precise;
    if (checkMove(actionList.HCB_Precise, playerInputHistory))
        return actionList.HCB_Precise;
    if (checkMove(actionList.DPF_Precise, playerInputHistory))
        return actionList.DPF_Precise;
    if (checkMove(actionList.DPF, playerInputHistory))
        return actionList.DPF;
    if (checkMove(actionList.DPB_Precise, playerInputHistory))
        return actionList.DPB_Precise;
    if (checkMove(actionList.DPB, playerInputHistory))
        return actionList.DPB;
    if (checkMove(actionList.QCF_Precise, playerInputHistory))
        return actionList.QCF_Precise;
    if (checkMove(actionList.QCB_Precise, playerInputHistory))
        return actionList.QCB_Precise;
    if (checkMove(actionList.FF, playerInputHistory))
        return actionList.FF;
    if (checkMove(actionList.BB, playerInputHistory))
        return actionList.BB;

    return NULL;
}

void Actions::initActions()
{
    actionList.HCF_Precise = new Action{
        "HCF_Precise",
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.HCF_Precise,
        Actions::commandsTypes.DPSize,
    };

    actionList.HCB_Precise = new Action{
        "HCB_Precise",
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.HCB_Precise,
        Actions::commandsTypes.DPSize,
    };

    actionList.DPF_Precise = new Action{
        "DPF_Precise",
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.DPF_Precise,
        Actions::commandsTypes.DPSize,
    };

    actionList.DPF = &(*actionList.DPF_Precise);
    actionList.DPF->name = "DPF";
    actionList.DPF->commandSequence = Actions::commandsTypes.DPF;

    actionList.QCF_Precise = new Action{
        "QCF_Precise",
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.QCF_Precise,
        Actions::commandsTypes.QCSize,
    };

    actionList.QCB_Precise = new Action{
        "QCB_Precise",
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.QCB_Precise,
        Actions::commandsTypes.QCSize,
    };

    actionList.FF = new Action{
        "FF",
        (PlayerInput)(PlayerInput::DIR_TOWARD),
        Actions::commandsTypes.FF,
        Actions::commandsTypes.FFSize,
    };

    actionList.BB = new Action{
        "BB",
        (PlayerInput)(PlayerInput::DIR_BACK),
        Actions::commandsTypes.BB,
        Actions::commandsTypes.BBSize,
    };
}
