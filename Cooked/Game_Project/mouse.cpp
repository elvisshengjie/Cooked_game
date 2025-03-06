#include "mouse.hpp"
#include <float.h>   // for FLT_MAX
#include <cmath>     // for sqrtf
#include "../Source/render.hpp"    // if you have a render header with ingredient1_box
// #include "../Source/Ingredients.hpp"
// #include "../Source/collison.hpp"

// This is your global mouse object
mouse mouse1(-400.0f, 100.0f);
mouse mouse2(0.0f, 150.0f);
mouse mouse3(400.0f, 100.0f);


// (Possibly) an external reference to an ingredient box declared elsewhere:
// extern Ingredients ingredient1_box; 
// If your project has "ingredient1_box" in another file, add an extern reference.

//-----------------------------------------------------------------
// mousedraw: Renders the mouse shape/texture
//-----------------------------------------------------------------
void mouse::mousedraw(AEGfxVertexList* mesh, AEGfxVertexList* mesh2) const
{
    AEMtx33 rectmouse;
    AEMtx33Scale(&rectmouse, width, height);
    AEMtx33TransApply(&rectmouse, &rectmouse, x, y);
    AEGfxSetTransform(rectmouse.m);

    // Example color settings
    AEGfxSetColorToMultiply(0.0f, 0.0f, 0.5f, 0.5f);
    AEGfxSetColorToAdd(0.0f, 1.0f, 1.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetBlendColor(1.0f, 0.0f, 1.0f, 1.0f);
    AEGfxSetTransparency(1.0f);

    // Draw the mesh for the mouse
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

//-----------------------------------------------------------------
// mouseMove: Moves the mouse toward the nearest of 3 ingredients
//-----------------------------------------------------------------
void mouse::mouseMove(float speed)
{
    dt = static_cast<float>(AEFrameRateControllerGetFrameTime());

    // 1. If we do NOT already have a target, find the nearest ingredient box
    if (!hasTarget)
    {
        float nearestDist = FLT_MAX;
        float chosenX = 0.0f;
        float chosenY = 0.0f;

        // We assume there are 3 ingredient boxes, each offset by 151.0f from the first
        // e.g. ingredient1_box at (ingredient1_box.x, ingredient1_box.y)
        // The next 2 are at x + 151, x + 302, etc.
        for (int i = 0; i < 3; ++i)
        {
            float ix = ingredient1_box.x + 151.0f * i;
            float iy = ingredient1_box.y;

            // Distance from the mouse to this ingredient
            float dx = ix - x;
            float dy = iy - y;
            float distSqr = dx * dx + dy * dy; // no sqrt needed for comparison

            // If it's closer than our currently known nearest, use it
            if (distSqr < nearestDist)
            {
                nearestDist = distSqr;
                chosenX = ix;
                chosenY = iy;
            }
        }

        // Mark that we've found our nearest target
        hasTarget = true;
        targetX = chosenX;
        targetY = chosenY;
    }

    // 2. If we DO have a target, move toward it
    if (hasTarget)
    {
        float dx = targetX - x;
        float dy = targetY - y;
        float distSqr = dx * dx + dy * dy;

        // Check if we arrived (or are "close enough") to the target
        float arriveRadius = 2.0f; // You can tweak this threshold
        if (distSqr < arriveRadius * arriveRadius)
        {
            // We consider we're at the ingredient, so drop the target
            hasTarget = false;
        }
        else
        {
            // Otherwise, normalize the direction and move
            float dist = sqrtf(distSqr);
            dx /= dist;
            dy /= dist;

            // Move the mouse
            x += dx * speed * dt;
            y += dy * speed * dt;
        }
    }

    // Keep the mouse within screen boundaries
    ClampToScreen();
}

//-----------------------------------------------------------------
// mouseCheckCollison: returns true if bounding-box collision
//-----------------------------------------------------------------
bool mouse::mouseCheckCollison(float x1, float y1, float width1, float height1) const
{
    return Colingredientbox1.collisonRect(x, y, width, height,
        x1, y1, width1, height1);
}

//-----------------------------------------------------------------
// mouseCheckCollisonobject: if you have different collisions
//-----------------------------------------------------------------
void mouse::mouseCheckCollisonobject(float x1, float y1, float width1, float height1)
{
    Colingredientbox1.collisonobjectRect(x, y, width, height,
        x1, y1, width1, height1);
}

//-----------------------------------------------------------------
// ClampToScreen: ensures the mouse stays within boundaries
//-----------------------------------------------------------------
void mouse::ClampToScreen()
{
    const float halfWidth = width * 0.5f;
    const float halfHeight = height * 0.5f;

    const float screenLeft = -800.0f;
    const float screenRight = 800.0f;
    const float screenBottom = -450.0f;
    const float screenTop = 450.0f;

    float mouseLeft = x - halfWidth;
    float mouseRight = x + halfWidth;

    if (mouseLeft < screenLeft)
        x = screenLeft + halfWidth;
    else if (mouseRight >= screenRight)
        x = screenRight - halfWidth - 1.0f;

    float mouseBottom = y - halfHeight;
    float mouseTop = y + halfHeight;

    if (mouseBottom < screenBottom)
        y = screenBottom + halfHeight;
    else if (mouseTop >= screenTop)
        y = screenTop - halfHeight - 1.0f;
}

