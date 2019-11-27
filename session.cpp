#include "session.h"

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
};

void Session::addPlayer(PlayerController *player, GGPOPlayerType type)
{
    int handleId = 0;

    // adds players
    player->ggpoPlayer.size = player->ggpoPlayer.size = sizeof(GGPOPlayer);
    player->ggpoPlayer.type = type;

    if (type == GGPO_PLAYERTYPE_LOCAL)
    {
        handleId = 1;
        strcpy_s(player->ggpoPlayer.u.remote.ip_address, "127.0.0.1");
        player->ggpoPlayer.u.remote.port = 8002;
    }

    GGPOErrorCode result1 = ggpo_add_player(ggpo, &player->ggpoPlayer, &playerHandles[handleId]);
}

GGPOErrorCode Session::synchronizeInputs()
{
    std::array<PlayerInput*, 2> inputs;
    inputs[0] = &player1->pd.input;
    inputs[1] = &player2->pd.input;

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
    std::cout << "Callback - beginGameCallback" << std::endl;
    return true;
};

bool saveGameStateCallback(unsigned char **buffer, int *len, int *checksum, int frame)
{
    std::cout << "Callback - saveGameStateCallback" << std::endl;
    return true;
};

bool loadGameStateCallback(unsigned char *buffer, int len)
{
    std::cout << "Callback - loadGameStateCallback" << std::endl;
    return true;
};

bool logGameStateCallback(char *filename, unsigned char *buffer, int len)
{
    std::cout << "Callback - logGameStateCallback" << std::endl;
    return true;
};

void freeBufferCallback(void *buffer)
{
    std::cout << "Callback - freeBufferCallback" << std::endl;
    return;
};

bool advanceFrameCallback(int flags)
{
    std::cout << "Callback - advanceFrameCallback" << std::endl;
    return true;
};

bool onEventCallback(GGPOEvent *info)
{
    std::cout << "Callback - onEventCallback" << std::endl;
    return true;
};
