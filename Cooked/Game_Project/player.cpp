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

	if (Hand != EMPTY) {
		float offsetX = width + 2.0f;
		float offsetY = 0.0f;

		AEMtx33 ingredientTransform;
		AEMtx33Scale(&ingredientTransform, width * 0.5f, height * 0.5f);
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
		// IMPORTANT: Use a dedicated mesh (mesh2) that is created with white (neutral) vertex colors.
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
		// If the player is not already holding something, pick up the box ingredient.
		if (Hand != EMPTY)
		{
			std::cout << "You are already holding, drop into Dustbin / Stove";
			return;
		}
			Hand = boxIngredient;                // Player picks up the current ingredient.
			boxIngredient = GetRandomIngredient(boxIngredient); // Randomize the box immediately.
			std::cout << "Picked up: " << IngredientToString(Hand) << std::endl;
		// If already holding an ingredient, drop it (clear the held ingredient).
	}
}

void player::playerDrop(Stove& stove) {
	//std::cout << "Attempted";
	if (AEInputCheckTriggered(AEVK_E)) {
		std::cout << "Attempted";
		if (Hand != EMPTY) {
			if (playerCheckCollison(stove.getX(), stove.getY(), stove.getW(), stove.getH()))
			{
				stove.putIngredient(IngredientToString(Hand));  // Convert enum to string
				std::cout << "Dropped ingredient: " << IngredientToString(Hand) << " into the stove!" << std::endl;
				Hand = EMPTY;  // Player no longer holds the ingredient
			}
			else if (playerCheckCollison(-750.0f, -300.0f,150.0f, 200.0f))
			{
				std::cout << "Threw away ingredient: " << IngredientToString(Hand) << std::endl;
				Hand = EMPTY;  // Ingredient is removed
			}
			else {
				return;
			}
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