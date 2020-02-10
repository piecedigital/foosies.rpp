#ifndef FRAME_DATA_H
#define FRAME_DATA_H

#include "deps/nlohmann/json.hpp"

using JSON = nlohmann::json;

typedef struct FrameData;

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
    FrameData *cancelMoves;
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
    FrameData *counterHitOnlyCancellables;
    float Multiplier = 1.2f;
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
};

class FrameData
{
public:
    KnockdownTypeWindow *knockdownTypeWindow;
    int knockdownTypeWindowSize;
    KnockupKnockbackWindow *knockupKnockbackWindow;
    int knockupKnockbackWindowSize;
    LaunchWindow *launchWindow;
    int launchWindowSize;
    PushbackWindow *pushbackWindow;
    int pushbackWindowSize;
    DamageWindow *damageWindow;
    int damageWindowSize;
    StunWindow *stunWindow;
    int stunWindowSize;
    CancellableWindow *cancellableWindow;
    int cancellableWindowSize;
    InvincibilityWindow *invincibilityWindow;
    int invincibilityWindowSize;
    CounterHitStateWindow *counterHitStateWindow;
    int counterHitStateWindowSize;
    OverheadWindow *overheadWindow;
    int overheadWindowSize;
    PropulsionWindow *propulsionWindow;
    int propulsionWindowSize;

    FrameBoxData *frameBoxData;
    int frameBoxDataSize;

    void frameDataFromJSON(JSON json)
    {
        // knockdownTypeWindow
        // knockupKnockbackWindow
        // launchWindow
        // pushbackWindow
        // damageWindow
        // stunWindow
        // cancellableWindow
        // invincibilityWindow
        // counterHitStateWindow
        // overheadWindow
        // propulsionWindow
        if (json.contains("frameBoxData"))
        {
            if (frameBoxData != NULL)
            {
                delete frameBoxData;
            }

            frameBoxDataSize = json["frameBoxData"].size();

            frameBoxData = new FrameBoxData[frameBoxDataSize];

            for (int i = 0; i < frameBoxDataSize; i++)
            {
                frameBoxData[i] = {
                    json["frameBoxData"]["xOffset"].get<int>(),
                    json["frameBoxData"]["yOffset"].get<int>(),
                    json["frameBoxData"]["width"].get<int>(),
                    json["frameBoxData"]["height"].get<int>()
                };
            }
        }
    }
};

#endif
