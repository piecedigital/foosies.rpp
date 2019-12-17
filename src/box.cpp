#include <string>
#include "box.hpp"
#include "../bin/raylib.h"

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

    return selfBoxLeft <= otherBoxRight
        && selfBoxRight >= otherBoxLeft
        && selfBoxTop >= otherBoxBottom
        && selfBoxBottom <= otherBoxTop;
}

void Box::updateBoxShape(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Box::render()
{
    DrawTransform dt = _getDrawTransform();
    // std::cout
    //     << "X: " << dt.x
    //     << "Y: " << dt.y
    //     << "Width: " << dt.width
    //     << "Height: " << dt.height
    //     << std::endl;

    std::string s;
    s.append("X: ").append(std::to_string(dt.x)).append("\n")
        .append("Y: ").append(std::to_string(dt.y)).append("\n")
        .append("Width: ").append(std::to_string(dt.width)).append("\n")
        .append("Height: ").append(std::to_string(dt.height)).append("\n");
    DrawText(s.c_str(), 50, 20, 20, DARKGRAY);

    DrawModelEx(model, Vector3{dt.x, dt.y, 1.f}, {0.f, 1.f, 0.f}, 0.f, Vector3{dt.width, dt.height, 0.5f}, _getBoxColor(.5));
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
        (float)width,
        (float)height};
}
