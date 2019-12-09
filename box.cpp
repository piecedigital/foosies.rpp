#include <string>
#include "box.hpp"
#include "bin/raylib.h"

Box::Box()
{}

bool Box::isColliding(Box box)
{
    return CheckCollisionRecs(rect, box.rect);
}

void Box::updateBoxShape(float x, float y, float width, float height)
{
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
}

void Box::updateBoxShape(Vector3 vect, float width, float height)
{
    rect.x = vect.x;
    rect.y = vect.y;
    rect.width = width;
    rect.height = height;
}

void Box::render()
{
    DrawCube({
        rect.x,
        rect.y,
        1.f
    },
    rect.width,
    rect.height,
    0.5f,
    _getBoxColor());
}

Color Box::_getBoxColor()
{
    if (type == BoxType::BOX_PUSH)
        return PUSH_BOX_COLOR;
    if (type == BoxType::BOX_GRAB)
        return GRAB_BOX_COLOR;
    if (type == BoxType::BOX_HIT)
        return HIT_BOX_COLOR;
    if (type == BoxType::BOX_HURT)
        return HURT_BOX_COLOR;
    if (type == BoxType::BOX_PROXIMITY)
        return PROXIMITY_BOX_COLOR;
    return BLACK;
}
