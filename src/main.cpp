#include "foosiespp.hpp"

int main()
{
    // 1280, 720
    // 1920, 1080
    int screenWidth = 1280;
    int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "foosiespp");
    InitAudioDevice();
    Music s = LoadMusicStream("assets/audio/spawn.mp3");
    // PlayMusicStream(s);
    AudioStream ss = s.stream;
    rAudioBuffer **ab = &ss.buffer;
    // auto d = (**ab).buffer[0];
    auto d = (**ab).bufferSizeInFrames;
    std::cout << d << std::endl;
    Game game;
    return game.init();
}
