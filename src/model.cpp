#include "model.hpp"
#include <string>
#include <iostream>

ModelController::ModelController()
{
    bodyWidth = 100;
    bodyHeight = 200;
    color = BLACK;
};

void ModelController::init(const char *folder)
{
    bodyWidth = 100;
    bodyHeight = 200;
    color = BLACK;
    // model = LoadModel(std::string(folder).append("/model.gltf").c_str());
    model = LoadModel(std::string(folder).append("/model.iqm").c_str());
    animations = LoadModelAnimations(std::string(folder).append("/model.iqm").c_str(), &animCount);
    Texture baseColor = LoadTexture(std::string(folder).append("/Texture.png").c_str());
    Texture bumpMap = LoadTexture(std::string(folder).append("/Bump.png").c_str());

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

void ModelController::setAnimation(int animationId)
{
    currentAnim = animationId;
    UpdateModelAnimation(model, animations[currentAnim], 0);
}

void ModelController::setAnimationFrame(int frame)
{
    UpdateModelAnimation(model, animations[currentAnim], frame);
}

void ModelController::setAnimationFrameArray(int *frameArray)
{}

void ModelController::setAnimationLoop(bool willLoop)
{
    animationWillLoop = willLoop;
}

void ModelController::render(Vector3 translation, int rotation)
{
    // SetShaderValue(model.materials[0].shader, GetShaderLocation(model.materials[0].shader, "lightPosition"), lightPos, UNIFORM_VEC3);
    DrawModelExPlus(model, translation, {0.f, 1.f, 0.f}, {
        90.f,
        (90.f * rotation * -1),
        0,
    }, {1.f, 1.f, 1.f}, WHITE);
}

void ModelController::unload()
{
    UnloadModel(model);
}