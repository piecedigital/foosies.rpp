#ifndef FRAME_DATA_H
#define FRAME_DATA_H

#include "deps/nlohmann/json.hpp"

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
    int cancelMoves;
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
        if (json.contains("knockdownTypeWindow"))
        {
            if (knockdownTypeWindow != NULL)
            {
                delete knockdownTypeWindow;
            }

            knockdownTypeWindowSize = json["knockdownTypeWindow"].size();

            knockdownTypeWindow = new KnockdownTypeWindow[knockdownTypeWindowSize];

            for (int i = 0; i < knockdownTypeWindowSize; i++)
            {
                knockdownTypeWindow[i] = {
                    json["knockdownTypeWindow"]["knockdownType"].get<KnockdownType>(),
                };
            }
        }

        if (json.contains("knockupKnockbackWindow"))
        {
            if (knockupKnockbackWindow != NULL)
            {
                delete knockupKnockbackWindow;
            }

            knockupKnockbackWindowSize = json["knockupKnockbackWindow"].size();

            knockupKnockbackWindow = new KnockupKnockbackWindow[knockupKnockbackWindowSize];

            for (int i = 0; i < knockupKnockbackWindowSize; i++)
            {
                knockupKnockbackWindow[i] = {
                    json["knockupKnockbackWindow"]["knockupValue"].get<int>(),
                    json["knockupKnockbackWindow"]["knockbackValue"].get<int>(),
                };
            }
        }

        if (json.contains("launchWindow"))
        {
            if (launchWindow != NULL)
            {
                delete launchWindow;
            }

            launchWindowSize = json["launchWindow"].size();

            launchWindow = new LaunchWindow[launchWindowSize];

            for (int i = 0; i < launchWindowSize; i++)
            {
                launchWindow[i] = {
                    json["launchWindow"]["launchValue"].get<int>(),
                };
            }
        }

        if (json.contains("pushbackWindow"))
        {
            if (pushbackWindow != NULL)
            {
                delete pushbackWindow;
            }

            pushbackWindowSize = json["pushbackWindow"].size();

            pushbackWindow = new PushbackWindow[pushbackWindowSize];

            for (int i = 0; i < pushbackWindowSize; i++)
            {
                pushbackWindow[i] = {
                    json["pushbackWindow"]["pushbackOnHit"].get<int>(),
                    json["pushbackWindow"]["pushbackOnBlock"].get<int>(),
                };
            }
        }

        if (json.contains("damageWindow"))
        {
            if (damageWindow != NULL)
            {
                delete damageWindow;
            }

            damageWindowSize = json["damageWindow"].size();

            damageWindow = new DamageWindow[damageWindowSize];

            for (int i = 0; i < damageWindowSize; i++)
            {
                damageWindow[i] = {
                    json["damageWindow"]["damageOnHit"].get<int>(),
                    json["damageWindow"]["damageOnBlock"].get<int>(),
                };
            }
        }

        if (json.contains("stunWindow"))
        {
            if (stunWindow != NULL)
            {
                delete stunWindow;
            }

            stunWindowSize = json["stunWindow"].size();

            stunWindow = new StunWindow[stunWindowSize];

            for (int i = 0; i < stunWindowSize; i++)
            {
                stunWindow[i] = {
                    json["stunWindow"]["stunValue"].get<int>(),
                };
            }
        }

        if (json.contains("cancellableWindow"))
        {
            if (cancellableWindow != NULL)
            {
                delete cancellableWindow;
            }

            cancellableWindowSize = json["cancellableWindow"].size();

            cancellableWindow = new CancellableWindow[cancellableWindowSize];

            for (int i = 0; i < cancellableWindowSize; i++)
            {
                cancellableWindow[i] = {
                    json["cancellableWindow"]["cancelMoves"].get<int>(),
                };
            }
        }

        if (json.contains("invincibilityWindow"))
        {
            if (invincibilityWindow != NULL)
            {
                delete invincibilityWindow;
            }

            invincibilityWindowSize = json["invincibilityWindow"].size();

            invincibilityWindow = new InvincibilityWindow[invincibilityWindowSize];

            for (int i = 0; i < invincibilityWindowSize; i++)
            {
                invincibilityWindow[i] = {
                    json["invincibilityWindow"]["hitInvincibility"].get<bool>(),
                    json["invincibilityWindow"]["grabInvincibility"].get<bool>(),
                    json["invincibilityWindow"]["exHitInvincibility"].get<bool>(),
                    json["invincibilityWindow"]["exGrabInvincibility"].get<bool>(),
                    json["invincibilityWindow"]["superHitInvincibility"].get<bool>(),
                    json["invincibilityWindow"]["superGrabInvincibility"].get<bool>(),
                };
            }
        }

        if (json.contains("counterHitStateWindow"))
        {
            if (counterHitStateWindow != NULL)
            {
                delete counterHitStateWindow;
            }

            counterHitStateWindowSize = json["counterHitStateWindow"].size();

            counterHitStateWindow = new CounterHitStateWindow[counterHitStateWindowSize];

            for (int i = 0; i < counterHitStateWindowSize; i++)
            {
                counterHitStateWindow[i] = {
                    json["counterHitStateWindow"]["isCounterHitable"].get<bool>(),
                    json["counterHitStateWindow"]["damageMultiplier"].get<float>(),
                    json["counterHitStateWindow"]["stunMultiplier"].get<float>(),
                    json["counterHitStateWindow"]["hitStunMultiplier"].get<float>(),
                    json["counterHitStateWindow"]["launchMultiplier"].get<float>(),
                    json["counterHitStateWindow"]["pushbackMultiplier"].get<float>(),
                    json["counterHitStateWindow"]["counterHitOnlyCancellables"].get<int>(),
                    json["counterHitStateWindow"]["Multiplier"].get<float>(),
                    json["counterHitStateWindow"]["knockdownTypeOverride"].get<KnockdownType>(),
                };
            }
        }

        if (json.contains("overheadWindow"))
        {
            if (overheadWindow != NULL)
            {
                delete overheadWindow;
            }

            overheadWindowSize = json["overheadWindow"].size();

            overheadWindow = new OverheadWindow[overheadWindowSize];

            for (int i = 0; i < overheadWindowSize; i++)
            {
                overheadWindow[i] = {
                    json["overheadWindow"]["isOverhead"].get<bool>(),
                };
            }
        }

        if (json.contains("propulsionWindow"))
        {
            if (propulsionWindow != NULL)
            {
                delete propulsionWindow;
            }

            propulsionWindowSize = json["propulsionWindow"].size();

            propulsionWindow = new PropulsionWindow[propulsionWindowSize];

            for (int i = 0; i < propulsionWindowSize; i++)
            {
                propulsionWindow[i] = {
                    json["propulsionWindow"]["hSpeed"].get<int>(),
                    json["propulsionWindow"]["vSpeed"].get<int>(),
                };
            }
        }

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
