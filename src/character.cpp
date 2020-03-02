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
    JSON json = JsonHandler::loadJsonFile("assets/movesets/d-func-moveset.json");

    fullMoveList.movesSize = json.size();
    fullMoveList.moves = new Move[fullMoveList.movesSize];

    // @TODO: get subset list of basic moves
    basicMoveList.movesSize = fullMoveList.movesSize;
    basicMoveList.moves = fullMoveList.moves;

    for (int i = 0; i < fullMoveList.movesSize; i++)
    {
        fullMoveList.moves[i].name = json[i]["name"].get<std::string>();

        fullMoveList.moves[i].meterCost = 0;
        if (!json[i]["meterCost"].empty())
        {
            fullMoveList.moves[i].meterCost = json[i]["meterCost"].get<int>();
        }

        fullMoveList.moves[i].triggerBtnSize = (PlayerInput)json[i]["triggerBtn"].size();
        fullMoveList.moves[i].triggerBtn = new PlayerInput[fullMoveList.moves[i].triggerBtnSize];
        for (int j = 0; j < fullMoveList.moves[i].triggerBtnSize; j++)
        {
            fullMoveList.moves[i].triggerBtn[j] = (PlayerInput)json[i]["triggerBtn"][j].get<int>();
        }

        fullMoveList.moves[i].triggerBtnCombo = 1;
        if (!json[i]["triggerBtnCombo"].empty())
        {
            fullMoveList.moves[i].triggerBtnCombo = (PlayerInput)json[i]["triggerBtnCombo"].get<int>();
        }

        fullMoveList.moves[i].commandSequenceSize = json[i]["commandSequence"].size();
        fullMoveList.moves[i].commandSequence = new PlayerInput[fullMoveList.moves[i].commandSequenceSize];
        for (int j = 0; j < fullMoveList.moves[j].commandSequenceSize; j++)
        {
            fullMoveList.moves[i].commandSequence[j] = (PlayerInput)json[i]["commandSequence"][j].get<int>();
        }

        fullMoveList.moves[i].frameData.frameDataFromJSON(json[i]["frameData"]);

        if (true)
        {
            basicMoveList.moves[i] = fullMoveList.moves[i];
        }
    }

    model = AssetManager::addModel("assets/models/characters/d-func");
    // model = new ModelController;
    model->init("assets/models/characters/d-func");
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
