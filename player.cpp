#include "player.h"

PlayerController::PlayerController()
{
    pd.input = PlayerInput();
    pd.transform = Transform();
    pd.intTranslation = Transform3();

    ggpoPlayer = GGPOPlayer();
}

void PlayerController::update()
{
}

void PlayerController::render()
{
}
