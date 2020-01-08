#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include "deps/raylib/raylib.h"
#include "box.hpp"
#include "globals.hpp"

class Character
{
public:
    int bodyWidth;
    int bodyHeight;
    Color color;
    Model model;
    ModelAnimation anim;
    PlayerData **playerData;
    PlayerBoxes **playerBoxes;

    Character();
    ~Character();

    void render();
    void unload();
private:
    void _convertTranslation();
    void _renderBox(Box box);
};

#endif
