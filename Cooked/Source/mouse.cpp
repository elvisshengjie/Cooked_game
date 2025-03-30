/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file mouse.cpp
@author1 Elvis lim sheng jie(elvisshengjie.lim)
-void mouseMove (only the part where the condition isChased)
-void chaseAway
-void handleDeviceInteraction
@author2 Justin
@course csd1451s25 Software Engineering Project 2
@section a
*//*______________________________________________________________________*/
#include "mouse.hpp"
#include <float.h>   // for FLT_MAX
#include <cmath>     // for sqrtf

#include "render.hpp"  // Adjust include paths if needed
// #include "../Source/Ingredients.hpp"
// #include "../Source/collison.hpp"

// Global mouse objects
mouse mouse1(-2500.0f, 100.0f);
mouse mouse2(2200.0f, 500.0f);
mouse mouse3(3300.0f, 0.0f);

//-----------------------------------------------------------------
// init: Re-initializes the mouse’s position and internal states
//-----------------------------------------------------------------
void mouse::init(float startX, float startY)
{
    x = startX;
    y = startY;

    hasTarget = false;
    isChased = false;
    

    randomDirX = 0.0f;
    randomDirY = 0.0f;

    isMoving = false;
    currentFrame = 0;
    frameTimer = 0.0f;

    // The mouse is not holding anything
    Hand = EMPTY;
}

//-----------------------------------------------------------------
// mousedraw: Renders the mouse shape/texture
//-----------------------------------------------------------------
void mouse::mousedraw(AEGfxVertexList* mesh,
    std::vector<AEGfxTexture*> up,
    std::vector<AEGfxTexture*> down,
    std::vector<AEGfxTexture*> left,
    std::vector<AEGfxTexture*> right)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

    AEGfxTexture* selectedTexture = nullptr;

    AEMtx33 rectmouse;
    AEMtx33Scale(&rectmouse, width, height);
    AEMtx33TransApply(&rectmouse, &rectmouse, x, y);
    AEGfxSetTransform(rectmouse.m);

    // Choose the appropriate texture frame
    if (isMoving)
    {
        switch (spriteDirection)
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
    else
    {
        // Idle: pick the default frame from one direction 
        selectedTexture = up[currentFrame];
    }

    // Apply the texture
    AEGfxTextureSet(selectedTexture, 0, 0);
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
            // Chase time over; end chase-away state
            isChased = false;
        }
        else
        {
            // Continue moving in the random direction
            x += randomDirX * speed * dt;
            y += randomDirY * speed * dt;
            isMoving = true;
            return; // Skip normal behavior
        }
    }

    // 1. If we do NOT already have a target, find the nearest ingredient box
    if (!hasTarget)
    {
        float nearestDist = FLT_MAX;
        float chosenX = 0.0f;
        float chosenY = 0.0f;

        // We assume there are 3 ingredient boxes spaced out horizontally
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

        // Check if we're close enough to consider "arrived"
        float arriveRadius = 2.0f;
        if (distSqr < arriveRadius * arriveRadius)
        {
            // We consider we're at the ingredient
            hasTarget = false;
        }
        else
        {
            // Otherwise, normalize and move
            float dist = sqrtf(distSqr);
            dx /= dist;
            dy /= dist;

            x += dx * speed * dt;
            y += dy * speed * dt;
            isMoving = true;

            // Update direction for sprite
            if (fabs(dx) > fabs(dy))
            {
                spriteDirection = (dx > 0) ? 4 : 3; // Right or Left
            }
            else
            {
                spriteDirection = (dy > 0) ? 1 : 2; // Up or Down
            }
        }
    }

    // Keep the mouse within screen boundaries (optional)
    // ClampToScreen();

    // Handle animation frames if moving
    if (isMoving)
    {
        frameTimer += dt;
        if (frameTimer >= frameDuration)
        {
            currentFrame = (currentFrame + 1) % 4; // Cycle 0..3
            frameTimer = 0.0f;
        }
    }
    else
    {
        currentFrame = 0; // Idle frame
    }
}

//-----------------------------------------------------------------
// chaseAway: Sets the mouse to run away randomly for 'duration' seconds
//-----------------------------------------------------------------
void mouse::chaseAway(float duration)
{
    isChased = true;
    chaseTimer.start(duration);  // Start the timer

    // Generate a random angle between 0 and 2*PI
    float angle = static_cast<float>(rand()) / RAND_MAX * 2.0f * 3.14159f;
    randomDirX = cosf(angle);
    randomDirY = sinf(angle);
}

void mouse::handleDeviceInteraction(const Rect& deviceRect, Timer& deviceCooldownTimer, player& player)
{
    // Check if the player collides with the device's collision area.
    if (player.playerCheckCollison(deviceRect.x, deviceRect.y, deviceRect.width, deviceRect.height)) {
        if (!deviceCooldownTimer.completed()) {
            float remaining = static_cast<float>(deviceCooldownTimer.getRemainingTime());
            std::string cooldownStr = "Device cooldown: " + std::to_string(static_cast<int>(remaining)) + " s";
            AEGfxPrint(FontID, cooldownStr.c_str(), 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
        }
        else {
            AEGfxPrint(FontID, "Press E to activate device", 0.0f, 0.0f, 1.0f,
                0.0f, 0.0f, 0.0f, 1.0f);
            if (AEInputCheckTriggered(AEVK_E)) {
                // Generate a random chase duration between 20 and 30 seconds.
                float chaseDuration = 20.0f + static_cast<float>(rand()) / RAND_MAX * 10.0f;
                // Trigger the chaseAway for all mouse objects.
                mouse1.chaseAway(chaseDuration);
                mouse2.chaseAway(chaseDuration);
                mouse3.chaseAway(chaseDuration);
                deviceCooldownTimer.start(25.0);
            }
        }
    }
}

//-----------------------------------------------------------------
// mouseCheckCollison: returns true if bounding-box collision
//-----------------------------------------------------------------
bool mouse::mouseCheckCollison(float x1, float y1, float width1, float height1) const
{
    // This uses some collision-detect helper. Adjust as needed.
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
// ClampToScreen: ensures the mouse stays within certain boundaries
//-----------------------------------------------------------------
void mouse::ClampToScreen()
{
    const float halfWidth = width * 0.5f;
    const float halfHeight = height * 0.5f;

    // Example screen boundaries
    const float screenLeft = -800.0f;
    const float screenRight = 800.0f;
    const float screenBottom = -450.0f;
    const float screenTop = 450.0f;

    float mouseLeft = x - halfWidth;
    float mouseRight = x + halfWidth;
    float mouseBottom = y - halfHeight;
    float mouseTop = y + halfHeight;

    if (mouseLeft < screenLeft)
        x = screenLeft + halfWidth;
    else if (mouseRight >= screenRight)
        x = screenRight - halfWidth - 1.0f;

    if (mouseBottom < screenBottom)
        y = screenBottom + halfHeight;
    else if (mouseTop >= screenTop)
        y = screenTop - halfHeight - 1.0f;
}
