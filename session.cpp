
#include "session.h"

Session::Session()
{
    Session::ggpo;
    Session::cb;

    /* fill in all callback functions */
    cb.begin_game = beginGameCallback;
    cb.save_game_state = saveGameStateCallback;
    cb.load_game_state = loadGameStateCallback;
    cb.log_game_state = logGameStateCallback;
    cb.free_buffer = freeBufferCallback;
    cb.advance_frame = advanceFrameCallback;
    cb.on_event = onEventCallback;
};

bool beginGameCallback(char *game)
{
    return true;
};

bool saveGameStateCallback(unsigned char **buffer, int *len, int *checksum, int frame)
{
    return true;
};

bool loadGameStateCallback(unsigned char *buffer, int len)
{
    return true;
};

bool logGameStateCallback(char *filename, unsigned char *buffer, int len)
{
    return true;
};

void freeBufferCallback(void *buffer)
{
    return;
};

bool advanceFrameCallback(int flags)
{
    return true;
};

bool onEventCallback(GGPOEvent *info)
{
    return true;
};
