#ifndef MOVES_H
#define MOVES_H

#include "frame_data.hpp"

struct Move
{
    bool available;
    const char *name;
    FrameData frameData;
};

struct MoveList
{
    Move HCF_Precise;
    Move HCB_Precise;
    Move DPF_Precise;
    Move DPF;
    Move DPB_Precise;
    Move DPB;
    Move QCF_Precise;
    Move QCB_Precise;
    Move FF;
    Move BB;
};

#endif