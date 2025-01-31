#include "player.hpp"
#include "collison.hpp"
#include <assert.h>
#include <iostream>



player players1;
void player::playerdraw(AEGfxVertexList* mesh)
{
    AEMtx33 rectplayer;
	AEMtx33Scale(&rectplayer, width, height);
	AEMtx33TransApply(&rectplayer, &rectplayer, x,y);
	AEGfxSetTransform(rectplayer.m);
	AEGfxSetColorToMultiply(0.0f, 0.0f, 1.0f, 1.0f);
	AEGfxSetColorToAdd(0.0f, 0.0f, 1.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetBlendColor(1.0f, 0.0f, 1.0f, 1.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
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

bool player::playerCheckCollison(float x1, float y1, float width1, float height1)
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

void player::playerPickUp(bool& isHolding, Ingredients& heldItem, const Ingredients& nearbyItem) {
	if (AEInputCheckTriggered(AEVK_E)) {
		if (!isHolding && nearbyItem != EMPTY) {
			isHolding = true;
			heldItem = nearbyItem;
			std::cout << "Picked up item: " << heldItem << std::endl;
		}
		else if (isHolding) {
			isHolding = false;
			std::cout << "Dropped item: " << heldItem << std::endl;
			heldItem = EMPTY;
		}
	}
}

