#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include "bin/raylib.h"
#include "custom-types.hpp"

class Controller
{
public:
    int padId;
    const char *name;

    Controller(unsigned int padId, const char *name);
    Controller();
    NormalizedInput getNormalizedInputs();

    bool _IsInputDown(std::string button);
    bool _IsInputPressed(std::string button);
    void _axisRecalculate();
    bool _IsAxisTilted(std::string direction);
    bool _IsAxisJustTilted(std::string direction);
    void setPlayer(int player);

private:
    float axisThresholdH;
    float axisThresholdV;
    float axisAbsoluteH;
    float axisAbsoluteV;
    float axisChangedH;
    float axisChangedV;
    int player;
};

#endif
