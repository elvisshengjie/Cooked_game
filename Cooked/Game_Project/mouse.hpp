#pragma once

#include <crtdbg.h>   // For memory leak checks (Windows)
#include <math.h>
#include <AEEngine.h> // Replace with your actual engine/graphics headers
#include "Ingredients.hpp"
#include "collison.hpp"
#include <assert.h>
#include <iostream>

class Rect;

// Forward declarations if needed:
// extern Ingredients ingredientBoxRect; 
// (Often you keep `ingredientBoxRect` in another .cpp/.h, with "extern" in a header.)

class mouse
{
public:
    mouse(float startX, float startY)
        : x(startX), y(startY), chaseTimer{}
    {
    }

    // Draw function (renders the mouse on screen)
    void mousedraw(AEGfxVertexList* mesh, std::vector<AEGfxTexture*> up,
        std::vector<AEGfxTexture*> down, std::vector<AEGfxTexture*> left,
        std::vector<AEGfxTexture*> right);

    // Movement + pathfinding toward nearest ingredient
    void mouseMove(float speed);

    // Collision checks
    bool mouseCheckCollison(float x1, float y1, float width1, float height1) const;
    void mouseCheckCollisonobject(float x1, float y1, float width1, float height1);

    // Keep the mouse position within screen boundaries
    void ClampToScreen();

    // The mouse "eats" or steals the ingredient
    /*void mouseEating(Ingredients& boxIngredient);*/

    // Call this if you want to reset the mouse¡¯s state (like a re-init)
    void init(float startX, float startY);

    // The mouse is chased away for a certain duration
    void chaseAway(float duration);

    // Public flags you may need for anim logic
    bool isMoving = false;
    int  currentFrame = 0;
    float frameTimer = 0.0f;
    const float frameDuration = 0.1f;
    int spriteDirection = 2; // 1-up , 2- down , 3-left , 4-right

private:
    // Position & size
    float x{};
    float y{};
    float width{ 50.0f };
    float height{ 50.0f };

    // Internal movement timing
    float dt{};

    // For pathfinding / nearest-target logic
    bool  hasTarget = false;  // Do we have a current ingredient target?
    float targetX = 0.0f;     // X coordinate of our current target
    float targetY = 0.0f;     // Y coordinate of our current target

    // Chasing (being scared away)
    bool  isChased = false;
    Timer chaseTimer;
    float randomDirX = 0.0f;
    float randomDirY = 0.0f;

    // The mouse "Hand": what ingredient is it holding
    Ingredients Hand = EMPTY;
};

// If you want global mouse objects accessible everywhere:
extern mouse mouse1;
extern mouse mouse2;
extern mouse mouse3;

