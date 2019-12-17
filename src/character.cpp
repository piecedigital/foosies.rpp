#include <vector>
#include "character.hpp"

Character::Character()
{
    color = BLACK;
    model = LoadModel("assets/models/characters/d-func/d-func.obj");

    // Shader shader = LoadShader("assets/shaders/toon.vs", "assets/shaders/toon.fs");
    // Material mat = LoadMaterialDefault();

    // mat.shader.locs[LOC_] = GetShaderLocation(shader, "lightPosition");
    // shader.locs[LOC_VECTOR_VIEW] = GetShaderLocation(shader, "eyePosition");
    // shader.locs[LOC_MAP_METALNESS] = GetShaderLocation(shader, "materialShininess");
    // shader.locs[LOC_MAP_DIFFUSE] = GetShaderLocation(shader, "materialDiffuse");
    // shader.locs[LOC_MAP_SPECULAR] = GetShaderLocation(shader, "materialSpecular");

    // float cameraPos[3] = {0.f, 3.f, 1.f};

    // SetShaderValue(shader, LOC_VECTOR_VIEW, cameraPos, UNIFORM_VEC3);
    // SetShaderValue(shader, LOC_MAP_METALNESS, new int[1]{ 1 }, UNIFORM_INT);
    // SetShaderValue(shader, LOC_MAP_DIFFUSE, new float[1]{ 1.f }, UNIFORM_FLOAT);
    // SetShaderValue(shader, LOC_MAP_SPECULAR, new float[1]{ 1.f }, UNIFORM_FLOAT);

    // model.materials[0] = mat;
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
    else
    {
        std::cout << "it's all null" << std::endl;
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
    box.updateBoxShape((*playerData)->physical.x, (*playerData)->physical.y + 100.f, 1.f, 2.f);
    box.render();
}
