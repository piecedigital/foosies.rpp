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

int main(int argCount, char **argv)
{
    // 1280, 720
    // 1920, 1080
    ConnectionInfo ci;
    ci.local = !(argCount == 2);
    std::string *theInfo = NULL;

    for (size_t i = 0; i < argCount; i++)
    {
        if (theInfo != NULL)
        {
            *theInfo = argv[i];
            theInfo = NULL;
            continue;
        }

        if (std::string(argv[i]) == "--address")
        {
            theInfo = &ci.address;
        }
        else if (std::string(argv[i]) == "--port")
        {
            theInfo = &ci.port;
        }
    }

    theInfo = NULL;
    std::cout << "Address: " << ci.address << std::endl;
    std::cout << "Port: " << ci.port << std::endl;

    int screenWidth = 1280;
    int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "foosiespp");
    InitAudioDevice();
    Game game;
    return game.init(ci);
}
