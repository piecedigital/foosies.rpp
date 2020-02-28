#ifndef MOVES_H
#define MOVES_H

#include "frame_data.hpp"

struct Move
{
    std::string name;
    PlayerInput *triggerBtn;
    int triggerBtnSize;
    int triggerBtnCombo;
    PlayerInput *commandSequence;
    int commandSequenceSize;
    int meterCost;
    FrameData frameData;
};

struct MoveList
{
    Move *moves;
    int movesSize;
};

#endif