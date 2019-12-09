#include <string>
#include "box.hpp"
#include "bin/raylib.h"

Box::Box()
{
    Mesh mesh = GenMeshCube(1.f, 1.f, 1.f);
    model = LoadModelFromMesh(mesh);
}

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
    // std::cout
    //     << "X: " << rect.x
    //     << "Y: " << rect.y
    //     << std::endl;
    // DrawCube({
    //     rect.x,
    //     rect.y,
    //     1.f
    // },
    // rect.width,
    // rect.height,
    // 0.5f,
    // _getBoxColor(.5));

    DrawModelEx(model, Vector3{rect.x, rect.y, 1.f}, {0.f, 1.f, 0.f}, 0.f, Vector3{rect.width, rect.height, 0.5f}, _getBoxColor(.5));
}

Color Box::_getBoxColor(float opacity)
{
    Color color = BLACK;
    if (opacity < 0.f)
        opacity = 0.f;
    if (opacity > 1.f)
        opacity = 1.f;

    unsigned int alpha = 255 * opacity;

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
