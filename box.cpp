#include "box.hpp"

Box::Box()
{}

bool Box::isColliding(Box box)
{
    CheckCollisionRecs(rect, box.rect);
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
