#include <vector>
#include <algorithm>
#include <iterator>
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

    JSON moveListJson = json["fullMoveList"];

    fullMoveList.movesSize = moveListJson.size();
    fullMoveList.moves = new Move[fullMoveList.movesSize];

    basicMoveList.movesSize = json["basicMoveList"].size();
    basicMoveList.moves = new Move[basicMoveList.movesSize];
    int basicMovesCursor = 0;
    std::vector<int> intArray;
    for (int i = 0; i < basicMoveList.movesSize; i++)
    {
        intArray.push_back(json["basicMoveList"][i].get<int>());
    }

    for (int i = 0; i < fullMoveList.movesSize; i++)
    {
        fullMoveList.moves[i].name = moveListJson[i]["name"].get<std::string>();

        fullMoveList.moves[i].meterCost = 0;
        if (!moveListJson[i]["meterCost"].empty())
        {
            fullMoveList.moves[i].meterCost = moveListJson[i]["meterCost"].get<int>();
        }

        fullMoveList.moves[i].triggerBtnSize = (PlayerInput)moveListJson[i]["triggerBtn"].size();
        fullMoveList.moves[i].triggerBtn = new PlayerInput[fullMoveList.moves[i].triggerBtnSize];
        for (int j = 0; j < fullMoveList.moves[i].triggerBtnSize; j++)
        {
            fullMoveList.moves[i].triggerBtn[j] = (PlayerInput)moveListJson[i]["triggerBtn"][j].get<int>();
        }

        fullMoveList.moves[i].triggerBtnCombo = 1;
        if (!moveListJson[i]["triggerBtnCombo"].empty())
        {
            fullMoveList.moves[i].triggerBtnCombo = (PlayerInput)moveListJson[i]["triggerBtnCombo"].get<int>();
        }

        fullMoveList.moves[i].commandSequenceSize = moveListJson[i]["commandSequence"].size();
        fullMoveList.moves[i].commandSequence = new PlayerInput[fullMoveList.moves[i].commandSequenceSize];
        for (int j = 0; j < fullMoveList.moves[i].commandSequenceSize; j++)
        {
            fullMoveList.moves[i].commandSequence[j] = (PlayerInput)moveListJson[i]["commandSequence"][j].get<int>();
        }

        fullMoveList.moves[i].frameData.frameDataFromJSON(moveListJson[i]["frameData"]);

        auto result = std::find(std::begin(intArray), std::end(intArray), i);
        if (result != std::end(intArray))
        {
            basicMoveList.moves[basicMovesCursor] = fullMoveList.moves[i];
            basicMovesCursor++;
        }
    }

    asset = AssetManager::addModel("assets/models/characters/d-func");
    asset->init("assets/models/characters/d-func");
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

        asset->render((*playerData)->transform.translation, (*playerData)->actionFace);
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
