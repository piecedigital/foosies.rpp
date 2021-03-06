#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

#include "deps/raylib/raylib.h"
#include "box.hpp"

#define INPUT_HISTORY_MAX 30
#define INPUT_BUFFER_MAX 3

// structs
struct Physical
{
    int x;
    int y;
    int z;
    int gravity = 100;
    int drag = 50;
    int jumpSpeed = 40;
    int knockback;
    int pushback;
    int HSpeed;
    int VSpeed;
};

struct NormalizedInput
{
    int DIR_H = 0;
    int DIR_V = 0;
    bool FACE_UP = false;
    bool FACE_DOWN = false;
    bool FACE_LEFT = false;
    bool FACE_RIGHT = false;
    bool SHOULDER_L = false;
    bool SHOULDER_R = false;
    bool TRIGGER_L = false;
    bool TRIGGER_R = false;
    bool BACK = false;
    bool START = false;
    bool HOME = false;
};

struct StatusEffect
{
    int wallBounce;
    int wallSplat;
    int groundBounce;
    int groundSplat;
    int knockdownHard;
    int knockdownSoft;
};

// enums
enum PlayerInput
{
    NONE = 0,
    NO_DIR = 1 << 1, // 2
    NO_BTN = 1 << 2, // 4
    DIR_UP = 1 << 3, // 8
    DIR_DOWN = 1 << 4, // 16
    DIR_BACK = 1 << 5, // 32
    DIR_TOWARD = 1 << 6, // 64
    DIR_UPBACK = 1 << 7, // 128
    DIR_UPTOWARD = 1 << 8, // 256
    DIR_DOWNBACK = 1 << 9, // 512
    DIR_DOWNTOWARD = 1 << 10, // 1024
    DIR_ANY_UP = 1 << 11, // 2048
    DIR_ANY_DOWN = 1 << 12, // 4096
    DIR_ANY_BACK = 1 << 13, // 8192
    DIR_ANY_TOWARD = 1 << 14, // 16384
    DIR_LEFT = 1 << 15, // 32768
    DIR_RIGHT = 1 << 16, // 65536
    BTN_JAB = 1 << 17, // 131072
    BTN_STRONG = 1 << 18, // 262144
    BTN_FIERCE = 1 << 19, // 524288
    BTN_SHORT = 1 << 20, // 1048576
    BTN_FORWARD = 1 << 21, // 2097152
    BTN_ROUNDHOUSE = 1 << 22, // 4194304
    BTN_MACRO1 = 1 << 23, // 8388608
    BTN_MACRO2 = 1 << 24, // 16777216
};

// functions
template <class T>
bool hasFlag(T &v, T flag)
{
    return (v & flag) != 0;
};

template <class T>
void setFlag(T &v, T flag)
{
    v = (T)(v | flag);
};

template <class T>
void unsetFlag(T &v, T flag)
{
    v = (T)(v &~ flag);
};

template <class T>
void clearEnum(T &v)
{
    v = 0;
};

struct PlayerData
{
    int sideFace = 1;
    int actionFace = 1;
    int dizzy = 1000;
    int vitality = 1000;
    int meter;
    PlayerInput input;
    Transform transform;
    Physical physical;
    StatusEffect statusEffect;
};

struct PlayerBoxes
{
    Box *pushBoxArray;
    int pushBoxSize;
    Box *grabBoxesArray;
    int grabBoxesSize;
    Box *hitBoxesArray;
    int hitBoxesSize;
    Box *hurtBoxesArray;
    int hurtBoxesSize;
    Box *proximityBoxesArray;
    int proximityBoxesSize;
};

struct PlayerProjectiles
{
    Box *projectilesArray;
    int projectilesSize;
};

struct GameState
{
    int gameTimer = 90;
    PlayerInput inputHistory[2][INPUT_HISTORY_MAX];
    PlayerData playerData[2];
    PlayerBoxes playerBoxes[2];
    PlayerProjectiles playerProjectiles[2];
};

// inline int fGetTextWidth(const char* text)
// {
//     int lineCount = 0;
//     char newLine[2] = "\n";
//     const char **splitText = TextSplit(text, newLine, &lineCount);

//     int longestLine = 0;

//     for (int i = 0; i < lineCount; i++)
//     {
//         const char *line = (*splitText) + i;
//         int length = TextLength(line);
//         if (length > longestLine) longestLine = length;
//     }

//     return longestLine;
// }

#endif
