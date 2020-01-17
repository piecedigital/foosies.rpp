#include <vector>
#include "character.hpp"

Character::Character()
{
    moveList.DPF_Precise = new Move;
    moveList.DPF_Precise->name = "Dragon Punch";
    moveList.DPF_Precise->triggerBtn = (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE);
    moveList.DPF_Precise->commandSequence = Actions::commandsTypes.DPF_Precise;
    moveList.DPF_Precise->sequenceSize = Actions::commandsTypes.DPSize;

    moveList.DPF = moveList.DPF_Precise;
    moveList.DPF->commandSequence = Actions::commandsTypes.DPF;

    moveList.QCF_Precise = new Move;
    moveList.QCF_Precise->name = "Hadouken";
    moveList.QCF_Precise->triggerBtn = (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE);
    moveList.QCF_Precise->commandSequence = Actions::commandsTypes.QCF_Precise;
    moveList.QCF_Precise->sequenceSize = Actions::commandsTypes.QCSize;
}
Character::~Character()
{
    unload();
}

void Character::render()
{
    if (*playerData != NULL)
    {
        _convertTranslation();

        model.render((*playerData)->transform.translation, (*playerData)->actionFace);
    }

    if (playerBoxes != NULL && *playerBoxes != NULL)
    {
        PlayerBoxes *box = *playerBoxes;
        for (int i = 0; i < box->pushBoxSize; i++)
        {
            _renderBox(box->pushBoxArray[i]);
        }
        for (int i = 0; i < box->grabBoxesSize; i++)
        {
            _renderBox(box->grabBoxesArray[i]);
        }
        for (int i = 0; i < box->hitBoxesSize; i++)
        {
            _renderBox(box->hitBoxesArray[i]);
        }
        for (int i = 0; i < box->hurtBoxesSize; i++)
        {
            _renderBox(box->hurtBoxesArray[i]);
        }
        for (int i = 0; i < box->proximityBoxesSize; i++)
        {
            _renderBox(box->proximityBoxesArray[i]);
        }
    }
}

void Character::unload()
{}

void Character::_convertTranslation()
{
    if ((*playerData) == NULL)
        return;
    (*playerData)->transform.translation = Vector3{
        ((float)(*playerData)->physical.x) / 100,
        ((float)(*playerData)->physical.y) / 100,
        ((float)(*playerData)->physical.z) / 100,
    };
}

void Character::_renderBox(Box box)
{
    box.render();
}
