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
    // Font f = GetFontDefault();
    // Vector2 width = MeasureTextEx(f, title, 16.f, 16.f);
    // DrawRectangle(
    //     (int)transform.translation.x,
    //     (int)transform.translation.y,
    //     (int)(width.x + 10),
    //     (int)(width.y + 10),
    //     RED);
    int width = MeasureText(title, 16);
    rectangle.width = (int)(width + 10);
    rectangle.height = (int)(26);

    DrawRectangle(
        (int)rectangle.x,
        (int)rectangle.y,
        rectangle.width,
        rectangle.height,
        backgroundColor);

    DrawText(
        title,
        (int)rectangle.x + 5,
        (int)rectangle.y + 5,
        16,
        textColor);
}