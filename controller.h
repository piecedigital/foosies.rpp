#include <string>
#include "custom-types.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
    float axisThresholdH;
    float axisThresholdV;
    float axisAbsoluteH;
    float axisAbsoluteV;
    float axisChangedH;
    float axisChangedV;

public:
    int padId;
    const char *name;

    Controller(unsigned int padId, const char *name);
    InputNormalization getNormalizedInputs();

    void _axisRecalculate();
    bool _axisJustTilted(std::string direction);
};

#endif
