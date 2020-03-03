#ifndef ACTIONS_H
#define ACTIONS_H

#include "globals.hpp"
#include "moves.hpp"

namespace Actions
{
bool checkMove(Move move, PlayerInput *);

Move *detectCommand(PlayerInput *playerInput, MoveList moveList, int meter);

MoveList moveListFromMove(Move move, MoveList fullMoveList);

void handleKnockdownTypeWindow(FrameData);
void handleKnockupKnockbackWindow(FrameData);
void handleLaunchWindow(FrameData);
void handlePushbackWindow(FrameData);
void handleDamageWindow(FrameData);
void handleStunWindow(FrameData);
void handleCancellableWindow(FrameData);
void handleInvincibilityWindow(FrameData);
void handleCounterHitStateWindow(FrameData);
void handleOverheadWindow(FrameData);
void handlePropulsionWindow(FrameData);
void handleFrameBoxData(FrameData);

};

#endif
