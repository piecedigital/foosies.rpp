// /*******************************************************************************************
// *
// *   Test v1.0.0 - Tool Description
// *
// *   LICENSE: Propietary License
// *
// *   Copyright (c) 2019 raylib technologies. All Rights Reserved.
// *
// *   Unauthorized copying of this file, via any medium is strictly prohibited
// *   This project is proprietary and confidential unless the owner allows
// *   usage in any other form by expresely written permission.
// *
// **********************************************************************************************/

// #include "raylib/raylib.h"

// #define RAYGUI_IMPLEMENTATION
// #include "../bin/raygui.h"

// //----------------------------------------------------------------------------------
// // Controls Functions Declaration
// //----------------------------------------------------------------------------------


// //------------------------------------------------------------------------------------
// // Program main entry point
// //------------------------------------------------------------------------------------
// int main()
// {
//     // Initialization
//     //---------------------------------------------------------------------------------------
//     int screenWidth = 800;
//     int screenHeight = 450;

//     InitWindow(screenWidth, screenHeight, "test");

//     // test: controls initialization
//     //----------------------------------------------------------------------------------
//     // Define anchors
//     Vector2 anchor01 = { 151, 190 };            // ANCHOR ID:1
//     Vector2 anchor02 = { -53, -18 };            // ANCHOR ID:2

//     // Define controls variables
//     bool WindowBox000Active = true;            // WindowBox: WindowBox000
//     bool TextBox001EditMode = false;
//     char TextBox001Text[128] = "SAMPLE TEXT";            // TextBox: TextBox001
//     bool TextmultiBox002EditMode = false;
//     char TextmultiBox002Text[128] = "SAMPLE TEXT";            // TextmultiBox: TextmultiBox002
//     Vector2 ScrollPanel003ScrollOffset = { 0, 0 };
//     Vector2 ScrollPanel003BoundsOffset = { 0, 0 };            // ScrollPanel: ScrollPanel003

//     // Define controls rectangles
//     Rectangle layoutRecs[4] = {
//         { anchor01.x + 0, anchor01.y + 0, 402, 240 },    // WindowBox: WindowBox000
//         { anchor01.x + 10, anchor01.y + 72, 125, 25 },    // TextBox: TextBox001
//         { anchor01.x + 11, anchor01.y + 126, 125, 75 },    // TextmultiBox: TextmultiBox002
//         { anchor01.x + 145, anchor01.y + 31, 247, 200 },    // ScrollPanel: ScrollPanel003
//     };
//     //----------------------------------------------------------------------------------

//     SetTargetFPS(60);
//     //--------------------------------------------------------------------------------------

//     // Main game loop
//     while (!WindowShouldClose())    // Detect window close button or ESC key
//     {
//         // Update
//         //----------------------------------------------------------------------------------
//         // TODO: Implement required update logic
//         //----------------------------------------------------------------------------------

//         // Draw
//         //----------------------------------------------------------------------------------
//         BeginDrawing();

//             ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

//             // raygui: controls drawing
//             //----------------------------------------------------------------------------------
//             // Draw controls
//             if (WindowBox000Active)
//             {

//                 // WindowBox000Active = !GuiWindowBox(layoutRecs[0], "SAMPLE TEXT");
//                 // if (GuiTextBox(layoutRecs[1], (char*)TextBox001Text, 128, TextBox001EditMode)) TextBox001EditMode = !TextBox001EditMode;
//                 // if (GuiTextBoxMulti(layoutRecs[2], TextmultiBox002Text, 128, TextmultiBox002EditMode)) TextmultiBox002EditMode = !TextmultiBox002EditMode;
//                 Vector2 ScrollPanel003ScrollOffset;
//                 GuiScrollPanel({layoutRecs[3].x, layoutRecs[3].y, layoutRecs[3].width - ScrollPanel003BoundsOffset.x, layoutRecs[3].height - ScrollPanel003BoundsOffset.y }, layoutRecs[3], &ScrollPanel003ScrollOffset);
//             }
//             //----------------------------------------------------------------------------------

//         EndDrawing();
//         //----------------------------------------------------------------------------------
//     }

//     // De-Initialization
//     //--------------------------------------------------------------------------------------
//     CloseWindow();        // Close window and OpenGL context
//     //--------------------------------------------------------------------------------------

//     return 0;
// }

// //------------------------------------------------------------------------------------
// // Controls Functions Definitions (local)
// //------------------------------------------------------------------------------------



#include "foosiespp.hpp"

int main()
{
    // 1280, 720
    // 1920, 1080
    int screenWidth = 1280;
    int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "foosiespp");
    InitAudioDevice();
    LoadMusicStream("assets/audio/spawn.ogg");
    // PlayMusicStream(s);
    // AudioStream ss = s.stream;
    // rAudioBuffer **ab = &ss.buffer;
    // std::cout << (**ab) << std::endl;
    Game game;
    return game.init();
}
