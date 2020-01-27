#ifndef MODEL_H
#define MODEL_H

#include "deps/raylib/raylib.h"

class ModelController
{
public:
    int bodyWidth;
    int bodyHeight;
    float lightPos[3];
    Color color;
    Model model;
    int animCount;
    ModelAnimation *animations;
    int currentAnim;
    int currentAnimFrame;
    int currentAnimFrameCount;
    int *currentAnimFrameArray;
    bool animationWillLoop;

    ModelController();

    void init(const char *folder);
    /**
     * Sets new animation.
     *
     * Nullifies the existing animation frame array.
     */
    void setAnimation(int animationId);

    /**
     * Sets new animation.
     *
     * Nullifies the existing animation frame array.
     */
    // void setAnimation(const char* animationName);

    void setAnimationFrame(int frame);

    /**
     * Sets a list of frames from an existing animation.
     */
    void setAnimationFrameArray(int *frameArray, int frameCount);

    /**
     * Sets whether the animation will loop.
     */
    void setAnimationLoop(bool willLoop);

    void render(Vector3 translation, int rotation);

    void unload();
};

#endif
