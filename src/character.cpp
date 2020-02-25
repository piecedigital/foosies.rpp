#include <vector>
#include "character.hpp"
#include "asset_manager.hpp"
#include "json_handler.hpp"
#include "frame_data.hpp"

using JSON = nlohmann::json;

Character::Character()
{
    towardHSpeed = 10;
    backHSpeed = 6;
    accellerationH = 4;
    JSON json = JsonHandler::loadJsonFile("assets/sample.json");

    std::cout << json.dump() << std::endl;
    FrameData fd;
    fd.frameDataFromJSON(json["frameData"]);
    std::cout << fd.stunWindow[0].stunValue << std::endl;

    model = AssetManager::addModel("assets/models/characters/d-func");
    // model = new ModelController;
    model->init("assets/models/characters/d-func");

    actionList.HCF_Precise = new Action{
        "HCF_Precise",
        true,
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.HCF_Precise,
        Actions::commandsTypes.DPSize,
    };

    actionList.HCB_Precise = new Action{
        "HCB_Precise",
        true,
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.HCB_Precise,
        Actions::commandsTypes.DPSize,
    };

    actionList.DPF_Precise = new Action{
        "DPF_Precise",
        true,
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.DPF_Precise,
        Actions::commandsTypes.DPSize,
    };

    actionList.DPF = &(*actionList.DPF_Precise);
    actionList.DPF->name = "DPF";
    actionList.DPF->commandSequence = Actions::commandsTypes.DPF;

    actionList.QCF_Precise = new Action{
        "QCF_Precise",
        true,
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.QCF_Precise,
        Actions::commandsTypes.QCSize,
    };

    actionList.QCB_Precise = new Action{
        "QCB_Precise",
        true,
        (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE),
        Actions::commandsTypes.QCB_Precise,
        Actions::commandsTypes.QCSize,
    };

    actionList.FF = new Action{
        "FF",
        true,
        (PlayerInput)(PlayerInput::DIR_TOWARD),
        Actions::commandsTypes.FF,
        Actions::commandsTypes.FFSize,
    };

    actionList.BB = new Action{
        "BB",
        true,
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
