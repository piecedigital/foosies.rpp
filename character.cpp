#include "character.hpp"

Character::Character()
{
    color = BLACK;
    model = LoadModel("assets/models/characters/d-func/d-func.obj");
    // model = LoadModel("assets/models/castle.obj");
    // Texture2D texture = LoadTexture("assets/models/castle_diffuse.png"); // Load model texture
    // model.materials[0].maps[MAP_DIFFUSE].texture = texture;                 // Set map diffuse texture
    // Mesh mesh = GenMeshCube(1.f, 2.f, 0.2f);
    // model = LoadModelFromMesh(mesh);
}
Character::~Character()
{
    unload();
}

void Character::render()
{
    if (pd == NULL)
        return;
    _convertTranslation();
    DrawCube({
                 (*pd)->transform.translation.x,
                 (*pd)->transform.translation.y + 1.f,
                 (*pd)->transform.translation.z - 1.f,
             },
             1.f, 2.f, 0.1f, BLUE);
    DrawModelEx(model, (*pd)->transform.translation, {0.f, 1.f, 0.f}, (90.f * (*pd)->actionFace), {1.f, 1.f, 1.f}, color);
    DrawModelWiresEx(model, (*pd)->transform.translation, {0.f, 1.f, 0.f}, (90.f * (*pd)->actionFace), {1.f, 1.f, 1.f}, BLACK);
}

void Character::unload()
{
    UnloadModel(model);
}

void Character::_convertTranslation()
{
    if ((*pd) == NULL)
        return;
    (*pd)->transform.translation = Vector3{
        ((float)(*pd)->physical.x) / 100,
        ((float)(*pd)->physical.y) / 100,
        ((float)(*pd)->physical.z) / 100,
    };
}