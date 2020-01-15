#ifndef MODEL_H
#define MODEL_H

#include "deps/raylib/raylib.h"

class ModelWrapper
{
public:
    int bodyWidth;
    int bodyHeight;
    float lightPos[3];
    Color color;
    Model model;
    ModelAnimation anim;

    ModelWrapper();
    ~ModelWrapper();

    void render(Vector3 translation, int rotation);
    void unload();
};

#endif
