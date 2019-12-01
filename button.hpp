#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "bin/raylib.h"

struct ButtonCallbacks
{
    void (*onClick)();
};

class Button
{
public:
    const char *title;
    ButtonCallbacks callbacks;
    Transform transform;

    Button();
    ~Button();

    void init(const char *title, Vector3 position);
    void render();
};

#endif
