#ifndef MOVES_H
#define MOVES_H

#include "frame_data.hpp"

struct Move
{
    std::string name;
    std::string actionId;
    PlayerInput triggerBtn;
    FrameData frameData;
};

struct MoveList
{
    Move *moves;
    int movesSize;
};

#endif