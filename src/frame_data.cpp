#include "frame_data.hpp"

void FrameData::frameDataFromJSON(JSON json)
{
    // std::cout << "BEFORE: knockdownTypeWindow" << std::endl;
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
                json["knockdownTypeWindow"][i]["firstFrameOfWindow"].get<int>(),
                json["knockdownTypeWindow"][i]["lastFrameOfWindow"].get<int>(),
                json["knockdownTypeWindow"][i]["knockdownType"].get<KnockdownType>(),
            };
        }
    }

    // std::cout << "BEFORE: knockupKnockbackWindow" << std::endl;
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
                json["knockupKnockbackWindow"][i]["firstFrameOfWindow"].get<int>(),
                json["knockupKnockbackWindow"][i]["lastFrameOfWindow"].get<int>(),
                json["knockupKnockbackWindow"][i]["knockupValue"].get<int>(),
                json["knockupKnockbackWindow"][i]["knockbackValue"].get<int>(),
            };
        }
    }

    // std::cout << "BEFORE: launchWindow" << std::endl;
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
                json["launchWindow"][i]["firstFrameOfWindow"].get<int>(),
                json["launchWindow"][i]["lastFrameOfWindow"].get<int>(),
                json["launchWindow"][i]["launchValue"].get<int>(),
            };
        }
    }

    // std::cout << "BEFORE: pushbackWindow" << std::endl;
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
                json["pushbackWindow"][i]["firstFrameOfWindow"].get<int>(),
                json["pushbackWindow"][i]["lastFrameOfWindow"].get<int>(),
                json["pushbackWindow"][i]["pushbackOnHit"].get<int>(),
                json["pushbackWindow"][i]["pushbackOnBlock"].get<int>(),
            };
        }
    }

    // std::cout << "BEFORE: damageWindow" << std::endl;
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
                json["damageWindow"][i]["firstFrameOfWindow"].get<int>(),
                json["damageWindow"][i]["lastFrameOfWindow"].get<int>(),
                json["damageWindow"][i]["damageOnHit"].get<int>(),
                json["damageWindow"][i]["damageOnBlock"].get<int>(),
            };
        }
    }

    // std::cout << "BEFORE: stunWindow" << std::endl;
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
                json["stunWindow"][i]["firstFrameOfWindow"].get<int>(),
                json["stunWindow"][i]["lastFrameOfWindow"].get<int>(),
                json["stunWindow"][i]["stunValue"].get<int>(),
            };
        }
    }

    // std::cout << "BEFORE: cancellableWindow" << std::endl;
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
            cancellableWindow[i].firstFrameOfWindow = json["cancellableWindow"][i]["firstFrameOfWindow"].get<int>();
            cancellableWindow[i].cancelMovesSize = json["cancellableWindow"][i]["cancelMoves"].size();
            cancellableWindow[i].cancelMoves = new int[cancellableWindow[i].cancelMovesSize];
            for (int i = 0; i < cancellableWindow[i].cancelMovesSize; i++)
            {
                cancellableWindow[i].cancelMoves[i] = json["cancellableWindow"][i]["cancelMoves"][i].get<int>();
            }
        }
    }

    // std::cout << "BEFORE: invincibilityWindow" << std::endl;
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
                json["invincibilityWindow"][i]["firstFrameOfWindow"].get<int>(),
                json["invincibilityWindow"][i]["lastFrameOfWindow"].get<int>(),
                json["invincibilityWindow"][i]["hitInvincibility"].get<bool>(),
                json["invincibilityWindow"][i]["grabInvincibility"].get<bool>(),
                json["invincibilityWindow"][i]["exHitInvincibility"].get<bool>(),
                json["invincibilityWindow"][i]["exGrabInvincibility"].get<bool>(),
                json["invincibilityWindow"][i]["superHitInvincibility"].get<bool>(),
                json["invincibilityWindow"][i]["superGrabInvincibility"].get<bool>(),
            };
        }
    }

    // std::cout << "BEFORE: counterHitStateWindow" << std::endl;
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
                json["counterHitStateWindow"][i]["firstFrameOfWindow"].get<int>(),
                json["counterHitStateWindow"][i]["lastFrameOfWindow"].get<int>(),
                json["counterHitStateWindow"][i]["isCounterHitable"].get<bool>(),
                json["counterHitStateWindow"][i]["damageMultiplier"].get<float>(),
                json["counterHitStateWindow"][i]["stunMultiplier"].get<float>(),
                json["counterHitStateWindow"][i]["hitStunMultiplier"].get<float>(),
                json["counterHitStateWindow"][i]["launchMultiplier"].get<float>(),
                json["counterHitStateWindow"][i]["pushbackMultiplier"].get<float>(),
                json["counterHitStateWindow"][i]["counterHitOnlyCancellables"].get<int>(),
                json["counterHitStateWindow"][i]["multiplier"].get<float>(),
                json["counterHitStateWindow"][i]["knockdownTypeOverride"].get<KnockdownType>(),
            };
        }
    }

    // std::cout << "BEFORE: overheadWindow" << std::endl;
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
                json["overheadWindow"][i]["firstFrameOfWindow"].get<int>(),
                json["overheadWindow"][i]["lastFrameOfWindow"].get<int>(),
                json["overheadWindow"][i]["isOverhead"].get<bool>(),
            };
        }
    }

    // std::cout << "BEFORE: propulsionWindow" << std::endl;
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
                json["propulsionWindow"][i]["firstFrameOfWindow"].get<int>(),
                json["propulsionWindow"][i]["lastFrameOfWindow"].get<int>(),
                json["propulsionWindow"][i]["hSpeed"].get<int>(),
                json["propulsionWindow"][i]["vSpeed"].get<int>(),
            };
        }
    }

    // std::cout << "BEFORE: frameBoxData" << std::endl;
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
                json["frameBoxData"][i]["xOffset"].get<int>(),
                json["frameBoxData"][i]["yOffset"].get<int>(),
                json["frameBoxData"][i]["width"].get<int>(),
                json["frameBoxData"][i]["height"].get<int>(),
                json["frameBoxData"][i]["boxType"].get<BoxType>()};
        }
    }
}
