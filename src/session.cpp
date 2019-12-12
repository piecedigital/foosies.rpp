#include "session.hpp"

GameState *gs;

Session::Session(Game *game)
{
    // gs = game;
    this->game = game;
    /* fill in all callback functions */
    cb.begin_game = beginGameCallback;
    cb.save_game_state = saveGameStateCallback;
    cb.load_game_state = loadGameStateCallback;
    cb.log_game_state = logGameStateCallback;
    cb.free_buffer = freeBufferCallback;
    cb.advance_frame = advanceFrameCallback;
    cb.on_event = onEventCallback;
};

Session::~Session()
{
    if (ggpo != NULL)
    {
        ggpo_close_session(ggpo);
    }

    if (player1 != NULL)
    {
        delete player1;
    }

    player1 = NULL;
    if (player2 != NULL)
    {
        delete player2;
    }
    player2 = NULL;
};

GGPOErrorCode Session::addPlayer(PlayerController *player, GGPOPlayerType type)
{
    int handleId = 0;

    // adds players
    player->ggpoPlayer.size = player->ggpoPlayer.size = sizeof(GGPOPlayer);
    player->ggpoPlayer.type = type;

    if (type == GGPO_PLAYERTYPE_REMOTE)
    {
        handleId = 1;
        Session::player2 = player;
        strcpy_s(player->ggpoPlayer.u.remote.ip_address, "127.0.0.1");
        player->ggpoPlayer.u.remote.port = 8002;
    }
    else
    {
        Session::player1 = player;
    }

    return ggpo_add_player(ggpo, &player->ggpoPlayer, &playerHandles[handleId]);
}

GGPOErrorCode Session::start()
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

GGPOErrorCode Session::synchronizeInputs()
{
    std::array<PlayerInput*, 2> inputs;
    inputs[0] = &player1->playerData->input;
    inputs[1] = &player2->playerData->input;

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

bool /*Session::*/beginGameCallback(char *game)
{
    #ifdef _DEBUG
    std::cout << "Callback - beginGameCallback" << std::endl;
    #endif
    return true;
};

bool /*Session::*/saveGameStateCallback(unsigned char **buffer, int *len, int *checksum, int frame)
{
    #ifdef _DEBUG
    std::cout << "Callback - saveGameStateCallback" << std::endl;
    #endif

    std::cout << "Clicked: Save State" << std::endl;
    *len = (int)sizeof(*gs);
    *buffer = (unsigned char *)malloc(*len);
    if (!*buffer)
    {
        return false;
    }
    memcpy(&buffer, gs, *len);

    return true;
};

bool /*Session::*/loadGameStateCallback(unsigned char *buffer, int len)
{
    #ifdef _DEBUG
    std::cout << "Callback - loadGameStateCallback" << std::endl;
    #endif

    std::cout << "Clicked: Load State" << std::endl;
    memcpy(gs, buffer, len);

    return true;
};

bool /*Session::*/logGameStateCallback(char *filename, unsigned char *buffer, int len)
{
    #ifdef _DEBUG
    std::cout << "Callback - logGameStateCallback" << std::endl;
    #endif
    return true;
};

void /*Session::*/freeBufferCallback(void *buffer)
{
    #ifdef _DEBUG
    std::cout << "Callback - freeBufferCallback" << std::endl;
    #endif
    return;
};

bool /*Session::*/advanceFrameCallback(int flags)
{
    #ifdef _DEBUG
    std::cout << "Callback - advanceFrameCallback" << std::endl;
    #endif
    return true;
};

bool /*Session::*/onEventCallback(GGPOEvent *info)
{
    #ifdef _DEBUG
    std::cout << "Callback - onEventCallback" << std::endl;
    #endif
    return true;
};
