#include "foosiespp.hpp"

int main()
{
    // 1280, 720
    // 1920, 1080
    int screenWidth = 1280;
    int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "foosiespp");
    InitAudioDevice();
    Game game;
    return game.init();
}
