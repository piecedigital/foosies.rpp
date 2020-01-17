#include <string>
#include "box.hpp"
#include "deps/raylib/raylib.h"

Box::Box()
{
    Mesh mesh = GenMeshCube(1.f, 1.f, 1.f);
    model = LoadModelFromMesh(mesh);
}

bool Box::isColliding(Box box)
{
    float selfBoxLeft = (float)x - (float)width / 2;
    float selfBoxRight = (float)x + (float)width / 2;
    float selfBoxTop = (float)y + (float)height / 2;
    float selfBoxBottom = (float)y - (float)height / 2;

    float otherBoxLeft = (float)box.x - (float)box.width / 2;
    float otherBoxRight = (float)box.x + (float)box.width / 2;
    float otherBoxTop = (float)box.y + (float)box.height / 2;
    float otherBoxBottom = (float)box.y - (float)box.height / 2;

    bool clash = selfBoxLeft <= otherBoxRight
        && selfBoxRight >= otherBoxLeft
        && selfBoxTop >= otherBoxBottom
        && selfBoxBottom <= otherBoxTop;

    return clash;
}

BoxIntersection Box::getIntersections(Box otherBox, int sideFace)
{
    float selfBoxLeft = (float)x - (float)width / 2;
    float selfBoxRight = (float)x + (float)width / 2;
    float selfBoxTop = (float)y + (float)height / 2;
    float selfBoxBottom = (float)y - (float)height / 2;

    float otherBoxLeft = (float)otherBox.x - (float)otherBox.width / 2;
    float otherBoxRight = (float)otherBox.x + (float)otherBox.width / 2;
    float otherBoxTop = (float)otherBox.y + (float)otherBox.height / 2;
    float otherBoxBottom = (float)otherBox.y - (float)otherBox.height / 2;

    BoxIntersection intersection = {0};

    if (x < otherBox.x || (x == otherBox.x && sideFace == 1))
    {
        intersection.x = std::abs(otherBoxLeft - selfBoxRight);
    }
    else if (x > otherBox.x || (x == otherBox.x && sideFace == -1))
    {
        intersection.x = std::abs(selfBoxLeft - otherBoxRight);
    }

    /*
    if (y < otherBox.y)
    {
        intersection.y = std::abs(otherBoxBottom - selfBoxTop);
    }
    else if (y > otherBox.y)
    {
        intersection.y = std::abs(selfBoxBottom - otherBoxTop);
    }
    */

    return intersection;
}

void Box::updateBox(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Box::render()
{
    DrawTransform dt = _getDrawTransform();

    DrawModelEx(model, Vector3{dt.x, dt.y, 1.f}, {0.f, 1.f, 0.f}, 0.f, Vector3{dt.width, dt.height, 0.5f}, _getBoxColor(.2));
}

Color Box::_getBoxColor(float opacity)
{
    Color color = BLACK;
    if (opacity < 0.f)
        opacity = 0.f;
    if (opacity > 1.f)
        opacity = 1.f;

    unsigned int alpha = (int)(255 * opacity);

    if (type == BoxType::BOX_PUSH)
        color = PUSH_BOX_COLOR;
    if (type == BoxType::BOX_GRAB)
        color = GRAB_BOX_COLOR;
    if (type == BoxType::BOX_HIT)
        color = HIT_BOX_COLOR;
    if (type == BoxType::BOX_HURT)
        color = HURT_BOX_COLOR;
    if (type == BoxType::BOX_PROXIMITY)
        color = PROXIMITY_BOX_COLOR;

    color.a = alpha;

    return color;
}

Color Box::_getBoxColor()
{
    return _getBoxColor(1);
}

DrawTransform Box::_getDrawTransform()
{
    return {
        (float)x / 100,
        (float)y / 100,
        (float)width / 100,
        (float)height / 100};
}
