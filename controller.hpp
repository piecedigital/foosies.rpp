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
    NormalizedInput inputs;

    Controller(unsigned int padId, const char *name);
    Controller();
    void pollNormalizedInputs();

    bool _IsInputDown(std::string button);
    bool _IsInputPressed(std::string button);
    void _axisRecalculate();
    bool _IsAxisTilted(std::string direction);
    bool _IsAxisJustTilted(std::string direction);

private:
    float axisThresholdH;
    float axisThresholdV;
    float axisAbsoluteH;
    float axisAbsoluteV;
    float axisChangedH;
    float axisChangedV;

    void _resetInputs();
};

#endif
