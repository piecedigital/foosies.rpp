#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include "bin/raylib.h"
#include "custom-types.hpp"

class Character
{
public:
    Color color;
    Model model;
    ModelAnimation anim;
    PlayerData **pd;

    Character();
    ~Character();

    void render();
    void unload();
private:
    void _convertTranslation();
};

#endif
