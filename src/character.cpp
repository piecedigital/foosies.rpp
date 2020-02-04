#include <vector>
#include "character.hpp"
#include "asset_manager.hpp"

Character::Character()
{
    towardHSpeed = 10;
    backHSpeed = 6;
    accellerationH = 4;

    model = AssetManager::addModel("assets/models/characters/d-func");
    // model = new ModelController;
    model->init("assets/models/characters/d-func");

    moveList.DPF_Precise = new Move{
        "Dragon Punch",
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.DPF_Precise,
        Actions::commandsTypes.DPSize,
    };

    moveList.DPF = &(*moveList.DPF_Precise);
    moveList.DPF->commandSequence = Actions::commandsTypes.DPF;

    moveList.QCF_Precise = new Move{
        "Hadouken",
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.QCF_Precise,
        Actions::commandsTypes.QCSize,
    };

    moveList.FF = new Move{
        "Forward Dash",
        (PlayerInput)(PlayerInput::DIR_TOWARD),
        Actions::commandsTypes.FF,
        Actions::commandsTypes.FFSize,
    };

    moveList.BB = new Move{
        "Back Dash",
        (PlayerInput)(PlayerInput::DIR_BACK),
        Actions::commandsTypes.BB,
        Actions::commandsTypes.BBSize,
    };
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

        model->render((*playerData)->transform.translation, (*playerData)->actionFace);
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
