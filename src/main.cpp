#include "foosiespp.hpp"

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "foosiespp");

    Game game;
    return game.init();
}
