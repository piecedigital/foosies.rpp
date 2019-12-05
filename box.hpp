#ifndef BOX_H
#define BOX_H

#include "bin/raylib.h"

enum boxType
{
    BOX_NONE = 0,
    BOX_HIT,
    BOX_HURT,
    BOX_PROXIMITY,
    BOX_PUSH,
};

class Box
{
public:
    Rectangle rect;

    Box();

    void updateBoxShape(float x, float y, float width, float height);
    void updateBoxShape(Vector3 vect, float width, float height);

    bool isColliding(Box box);
};

#endif
