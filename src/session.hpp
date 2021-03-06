#ifndef SESSIONS_H
#define SESSIONS_H

#include <iostream>
#include <cstring>
#include <array>
#include "../bin/ggponet.h"
#include "player.hpp"

struct ConnectionInfo
{
    bool local;
    std::string address;
    std::string port;
};

class Session
{
public:
    int maxPlayers;
    int maxSpectators;
    GGPOSession *ggpo;
    GGPOSessionCallbacks cb;
    PlayerController *player1, *player2;
    GGPOPlayerHandle playerHandles[2];

    Session(GameState *gs);
    ~Session();

    GGPOErrorCode start();

    GGPOErrorCode addPlayer(PlayerController *player, GGPOPlayerType type);

    GGPOErrorCode synchronizeInputs();

    GGPOErrorCode end()
    {
        return ggpo_close_session(ggpo);
    }
};

bool beginGameCallback(char *game);
bool saveGameStateCallback(unsigned char **buffer, int *len, int *checksum, int frame);
bool loadGameStateCallback(unsigned char *buffer, int len);
bool logGameStateCallback(char *filename, unsigned char *buffer, int len);
void freeBufferCallback(void *buffer);
bool advanceFrameCallback(int flags);
bool onEventCallback(GGPOEvent *info);

#endif
