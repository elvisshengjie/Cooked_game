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
// extern Ingredients ingredient1_box; 
// (Often you keep `ingredient1_box` in another .cpp/.h, with "extern" in a header.)

class mouse
{
public:
    mouse(float startX, float startY)
        : x(startX), y(startY), chaseTimer{}
    {
    }
    // Draw function (renders the mouse on screen)
    void mousedraw(AEGfxVertexList* mesh) const;

    // Movement + pathfinding toward nearest ingredient
    void mouseMove(float speed);

    // Collision checks
    bool mouseCheckCollison(float x1, float y1, float width1, float height1) const;
    void mouseCheckCollisonobject(float x1, float y1, float width1, float height1);

    // Keep the mouse position within screen boundaries
    void ClampToScreen();

    // The mouse "eats" or steals the ingredient
    /*void mouseEating(Ingredients& boxIngredient);*/

    // OPTIONAL: Expose position if you need from outside
    // float getX() const { return x; }
    // float getY() const { return y; }
    // void  setPosition(float newX, float newY) { x = newX; y = newY; }

    void chaseAway(float duration);

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
    float targetX = 0.0f;  // X coordinate of our current target
    float targetY = 0.0f;  // Y coordinate of our current target


    //chasing
    bool isChased = false;
    Timer chaseTimer;
    float randomDirX = 0.0f;
    float randomDirY = 0.0f;

    // The mouse "Hand": what ingredient is it holding
    Ingredients Hand = EMPTY;
};

// We declare an extern mouse object if it¡¯s used globally
extern mouse mouse1;
extern mouse mouse2;
extern mouse mouse3;
