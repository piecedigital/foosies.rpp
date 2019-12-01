#include "button.hpp"

Button::Button()
{
}

Button::~Button()
{
    callbacks.onClick = NULL;
}

void Button::init(const char *title, Vector3 position)
{
    Button::title = title;
    transform.translation = position;
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

    DrawRectangle(
        (int)transform.translation.x,
        (int)transform.translation.y,
        (int)(width + 10),
        (int)(26),
        RED);

    DrawText(
        title,
        (int)transform.translation.x + 5,
        (int)transform.translation.y + 5,
        16,
        WHITE);
}