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
        : x(startX), y(startY)
    {
    }
    // Draw function (renders the mouse on screen)
    void mousedraw(AEGfxVertexList* mesh, AEGfxVertexList* mesh2) const;

    // Movement + pathfinding toward nearest ingredient
    void mouseMove(float speed);

    // Collision checks
    bool mouseCheckCollison(float x1, float y1, float width1, float height1) const;
    void mouseCheckCollisonobject(float x1, float y1, float width1, float height1);

    // Keep the mouse position within screen boundaries
    void ClampToScreen();

    // The mouse "eats" or steals the ingredient
    void mouseEating(Ingredients& boxIngredient);

    // OPTIONAL: Expose position if you need from outside
    // float getX() const { return x; }
    // float getY() const { return y; }
    // void  setPosition(float newX, float newY) { x = newX; y = newY; }

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

    // Example "dash" variables (if you need them)
    float dashspeed{ 700.0f };
    float dashCooldown{ 0.5f };
    float dashDuration{ 0.2f };
    int   rawX{};
    int   rawY{};
    float mouseX{};
    float mouseY{};
    bool  isDashing{ false };
    float DirectX{};
    float DirectY{};
    float DirectionX{};
    float DirectionY{};
    float Magnitude{};
    int   dashCounter{ 1 };
    Timer cooldown;
    Timer cooldown2;

    // The mouse "Hand": what ingredient is it holding
    Ingredients Hand = EMPTY;
};

// We declare an extern mouse object if it¡¯s used globally
extern mouse mouse1;
extern mouse mouse2;
extern mouse mouse3;
