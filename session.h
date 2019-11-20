#include "bin/ggponet.h"

class Session
{
public:
    GGPOSession *ggpo;
    GGPOSessionCallbacks cb;

    Session();

    void endSession()
    {
        ggpo_close_session(ggpo);
    }
};

bool beginGameCallback(char *game);
bool saveGameStateCallback(unsigned char **buffer, int *len, int *checksum, int frame);
bool loadGameStateCallback(unsigned char *buffer, int len);
bool logGameStateCallback(char *filename, unsigned char *buffer, int len);
void freeBufferCallback(void *buffer);
bool advanceFrameCallback(int flags);
bool onEventCallback(GGPOEvent *info);