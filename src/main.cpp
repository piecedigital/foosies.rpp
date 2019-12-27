// #include "foosiespp.hpp"

// int main()
// {
//     int screenWidth = 800;
//     int screenHeight = 450;
//     InitWindow(screenWidth, screenHeight, "foosiespp");

//     Game game;
//     return game.init();
// }

//============================================================================
// Name        : Duel Cubes
// Author      : Gamepro5
// Version     :
// Copyright   : © Gamepro5
// Description : 3D Shooter by Gamepro5
//============================================================================

#include "../bin/raylib.h"
#include <math.h>
#include <iostream>
using namespace std;
#include <string>

class person
{
public:
    string name, type, model, collisionBox;
    Camera camera;
    int health, defense;
    //property setting
    /*
  void collisionBox = DrawRectangle(int posX, int posY, int width, int height, Color color);

  Camera camera = { 0 };
  camera.position = (Vector3){ 4.0f, 2.0f, 4.0f };
  camera.target = (Vector3){ 0.0f, 1.8f, 0.0f };  // a struct!
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
  camera.fovy = 60.0f;
  camera.type = CAMERA_PERSPECTIVE;
  //end of property setting
  */
    person(string x, string y)
    { //constructor
        name = x;
        type = y;
        //collisionBox = DrawRectangle(int posX, int posY, int width, int height, Color color);
        camera = {0};
        camera.position = {4.0f, 2.0f, 4.0f};
        camera.target = {0.0f, 1.8f, 0.0f}; // a struct!
        camera.up = {0.0f, 1.0f, 0.0f};
        camera.fovy = 60.0f;
        camera.type = CAMERA_PERSPECTIVE;

        SetCameraMode(camera, CAMERA_FIRST_PERSON);

        SetTargetFPS(120);
    };
    void localloop()
    {
        if (IsKeyDown(KEY_W))
        {
            camera.position.x -= 0.5f;
        };
        if (IsKeyDown(KEY_A))
        {
            camera.position.x -= 0.5f;
        };
        if (IsKeyDown(KEY_S))
        {
            camera.position.z -= 0.5f;
        };
        if (IsKeyDown(KEY_D))
        {
            camera.position.z += 0.5f;
        };
        BeginMode3D(camera);
        UpdateCamera(&camera);
        //rendering list?
        ClearBackground(RAYWHITE);

        DrawCube({2.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 2.0f, {255, 0, 0, 255});

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndMode3D();
    };
};

int main(void)
{
    InitWindow(1080, 540, "Gamepro5's Engine Test");

    /*
    wKeyPressed = undefined;
    aKeyPressed = undefined;
    KeyPressed = undefined;
*/
    person phongie("phongie", "player");

    while (!WindowShouldClose())
    {
        //UpdateCamera(phongie.camera);

        BeginDrawing();

        phongie.localloop();

        EndDrawing();
    };

    return 0;
}
