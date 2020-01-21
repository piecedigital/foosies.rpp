#ifndef MODEL_H
#define MODEL_H

#include "deps/raylib/raylib.h"

class ModelController
{
public:
    int bodyWidth;
    int bodyHeight;
    float lightPos[3];
    Color color;
    Model model;
    int animCount;
    ModelAnimation *anim;

    ModelController();

    void init(const char *folder);
    void render(Vector3 translation, int rotation);
    void unload();
};

#endif
