#include "ggponet.h"

class Session
{
public:
    GGPOSession *ggpo;
    GGPOSessionCallbacks cb;

    Session();
};

bool beginGameCallback(char *game);
bool saveGameStateCallback(unsigned char **buffer, int *len, int *checksum, int frame);
bool loadGameStateCallback(unsigned char *buffer, int len);
bool logGameStateCallback(char *filename, unsigned char *buffer, int len);
void freeBufferCallback(void *buffer);
bool advanceFrameCallback(int flags);
bool onEventCallback(GGPOEvent *info);