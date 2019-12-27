#include <iostream>
#include "button.hpp"

Button::Button()
{
}

Button::~Button()
{
    callbacks.onClick = NULL;
}

void Button::init(const char *title, Vector2 position)
{
    Button::title = title;
    rectangle.x = position.x;
    rectangle.y = position.y;
}

void Button::update()
{
    backgroundColor = RED;
    textColor = WHITE;

    int width = MeasureText(title, 16);
    rectangle.width = (float)(width + 10);
    rectangle.height = (float)(26);

    bool inBox = CheckCollisionPointRec(
        GetMousePosition(),
        rectangle
        );
    if (inBox)
    {
        backgroundColor = BLACK;
        textColor = RED;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            clicked();
        }
    }
}

void Button::clicked()
{
    if (callbacks.onClick != NULL)
        callbacks.onClick();
}

void Button::render()
{
    DrawRectangle(
        (int)rectangle.x,
        (int)rectangle.y,
        (int)rectangle.width,
        (int)rectangle.height,
        backgroundColor);

    DrawText(
        title,
        (int)rectangle.x + 5,
        (int)rectangle.y + 5,
        16,
        textColor);
}
