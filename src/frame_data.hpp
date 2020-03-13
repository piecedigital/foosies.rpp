#ifndef FRAME_DATA_H
#define FRAME_DATA_H

#include "deps/nlohmann/json.hpp"
#include "./box.hpp"

using JSON = nlohmann::json;

struct frameWindow
{
    int firstFrameOfWindow;
    int lastFrameOfWindow;
};

enum KnockdownType {
    NORMAL = 0,
    HARD = 1 << 0,
    RESET = 1 << 1,
};

struct KnockdownTypeWindow : frameWindow
{
    KnockdownType knockdownType = KnockdownType::NORMAL;
};

struct KnockupKnockbackWindow : frameWindow
{
    int knockupValue;
    int knockbackValue;
};

struct LaunchWindow : frameWindow
{
    int launchValue;
};

struct PushbackWindow : frameWindow
{
    int pushbackOnHit;
    int pushbackOnBlock;
};

struct DamageWindow : frameWindow
{
    int damageOnHit;
    int damageOnBlock;
};

struct StunWindow : frameWindow
{
    int stunValue;
};

struct CancellableWindow : frameWindow
{
    int *cancelMoves;
    int cancelMovesSize;
};

struct InvincibilityWindow : frameWindow
{
    bool hitInvincibility;
    bool grabInvincibility;
    bool exHitInvincibility;
    bool exGrabInvincibility;
    bool superHitInvincibility;
    bool superGrabInvincibility;
};

struct CounterHitStateWindow : frameWindow
{
    bool isCounterHitable = false;
    float damageMultiplier = 1.2f;
    float stunMultiplier = 1.2f;
    float hitStunMultiplier = 1.2f;
    float launchMultiplier = 1.2f;
    float pushbackMultiplier = 1.2f;
    int counterHitOnlyCancellables;
    float multiplier = 1.2f;
    KnockdownType knockdownTypeOverride = KnockdownType::HARD;
};

struct OverheadWindow : frameWindow
{
    bool isOverhead = false;
};

struct PropulsionWindow : frameWindow
{
    int hSpeed;
    int vSpeed;
};

struct FrameBoxData
{
    int xOffset;
    int yOffset;
    int width;
    int height;
    BoxType boxType;
};

class FrameData
{
public:
    KnockdownTypeWindow *knockdownTypeWindow = NULL;
    int knockdownTypeWindowSize;
    KnockupKnockbackWindow *knockupKnockbackWindow = NULL;
    int knockupKnockbackWindowSize;
    LaunchWindow *launchWindow = NULL;
    int launchWindowSize;
    PushbackWindow *pushbackWindow = NULL;
    int pushbackWindowSize;
    DamageWindow *damageWindow = NULL;
    int damageWindowSize;
    StunWindow *stunWindow = NULL;
    int stunWindowSize;
    CancellableWindow *cancellableWindow = NULL;
    int cancellableWindowSize;
    InvincibilityWindow *invincibilityWindow = NULL;
    int invincibilityWindowSize;
    CounterHitStateWindow *counterHitStateWindow = NULL;
    int counterHitStateWindowSize;
    OverheadWindow *overheadWindow = NULL;
    int overheadWindowSize;
    PropulsionWindow *propulsionWindow = NULL;
    int propulsionWindowSize;

    FrameBoxData *frameBoxData = NULL;
    int frameBoxDataSize;

    void frameDataFromJSON(JSON json);
};

#endif
