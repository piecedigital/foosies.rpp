#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

struct Transform3
{
    int x;
    int y;
    int z;
};

enum PlayerInput
{
    NONE = 0,
    DIR_UP = 1 << 1,
    DIR_DOWN = 1 << 2,
    DIR_BACK = 1 << 3,
    DIR_TOWARD = 1 << 4,
    DIR_UPBACK = DIR_UP | DIR_BACK,
    DIR_UPTOWARD = DIR_UP | DIR_TOWARD,
    DIR_DOWNBACK = DIR_DOWN | DIR_BACK,
    DIR_DOWNTOWARD = DIR_DOWN | DIR_TOWARD,
    BTN_JAB = 1 << 9,
    BTN_STRONG = 1 << 10,
    BTN_FIERCE = 1 << 11,
    BTN_SHORT = 1 << 12,
    BTN_FORWARD = 1 << 13,
    BTN_ROUNDHOUSE = 1 << 14,
    BTN_MACRO1 = 1 << 15,
    BTN_MACRO2 = 1 << 16,
};

#endif
