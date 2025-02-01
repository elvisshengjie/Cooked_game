#include "player.hpp"
#include "collison.hpp"
#include <assert.h>
#include <iostream>



player players1;
void player::playerdraw(AEGfxVertexList* mesh, AEGfxVertexList* mesh2) const {
	// Draw the player (blue rectangle)
	AEMtx33 rectplayer;
	AEMtx33Scale(&rectplayer, width, height);
	AEMtx33TransApply(&rectplayer, &rectplayer, x, y);
	AEGfxSetTransform(rectplayer.m);
	AEGfxSetColorToMultiply(0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxSetColorToAdd(0.0f, 0.0f, 1.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetBlendColor(1.0f, 0.0f, 1.0f, 1.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	// If holding an ingredient, draw it near the player.
	if (Hand != EMPTY) {
		// Offset for drawing the held ingredient (e.g., to the right).
		float offsetX = width + 2.0f;
		float offsetY = 0.0f;

		AEMtx33 ingredientTransform;
		// Scale the held ingredient rectangle (here, half the player's size)
		AEMtx33Scale(&ingredientTransform, width * 0.5f, height * 0.5f);
		// Position it relative to the player's position.
		AEMtx33TransApply(&ingredientTransform, &ingredientTransform, x + offsetX, y + offsetY);
		AEGfxSetTransform(ingredientTransform.m);

		// Set the color based on the ingredient type held.
		switch (Hand)
		{
		case CHICKEN:
			AEGfxSetColorToMultiply(1.0f, 0.9f, 0.8f, 1.0f);
			AEGfxSetColorToAdd(1.0f, 0.9f, 0.8f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(1.0f, 0.9f, 0.8f, 1.0f);
			break;
		case RICE:
			AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
			AEGfxSetColorToAdd(1.0f, 1.0f, 1.0f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		case EGG:
			AEGfxSetColorToMultiply(1.0f, 1.0f, 0.5f, 1.0f);
			AEGfxSetColorToAdd(1.0f, 1.0f, 0.5f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(1.0f, 1.0f, 0.5f, 1.0f);
			break;
		case CHEESE:
			AEGfxSetColorToMultiply(1.0f, 0.9f, 0.2f, 1.0f);
			AEGfxSetColorToAdd(1.0f, 0.9f, 0.2f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(1.0f, 0.9f, 0.2f, 1.0f);
			break;
		case POTATO:
			AEGfxSetColorToMultiply(0.6f, 0.4f, 0.2f, 1.0f);
			AEGfxSetColorToAdd(0.6f, 0.4f, 0.2f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(0.6f, 0.4f, 0.2f, 1.0f);
			break;
		case BEEF:
			AEGfxSetColorToMultiply(0.5f, 0.1f, 0.1f, 1.0f);
			AEGfxSetColorToAdd(0.5f, 0.1f, 0.1f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(0.5f, 0.1f, 0.1f, 1.0f);
			break;
		default:
			AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}

		// Draw the held ingredient rectangle.
		// IMPORTANT: Use a dedicated mesh that has white (neutral) vertex colors so that the multiplier tint is clearly visible.
		AEGfxMeshDraw(mesh2, AE_GFX_MDM_TRIANGLES);
	}
}


void player::playerMove(float speed)
{
	if (AEInputCheckCurr(AEVK_W))
	{
		this->y += speed;
	}
	if (AEInputCheckCurr(AEVK_S))
	{
		this->y -= speed;
	}
	if (AEInputCheckCurr(AEVK_D))
	{
		this->x += speed;
	}
	if (AEInputCheckCurr(AEVK_A))
	{
		this->x -= speed;
	}
}

bool player::playerCheckCollison(float x1, float y1, float width1, float height1)const
{
	return Colingredientbox1.collisonRect(x, y, width, height, x1, y1, width1, height1);
}
void player::playerCheckCollisonobject(float x1, float y1, float width1, float height1)
{
	Colingredientbox1.collisonobjectRect(x, y, width, height, x1, y1, width1, height1);
}
void player::playerThrow(){
	this->Hand = EMPTY;
}

void player::ClampToScreen() {
	// Player's half dimensions (since x/y are at the center)
	const float halfWidth = width / 2.0f;
	const float halfHeight = height / 2.0f;

	// Screen boundaries 
	const float screenLeft = -800.0f;   
	const float screenRight = 800.0f;   
	const float screenBottom = -450.0f;   
	const float screenTop = 450.0f;   

	// Clamp x-axis (left/right edges)
	const float playerLeft = x - halfWidth;  
	const float playerRight = x + halfWidth;  

	if (playerLeft < screenLeft) {
		x = screenLeft + halfWidth;  
	}
	else if (playerRight >= screenRight) {
		x = screenRight - halfWidth -1 ; 
	}

	// Clamp y-axis (top/bottom edges)
	const float playerBottom = y - halfHeight; 
	const float playerTop = y + halfHeight; 

	if (playerBottom < screenBottom) {
		y = screenBottom + halfHeight; 
	}
	else if (playerTop >= screenTop) {
		y = screenTop - halfHeight -1;   
	}
}

void player::playerPickUp(Ingredients& boxIngredient)
{
	if (AEInputCheckTriggered(AEVK_E))
	{
		// If the player is not already holding something
		if (Hand == EMPTY)
		{
			Hand = boxIngredient;                // Pick up the current ingredient from the box.
			boxIngredient = GetRandomIngredient(); // Immediately randomize the box's ingredient.
			std::cout << "Picked up: " << IngredientToString(Hand) << std::endl;
		}
		// If already holding an ingredient, drop it (clear the hand)
		else
		{
			std::cout << "Dropped: " << IngredientToString(Hand) << std::endl;
			Hand = EMPTY;
		}
	}
}

//float player::getX() const 
//{
//	return x;
//}
//
//float player::getY() const
//{
//	return y;
//}
//heekkei0ehjiehfio