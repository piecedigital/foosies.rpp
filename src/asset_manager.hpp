#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <vector>
#include "model.hpp"

namespace AssetManager
{
#define CHARACTER_COUNT 1

static ModelController models[CHARACTER_COUNT];
static int modelsCount = 0;
static ModelController * addModel(const char *folder);
};

ModelController *AssetManager::addModel(const char *folder)
{
    ModelController m = ModelController{};
    modelsCount++;
    models[modelsCount - 1] = m;
    models[modelsCount - 1].init(folder);
    return &models[modelsCount - 1];
}

#endif
