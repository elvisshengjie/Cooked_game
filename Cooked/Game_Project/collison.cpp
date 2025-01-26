#include "collison.hpp"


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
