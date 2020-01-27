#ifndef JSON_HANDLE_H
#define JSON_HANDLE_H

#include "deps/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

using JSON = nlohmann::json;

#define OPEN_BRACE "{"
#define CLOSE_BRACE "}"
#define OPEN_SQUARE "["
#define CLOSE_SQUARE "]"
#define QUOTE "\""

namespace JsonHandler
{
    // if I make my own parser I'll come back to this
    /*
    enum JsonType
    {
        UNKNOWN = 0,
        // char*
        STRING,
        // double
        NUMBER,
        // JsonType
        OBJECT,
        // JsonType*
        ARRAY
    };

    struct JsonRep
    {
        JsonType type;
        bool isSet;
        void *value;
    };
    */

    static JSON parseJsonFile(const char *data)
    {
        return JSON::parse(data);
    };

    static JSON loadJsonFile(const char *filename)
    {
        std::ifstream file;
        file.open(filename);

        std::string data[100];
        std::string lineOfData;
        int lineCount = 0;

        if (file.is_open())
        {
            while (!file.eof())
            {
                std::getline(file,lineOfData);
                data[lineCount] = lineOfData;
                lineCount++;
            }
        }
        else
        {
            return "{}"_json;
        }

        file.close();

        std::string stitchedString;

        for (int i = 0; i < lineCount; i++)
        {
            stitchedString.append(data[i]);
        }

        return parseJsonFile(stitchedString.c_str());
    };

    static bool saveJsonFile(const char *filename, JSON data)
    {
        std::ofstream file;
        file.open(filename);
        file << data.dump();
        file.close();
    };
};

#endif
