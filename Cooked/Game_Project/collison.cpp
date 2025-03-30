/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file collison.cpp
@author1 Elvis lim sheng jie(elvisshengjie.lim)
- bool collisonRect
@author2
@course csd1451s25 Software Engineering Project 2
@section a
*//*______________________________________________________________________*/

#include "collison.hpp"
#include <iostream>


Collison Colingredientbox1;

bool Collison::collisonRect(float x0, float y0, float width0, float height0, float x1, float y1, float width1, float height1)
{
	// Calculate the edges of the first rectangle
	float playerLeft = x0 - (0.5f * width0);
	float playerRight = x0 + (0.5f * width0);
	float playerBottom = y0 - (0.5f * height0);
	float playerTop = y0 + (0.5f * height0);

	// Calculate the edges of the second rectangle
	float objectLeft = x1 - (0.5f * width1);
	float objectRight = x1 + (0.5f * width1);
	float objectBottom = y1 - (0.5f * height1);
	float objectTop = y1 + (0.5f * height1);

	// Check for collision
	return (playerRight >= objectLeft &&
		playerLeft <= objectRight &&
		playerTop >= objectBottom &&
		playerBottom <= objectTop);
}

void Collison::collisonobjectRect(
    float& px, float& py, float pw, float ph,
    float ox, float oy, float ow, float oh)
{
    // Half-widths, half-heights
    float halfPW = pw * 0.5f;
    float halfPH = ph * 0.5f;
    float halfOW = ow * 0.5f;
    float halfOH = oh * 0.5f;

    bool overlapX = (px + halfPW >= ox - halfOW) && (px - halfPW <= ox + halfOW);
    bool overlapY = (py + halfPH >= oy - halfOH) && (py - halfPH <= oy + halfOH);

    if (overlapX && overlapY) {
        // They overlap; figure out how far to push the player out.

        // Overlap amounts:
        float overlapLeft = (px + halfPW) - (ox - halfOW);
        float overlapRight = (ox + halfOW) - (px - halfPW);
        float overlapTop = (py + halfPH) - (oy - halfOH);
        float overlapBottom = (oy + halfOH) - (py - halfPH);

        // Find the smallest overlap
        float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

        // Adjust position based on which side is smallest
        if (minOverlap == overlapLeft) {
            px -= overlapLeft;    // Move player left
        }
        else if (minOverlap == overlapRight) {
            px += overlapRight;   // Move player right
        }
        else if (minOverlap == overlapTop) {
            py -= overlapTop;     // Move player up
        }
        else {
            py += overlapBottom;  // Move player down
        }
    }
}

