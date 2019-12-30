/*******************************************************************************************
*
*   Test v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2019 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "deps/raylib/raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "deps/raylib/raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "test");
    GuiLoadStyle("ui/dev/default.rgs");

    // test: controls initialization
    //----------------------------------------------------------------------------------
    // Define anchors
    Vector2 anchor01 = {10, 10}; // ANCHOR ID:1

    // Define controls variables
    bool TextBox001EditMode = false;
    unsigned char TextBox001Text[128] = "<Move Name>";            // TextBox: TextBox001
    bool TextmultiBox002EditMode = false;
    unsigned char TextmultiBox002Text[128] = "description";            // TextmultiBox: TextmultiBox002
    Vector2 ScrollPanel003ScrollOffset = { 0, 0 };
    Vector2 ScrollPanel003BoundsOffset = { 0, 0 };            // ScrollPanel: ScrollPanel003

    // Define controls rectangles
    Rectangle layoutRecs[4] = {
        { anchor01.x + 5, anchor01.y + 30, 145, 25 },    // TextBox: TextBox001
        { anchor01.x + 5, anchor01.y + 60, 145, 195 },    // TextmultiBox: TextmultiBox002
        { anchor01.x + 155, anchor01.y + 30, 270, 225 },    // ScrollPanel: ScrollPanel003
        { anchor01.x + 0, anchor01.y + 10, 430, 250 },    // GroupBox: GroupBox004
    };
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            // Draw controls
            if (GuiTextBox(layoutRecs[0], (char *)TextBox001Text, 128, TextBox001EditMode)) TextBox001EditMode = !TextBox001EditMode;
            if (GuiTextBoxMulti(layoutRecs[1], (char *)TextmultiBox002Text, 128, TextmultiBox002EditMode)) TextmultiBox002EditMode = !TextmultiBox002EditMode;
            GuiScrollPanel({layoutRecs[2].x, layoutRecs[2].y, layoutRecs[2].width - ScrollPanel003BoundsOffset.x, layoutRecs[2].height - ScrollPanel003BoundsOffset.y }, layoutRecs[2], &ScrollPanel003ScrollOffset);
            GuiGroupBox(layoutRecs[3], "Move Panel");
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------



// #include "foosiespp.hpp"

// int main()
// {
//     // 1280, 720
//     // 1920, 1080
//     int screenWidth = 1280;
//     int screenHeight = 720;
//     InitWindow(screenWidth, screenHeight, "foosiespp");
//     InitAudioDevice();
//     LoadMusicStream("assets/audio/spawn.mp3");
//     // PlayMusicStream(s);
//     // AudioStream ss = s.stream;
//     // rAudioBuffer **ab = &ss.buffer;
//     // std::cout << (**ab) << std::endl;
//     Game game;
//     return game.init();
// }
