#include "iostream"
#include "cstring"
#include "session.h"

using namespace std;

Session::Session()
{
    Session::ggpo;
    Session::cb;
    Session::playerHandles[2];

    /* fill in all callback functions */
    cb.begin_game = beginGameCallback;
    cb.save_game_state = saveGameStateCallback;
    cb.load_game_state = loadGameStateCallback;
    cb.log_game_state = logGameStateCallback;
    cb.free_buffer = freeBufferCallback;
    cb.advance_frame = advanceFrameCallback;
    cb.on_event = onEventCallback;

    // adds players
    GGPOPlayer p1, p2;
    p1.size = p2.size = sizeof(GGPOPlayer);
    p1.type = GGPO_PLAYERTYPE_LOCAL;
    p2.type = GGPO_PLAYERTYPE_REMOTE;

    strcpy(p2.u.remote.ip_address, "127.0.0.1");
    p2.u.remote.port = 8002;

    GGPOErrorCode result = ggpo_add_player(ggpo, &p1, &playerHandles[0]);
    GGPOErrorCode result = ggpo_add_player(ggpo, &p2, &playerHandles[0]);
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
