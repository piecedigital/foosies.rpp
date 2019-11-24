#include "session.h"

using namespace std;

Session::Session()
{
    Session::ggpo;
    Session::cb;
    Session::playerHandles;

    /* fill in all callback functions */
    cb.begin_game = beginGameCallback;
    cb.save_game_state = saveGameStateCallback;
    cb.load_game_state = loadGameStateCallback;
    cb.log_game_state = logGameStateCallback;
    cb.free_buffer = freeBufferCallback;
    cb.advance_frame = advanceFrameCallback;
    cb.on_event = onEventCallback;

    // adds players
    Session::player1 = Session::player2 = PlayerController();
    player1.ggpoPlayer.size = player2.ggpoPlayer.size = sizeof(GGPOPlayer);
    player1.ggpoPlayer.type = GGPO_PLAYERTYPE_LOCAL;
    player2.ggpoPlayer.type = GGPO_PLAYERTYPE_REMOTE;

    strcpy_s(player2.ggpoPlayer.u.remote.ip_address, "127.0.0.1");
    player2.ggpoPlayer.u.remote.port = 8002;

    GGPOErrorCode result1 = ggpo_add_player(ggpo, &player1.ggpoPlayer, &playerHandles[0]);
    GGPOErrorCode result2 = ggpo_add_player(ggpo, &player2.ggpoPlayer, &playerHandles[1]);
};

GGPOErrorCode Session::synchronizeInputs()
{
    array<PlayerInput*, 2> inputs;
    inputs[0] = &player1.pd.input;
    inputs[1] = &player2.pd.input;

    GGPOErrorCode result;

    for (size_t i = 0; i < inputs.size(); i++)
    {
        /* notify ggpo of the local player's inputs */
        result = ggpo_add_local_input(
            ggpo,               // the session object
            playerHandles[i],   // handle for p1
            &inputs[i],         // p1's inputs
            sizeof(inputs[i])); // size of p1's inputs
    }

    int flag;

    /* synchronize the local and remote inputs */
    if (GGPO_SUCCEEDED(result))
    {
        result = ggpo_synchronize_input(
            ggpo,            // the session object
            &inputs,          // array of inputs
            sizeof(inputs),
            &flag); // size of all inputs
    }

    return result;
}

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
