#include "mouse.hpp"
#include <float.h>   // for FLT_MAX
#include <cmath>     // for sqrtf
#include "../Source/render.hpp"    // if you have a render header with ingredientBoxRect
// #include "../Source/Ingredients.hpp"
// #include "../Source/collison.hpp"

// This is your global mouse object
mouse mouse1(-2500.0f, 100.0f);
mouse mouse2(2200.0f, 500.0f);
mouse mouse3(3300.0f, 0.0f);

//-----------------------------------------------------------------
// mousedraw: Renders the mouse shape/texture
//-----------------------------------------------------------------
void mouse::mousedraw(AEGfxVertexList* mesh, std::vector<AEGfxTexture*>up, std::vector<AEGfxTexture*>down, std::vector<AEGfxTexture*>left, std::vector<AEGfxTexture*>right)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

    AEGfxTexture* selectedTexture = nullptr;

    AEMtx33 rectmouse;
    AEMtx33Scale(&rectmouse, width, height);
    AEMtx33TransApply(&rectmouse, &rectmouse, x, y);
    AEGfxSetTransform(rectmouse.m);

    if (isMoving) {
        switch(spriteDirection)
        {
            case 1:
                selectedTexture = up[currentFrame];
                break;
            case 2:
                selectedTexture = down[currentFrame];
                break;
            case 3:
                selectedTexture = left[currentFrame];
                break;
            case 4:
                selectedTexture = right[currentFrame];
                break;
        }
    }
    else {
        selectedTexture = up[currentFrame];
    }

    //// Example color settings
    //AEGfxSetColorToMultiply(0.0f, 0.0f, 0.5f, 0.5f);
    //AEGfxSetColorToAdd(0.0f, 1.0f, 1.0f, 0.0f);
    //AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    //AEGfxSetBlendColor(1.0f, 0.0f, 1.0f, 1.0f);
    //AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(selectedTexture, 0, 0);

    // Draw the mesh for the mouse
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

//-----------------------------------------------------------------
// mouseMove: Moves the mouse toward the nearest of 3 ingredients
//-----------------------------------------------------------------
void mouse::mouseMove(float speed)
{
    dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
    isMoving = false;

    if (isChased)
    {
        if (chaseTimer.completed())
        {
            // Chase time over�end chase-away state.
            isChased = false;
        }
        else
        {
            // Continue moving in the random direction.
            x += randomDirX * speed * dt;
            y += randomDirY * speed * dt;
            isMoving = true;
            return; // Skip normal behavior.
        }
    }

    // 1. If we do NOT already have a target, find the nearest ingredient box
    if (!hasTarget)
    {
        float nearestDist = FLT_MAX;
        float chosenX = 0.0f;
        float chosenY = 0.0f;

        // We assume there are 3 ingredient boxes, each offset by 151.0f from the first
        // e.g. ingredientBoxRect at (ingredientBoxRect.x, ingredientBoxRect.y)
        // The next 2 are at x + 151, x + 302, etc.
        for (int i = 0; i < 3; ++i)
        {
            float ix = ingredientBoxRect.x + 151.0f * i;
            float iy = ingredientBoxRect.y;

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
            isMoving = true;

            if (fabs(dx) > fabs(dy)) {
                spriteDirection = (dx > 0) ? 4 : 3; // Right or Left
            }
            else {
                spriteDirection = (dy > 0) ? 1 : 2; // Up or Down
            }
        }
    }

    // Keep the mouse within screen boundaries
    /*ClampToScreen();*/

    if (isMoving) {
        frameTimer += dt;
        if (frameTimer >= frameDuration) {
            currentFrame = (currentFrame + 1) % 4; // Cycle through loaded textures
            frameTimer = 0.0f;
        }
    }
    else {
        currentFrame = 0; // Reset to idle frame
    }
}
void mouse::chaseAway(float duration)
{
    isChased = true;
    chaseTimer.start(duration);  // Start the timer with the desired duration.

    // Generate a random angle between 0 and 2*PI.
    float angle = static_cast<float>(rand()) / RAND_MAX * 2 * 3.14159f;
    randomDirX = cos(angle);
    randomDirY = sin(angle);
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

