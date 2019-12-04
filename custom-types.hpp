#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

#include "bin/raylib.h"

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
    int velocityH;
    int velocityV;
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
};

// enums
enum PlayerInput
{
    NONE = 0,
    DIR_UP = 1 << 1,
    DIR_DOWN = 1 << 2,
    DIR_BACK = 1 << 3,
    DIR_TOWARD = 1 << 4,
    DIR_UPBACK = DIR_UP + DIR_BACK,
    DIR_UPTOWARD = DIR_UP + DIR_TOWARD,
    DIR_DOWNBACK = DIR_DOWN + DIR_BACK,
    DIR_DOWNTOWARD = DIR_DOWN + DIR_TOWARD,
    BTN_JAB = 1 << 9,
    BTN_STRONG = 1 << 10,
    BTN_FIERCE = 1 << 11,
    BTN_SHORT = 1 << 12,
    BTN_FORWARD = 1 << 13,
    BTN_ROUNDHOUSE = 1 << 14,
    BTN_MACRO1 = 1 << 15,
    BTN_MACRO2 = 1 << 16,
};
inline PlayerInput operator~(PlayerInput a) { return (PlayerInput) ~(int)a; };
inline PlayerInput operator|(PlayerInput a, PlayerInput b) { return (PlayerInput)((int)a | (int)b); };
inline PlayerInput operator&(PlayerInput a, PlayerInput b) { return (PlayerInput)((int)a & (int)b); };
inline PlayerInput operator^(PlayerInput a, PlayerInput b) { return (PlayerInput)((int)a ^ (int)b); };

inline PlayerInput *operator|(PlayerInput *a, PlayerInput b) { return (PlayerInput *)((int &)a | (int)b); };
inline PlayerInput *operator&(PlayerInput *a, PlayerInput b) { return (PlayerInput *)((int &)a & (int)b); };

inline PlayerInput &operator|=(PlayerInput const &a, PlayerInput b) { return (PlayerInput &)((int &)a |= (int)b); };
inline PlayerInput *operator|=(PlayerInput const *a, PlayerInput b) { return (PlayerInput *)((int &)a |= (int)b); };
inline PlayerInput &operator&=(PlayerInput const &a, PlayerInput b) { return (PlayerInput &)((int &)a &= (int)b); };
inline PlayerInput &operator^=(PlayerInput const &a, PlayerInput b) { return (PlayerInput &)((int &)a ^= (int)b); };

// functions
inline bool hasFlag(PlayerInput v, PlayerInput flag)
{
    return (int)(v & flag) != 0;
};

inline void setFlag(PlayerInput &v, PlayerInput flag)
{
    v |= flag;
};

inline void clearEnum(PlayerInput &v)
{
    v = PlayerInput::NONE;
};

struct PlayerData
{
    int face = 1;
    int actionFace = 1;
    int dizzy = 1000;
    int vitality = 1000;
    PlayerInput input;
    Transform transform;
    Physical physical;
};

struct GameState
{
    int gameTimer = 90;
    PlayerData playerData[2];
};

#endif
