#include "game.hpp"

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "foosiespp");

    Game::init();

    return 0;
}
