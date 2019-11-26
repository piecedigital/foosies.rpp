#include <string>
#include "custom-types.h"

#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
public:
    int padId;
    const char *name;

    Controller(unsigned int padId, const char *name);
    Controller();
    InputNormalization getNormalizedInputs();

    bool _IsButtonDown(std::string button);
    bool _IsButtonPressed(std::string button);
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
