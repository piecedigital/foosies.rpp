#ifndef SESSIONS_H
#define SESSIONS_H

#include <iostream>
#include <cstring>
#include <array>
#include "bin/ggponet.h"
#include "player.hpp"

class Session
{
public:
    int maxPlayers;
    int maxSpectators;
    GGPOSession *ggpo;
    GGPOSessionCallbacks cb;
    PlayerController *player1, *player2;
    // std::array<GGPOPlayerHandle, 2> playerHandles;
    GGPOPlayerHandle playerHandles[2];

    Session();
    ~Session();

    GGPOErrorCode start()
    {
        maxPlayers = 2;
        maxSpectators = 0;

        return ggpo_start_session(
            &ggpo,              // the new session object
            &cb,                // our callbacks
            (char *)"test_app", // application name
            2,                  // 2 players
            sizeof(int),        // size of an input packet
            8001);              // our local udp port
    }

    void addPlayer(PlayerController *player, GGPOPlayerType type);

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
