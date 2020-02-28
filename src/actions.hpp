#ifndef ACTIONS_H
#define ACTIONS_H

#include "globals.hpp"
#include "moves.hpp"

namespace Actions
{
bool checkMove(Move move, PlayerInput *);

Move *detectCommand(PlayerInput *, MoveList);
};

#endif
