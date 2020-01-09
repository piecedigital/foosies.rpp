#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "deps/raylib/raylib.h";

struct ButtonCallbacks
{
    void (*onClick)();
};

class Button
{
public:
    const char *title;
    ButtonCallbacks callbacks;
    Rectangle rectangle;
    Color backgroundColor = RED;
    Color textColor = WHITE;

    Button();
    ~Button();

    void init(const char *title, Vector2 position);
    void update();
    void render();
private:
    void clicked();
};

#endif
