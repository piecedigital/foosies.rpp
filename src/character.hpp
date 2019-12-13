#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include "../bin/raylib.h"
#include "box.hpp"
#include "globals.hpp"

namespace CharacterController
{


    struct Character
    {
        Color color;
        Model model;
        ModelAnimation anim;
        PlayerData **playerData;
        PlayerBoxes **playerBoxes;
    };

    void init();
    void unload();
    void render();

    void _convertTranslation();
    void _renderBox(Box box);
};

#endif
