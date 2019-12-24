#ifndef BOX_H
#define BOX_H

#include <iostream>
#include "../bin/raylib.h"

#define PUSH_BOX_COLOR Color{253, 249, 0, 255};
#define GRAB_BOX_COLOR Color{0, 121, 241, 255};
#define HIT_BOX_COLOR Color{230, 41, 55, 255};
#define HURT_BOX_COLOR Color{0, 228, 48, 255};
#define PROXIMITY_BOX_COLOR Color{253, 249, 100, 255};

struct DrawTransform
{
    float x;
    float y;
    float width;
    float height;
};

struct BoxIntersection
{
    int x;
    // int y;
};

enum BoxType
{
    BOX_NONE = 0,
    BOX_PUSH,
    BOX_GRAB,
    BOX_HIT,
    BOX_HURT,
    BOX_PROXIMITY,
};

class Box
{
public:
    BoxType type;
    Model model;
    int x;
    int y;
    int width;
    int height;

    Box();

    void updateBox(int x, int y, int width, int height);

    bool isColliding(Box box);
    BoxIntersection getIntersections(Box otherBox, int sideFace);
    void render();
private:
    Color _getBoxColor();
    Color _getBoxColor(float opacity);
    DrawTransform _getDrawTransform();
};

#endif
