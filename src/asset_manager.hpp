#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <vector>
#include "model.hpp"

namespace AssetManager
{
#define CHARACTER_COUNT 1

static ModelController models[CHARACTER_COUNT];
static int modelsSize = 0;
static ModelController * addModel(const char *folder)
{
    ModelController m = ModelController{};
    modelsSize++;
    models[modelsSize - 1] = m;
    models[modelsSize - 1].init(folder);
    return &models[modelsSize - 1];
};
};

#endif
