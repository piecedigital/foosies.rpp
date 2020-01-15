#include "model.hpp"

ModelWrapper::ModelWrapper()
{
    bodyWidth = 100;
    bodyHeight = 200;
    color = BLACK;
    model = LoadModel("assets/models/characters/d-func/d-func.obj");

    Texture baseColor = LoadTexture("assets/models/characters/d-func/Skin Base Color.png");
    Texture bumpMap = LoadTexture("assets/models/characters/d-func/Skin Bump.png");

    Shader shader = LoadShader("assets/shaders/toon.vs", "assets/shaders/toon.fs");

    float cameraPos[3] = {0.f, 3.f, 2.f};

    lightPos[0] = 2.f;
    lightPos[1] = 6.f;
    lightPos[2] = 2.f;

    SetShaderValue(shader, GetShaderLocation(shader, "color"), new Vector3{
            (float)(color.r / 255),
            (float)(color.g / 255),
            (float)(color.b / 255),
        },
        UNIFORM_VEC3);
    SetShaderValue(shader, GetShaderLocation(shader, "lightPosition"), lightPos, UNIFORM_VEC3);
    SetShaderValue(shader, GetShaderLocation(shader, "eyePosition"), cameraPos, UNIFORM_VEC3);
    SetShaderValue(shader, GetShaderLocation(shader, "materialShininess"), new int[1]{1}, UNIFORM_INT);
    SetShaderValue(shader, GetShaderLocation(shader, "materialDiffuse"), new Vector3{2.f, 2.f, 2.f}, UNIFORM_VEC3);
    SetShaderValue(shader, GetShaderLocation(shader, "materialSpecular"), new float{0.1f}, UNIFORM_FLOAT);
    model.materials[0].maps[MAP_DIFFUSE].texture = baseColor;
    model.materials[0].maps[MAP_HEIGHT].texture = bumpMap;

    shader.locs[LOC_MATRIX_MODEL] = GetShaderLocation(shader, "model_matrix");
    shader.locs[LOC_MATRIX_VIEW] = GetShaderLocation(shader, "view_matrix");
    shader.locs[LOC_MATRIX_PROJECTION] = GetShaderLocation(shader, "projection_matrix");

    model.materials[0].maps[MAP_METALNESS].value = 1.f;
    model.materials[0].maps[MAP_ROUGHNESS].value = 1.f;
    model.materials[0].maps[MAP_OCCLUSION].value = 1.0f;
    model.materials[0].maps[MAP_EMISSION].value = 0.5f;
    model.materials[0].maps[MAP_HEIGHT].value = 1.f;

    model.materials[0].shader = shader;
}
ModelWrapper::~ModelWrapper()
{
    unload();
}

void ModelWrapper::render(Vector3 translation, int rotation)
{
    // SetShaderValue(model.materials[0].shader, GetShaderLocation(model.materials[0].shader, "lightPosition"), lightPos, UNIFORM_VEC3);
    DrawModelEx(model, translation, {0.f, 1.f, 0.f}, (90.f * rotation), {1.f, 1.f, 1.f}, WHITE);
    DrawModelWiresEx(model, translation, {0.f, 1.f, 0.f}, (90.f * rotation), {1.f, 1.f, 1.f}, color);
}

void ModelWrapper::unload()
{
    UnloadModel(model);
}