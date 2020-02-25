#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
#include "deps/raylib/raylib.h"
#include "box.hpp"
#include "globals.hpp"
#include "actions.hpp"
#include "model.hpp"
#include "moves.hpp"

class Character
{
public:
    ModelController *model;
    PlayerData **playerData;
    PlayerBoxes **playerBoxes;
    MoveList moveList;
    int towardHSpeed;
    int backHSpeed;
    int accellerationH;

    Character();
    ~Character();

    void render();
    void unload();
private:
    void _convertTranslation();
    void _renderBox(Box box);
};

#endif
