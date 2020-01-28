// #include "json_handler.hpp"
// #include <iostream>
// #include <string>

// int main()
// {
//     JSON json = JsonHandler::loadJsonFile("assets/sample.json");
//     std::cout << json.dump() << std::endl;
//     std::cout << "Name: " << json["name"].get<std::string>() << std::endl;
//     std::cout << "Owns: " << json["owns"]["likes"].get<JSON::array_t>() << std::endl;
//     // std::cout << "Name: " << json.dump() << std::endl;

//     return 0;
// }

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
