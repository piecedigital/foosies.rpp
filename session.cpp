#include "iostream"
#include "session.h"

using namespace std;

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
    cout << "Callback - beginGameCallback";
    return true;
};

bool saveGameStateCallback(unsigned char **buffer, int *len, int *checksum, int frame)
{
    cout << "Callback - saveGameStateCallback";
    return true;
};

bool loadGameStateCallback(unsigned char *buffer, int len)
{
    cout << "Callback - loadGameStateCallback";
    return true;
};

bool logGameStateCallback(char *filename, unsigned char *buffer, int len)
{
    cout << "Callback - logGameStateCallback";
    return true;
};

void freeBufferCallback(void *buffer)
{
    cout << "Callback - freeBufferCallback";
    return;
};

bool advanceFrameCallback(int flags)
{
    cout << "Callback - advanceFrameCallback";
    return true;
};

bool onEventCallback(GGPOEvent *info)
{
    cout << "Callback - onEventCallback";
    return true;
};
