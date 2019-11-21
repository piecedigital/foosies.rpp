#include "bin/ggponet.h"

class Session
{
public:
    GGPOSession *ggpo;
    GGPOSessionCallbacks cb;
    GGPOPlayerHandle playerHandles[];

    Session();

    GGPOErrorCode start()
    {
        return ggpo_start_session(
            &ggpo,              // the new session object
            &cb,                // our callbacks
            (char *)"test_app", // application name
            2,                  // 2 players
            sizeof(int),        // size of an input packet
            8001);              // our local udp port
    }

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