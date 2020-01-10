#include <vector>
#include "character.hpp"

Character::Character()
{
    bodyWidth = 100;
    bodyHeight = 200;
    color = BLACK;
    model = LoadModel("assets/models/characters/d-func/d-func.obj");
    for (int i = 0; i < model.materialCount; i++)
    {
        Shader shader = LoadShader("assets/shaders/toon.vs", "assets/shaders/toon.fs");

        float cameraPos[3] = {0.f, 3.f, 2.f};

        float lightPos[3] = {
            2.f,
            6.f,
            2.f};

        SetShaderValue(shader, GetShaderLocation(shader, "color"), &model.materials[i].maps[MAP_ALBEDO].color, UNIFORM_VEC3);
        SetShaderValue(shader, GetShaderLocation(shader, "lightPosition"), lightPos, UNIFORM_VEC3);
        SetShaderValue(shader, GetShaderLocation(shader, "eyePosition"), cameraPos, UNIFORM_VEC3);
        SetShaderValue(shader, GetShaderLocation(shader, "materialShininess"), new int[1]{1}, UNIFORM_INT);
        SetShaderValue(shader, GetShaderLocation(shader, "materialDiffuse"), new float[1]{1.f}, UNIFORM_FLOAT);
        SetShaderValue(shader, GetShaderLocation(shader, "materialSpecular"), new float[1]{1.f}, UNIFORM_FLOAT);

        shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "model_matrix");
        shader.locs[LOC_MATRIX_VIEW] = GetShaderLocation(shader, "view_matrix");
        shader.locs[LOC_MATRIX_PROJECTION] = GetShaderLocation(shader, "projection_matrix");

        model.materials[i].maps[MAP_METALNESS].value = 1.f;
        model.materials[i].maps[MAP_ROUGHNESS].value = 5.5;
        model.materials[i].maps[MAP_OCCLUSION].value = 1.0f;
        model.materials[i].maps[MAP_EMISSION].value = 0.5f;
        model.materials[i].maps[MAP_HEIGHT].value = 0.5f;

        model.materials[i].shader = shader;
    }

    moveList.QCF_Precise = new Move;
    moveList.QCF_Precise->name = "Hadouken";
    moveList.QCFTriggerBtn = (PlayerInput)(PlayerInput::BTN_JAB | PlayerInput::BTN_STRONG | PlayerInput::BTN_FIERCE);
}
Character::~Character()
{
    unload();
}

void Character::render()
{
    float lightPos[3] = {
        (*playerData)->transform.translation.x + 1,
        (*playerData)->transform.translation.y + 1,
        (*playerData)->transform.translation.z + 1};
    // SetShaderValue(model.materials[0].shader, GetShaderLocation(model.materials[0].shader, "lightPosition"), lightPos, UNIFORM_VEC3);

    if (*playerData != NULL)
    {
        _convertTranslation();

        DrawModelEx(model, (*playerData)->transform.translation, {0.f, 1.f, 0.f}, (90.f * (*playerData)->actionFace), {1.f, 1.f, 1.f}, WHITE);
        DrawModelWiresEx(model, (*playerData)->transform.translation, {0.f, 1.f, 0.f}, (90.f * (*playerData)->actionFace), {1.f, 1.f, 1.f}, color);
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
{
    UnloadModel(model);
}

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
