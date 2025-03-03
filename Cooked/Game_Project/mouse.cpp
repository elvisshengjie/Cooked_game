#include "mouse.hpp"



mouse mouse1;

void mouse::mousedraw(AEGfxVertexList* mesh, AEGfxVertexList* mesh2) const {
	// Draw the player (blue rectangle)
	AEMtx33 rectplayer;
	AEMtx33Scale(&rectplayer, width, height);
	AEMtx33TransApply(&rectplayer, &rectplayer, x, y);
	AEGfxSetTransform(rectplayer.m);
	AEGfxSetColorToMultiply(0.0f, 0.0f, 0.5f, 0.5f);
	AEGfxSetColorToAdd(0.0f, 1.0f, 1.0f, 0.0f);
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);
	AEGfxSetBlendColor(1.0f, 0.0f, 1.0f, 1.0f);
	AEGfxSetTransparency(1.0f);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	
}

void mouse::mouseMove(float speed)
{
	dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
	std::vector<Rect> arr[5]; // Array of 5 vectors

	arr[0].push_back(10);
	arr[1].push_back(20);
	arr[2].push_back(30);
	if (isDashing) {
		this->x += DirectX * dashspeed * dt; //DirectX * dashspeed *dt
		this->y += DirectY * dashspeed * dt;

	}
	else if (!isDashing) {

		normalize_speed = speed * 0.707f;
		if (AEInputCheckCurr(AEVK_W) && AEInputCheckCurr(AEVK_D)) { //NE
			this->x += normalize_speed * dt;
			this->y += normalize_speed * dt;
		}
		else if (AEInputCheckCurr(AEVK_W) && AEInputCheckCurr(AEVK_A)) { //NW
			this->x -= normalize_speed * dt;
			this->y += normalize_speed * dt;
		}
		else if (AEInputCheckCurr(AEVK_S) && AEInputCheckCurr(AEVK_D)) { //SE
			this->x += normalize_speed * dt;
			this->y -= normalize_speed * dt;
		}
		else if (AEInputCheckCurr(AEVK_S) && AEInputCheckCurr(AEVK_A)) { //SW
			this->x -= normalize_speed * dt;
			this->y -= normalize_speed * dt;
		}
		else if (AEInputCheckCurr(AEVK_W))
		{
			this->y += speed * dt;
		}
		else if (AEInputCheckCurr(AEVK_S))
		{
			this->y -= speed * dt;
		}
		else if (AEInputCheckCurr(AEVK_D))
		{
			this->x += speed * dt;
		}
		else if (AEInputCheckCurr(AEVK_A))
		{
			this->x -= speed * dt;
		}
	}
}

bool mouse::mouseCheckCollison(float x1, float y1, float width1, float height1)const
{
	return Colingredientbox1.collisonRect(x, y, width, height, x1, y1, width1, height1);
}
void mouse::mouseCheckCollisonobject(float x1, float y1, float width1, float height1)
{
	Colingredientbox1.collisonobjectRect(x, y, width, height, x1, y1, width1, height1);
}
//void mouse::mouseThrow() {
//	this->Hand = EMPTY;
//}

void mouse::ClampToScreen() {
	// Player's half dimensions (since x/y are at the center)
	const float halfWidth = width / 2.0f;
	const float halfHeight = height / 2.0f;

	// Screen boundaries 
	const float screenLeft = -800.0f;
	const float screenRight = 800.0f;
	const float screenBottom = -450.0f;
	const float screenTop = 450.0f;

	// Clamp x-axis (left/right edges)
	const float mouseLeft = x - halfWidth;
	const float mouseRight = x + halfWidth;

	if (mouseLeft < screenLeft) {
		x = screenLeft + halfWidth;
	}
	else if (mouseRight >= screenRight) {
		x = screenRight - halfWidth - 1;
	}

	// Clamp y-axis (top/bottom edges)
	const float mouseBottom = y - halfHeight;
	const float mouseTop = y + halfHeight;

	if (mouseBottom < screenBottom) {
		y = screenBottom + halfHeight;
	}
	else if (mouseTop >= screenTop) {
		y = screenTop - halfHeight - 1;
	}
}

void mouse::mouseEating(Ingredients& boxIngredient)
{
	if (mouse::mouseCheckCollison)
	{
		
		boxIngredient = GetRandomIngredient(boxIngredient); // Randomize the box immediately.
		
	}
}




