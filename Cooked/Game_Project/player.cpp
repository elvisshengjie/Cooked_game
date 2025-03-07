#include "player.hpp"


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
	if (dx == 0 && dy == 0) {
		cannotdash == true;
	}
	if (AEInputCheckCurr(AEVK_W)) {
		dy += 1;
		cannotdash == false;
	}if (AEInputCheckCurr(AEVK_S)) {
		dy -= 1;
		cannotdash == false;
	}if (AEInputCheckCurr(AEVK_A)) {
		dx -= 1;
		cannotdash == false;
	}
	if (AEInputCheckCurr(AEVK_D)) {
		dx += 1;
		cannotdash == false;
	}
	

	if (dx != 0.0f || dy != 0.0f) {
		angle = atan2(dy, dx);

	}
	dt = static_cast<float>(AEFrameRateControllerGetFrameTime());

	
	if (isDashing && !cannotdash)  {
		
		
		mangnituded = sqrt(dx * dx + dy * dy);
		normdx = dx / mangnituded;
		normdy = dy / mangnituded;
		
		

		this->x += normdx * dashspeed * dt; //DirectX * dashspeed *dt
		this->y += normdy * dashspeed * dt;
		dx = 0;
		dy = 0;

	}
	else if(!isDashing){
		
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
		if (Hand != EMPTY) {
			if (playerCheckCollison(stove.getX(), stove.getY(), stove.getW(), stove.getH()))
			{
				std::cout << IngredientToString(Hand) << "\n";
				if (stove.putIngredient(IngredientToString(Hand))) {
					std::cout << "Dropped ingredient: " << IngredientToString(Hand) << " into the stove!" << std::endl;
					Hand = EMPTY;
				}
				return;				
				 // Player no longer holds the ingredient
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

void player::playerDash() {

	

	if (dashCounter == 1) {
		if (AEInputCheckTriggered(AEVK_SPACE)) {
			
				// Prevent dashing if the player is not moving
			if (dx == 0 && dy == 0) {
				return;  // Stop execution if no movement direction
			}
			//rawX, rawY;
			//AEInputGetCursorPosition(&rawX, &rawY);
			//// Convert from screen-space (assuming 1600x900) to centered coordinates:
			//mouseX = (rawX - 800);// 800.0f;
			//mouseY = (450 - rawY); // 450.0f;

			//DirectX = mouseX - x;
			//DirectY = mouseY - y;

			//Magnitude = (DirectX * DirectX + DirectY * DirectY);
			//Magnitude = sqrt(Magnitude);

			//if (Magnitude > 0) {
			//	DirectX /= Magnitude;
			//	DirectY /= Magnitude;

			//}

			isDashing = true;
			cooldown.start(dashDuration);

			}

		}
	if (isDashing) {
		float remainTimedash2 = cooldown.getRemainingTime();
		std::cout << "Remaining time: " << remainTimedash2 << std::endl;
		if (AEIsF32Zero(remainTimedash2)) {
			dashCounter = 0;
			isDashing = false;
			cooldown2.start(dashCooldown);
		}

	}

	 
	if (dashCounter == 0 && !isDashing)
	{
		float remainTimedash = cooldown2.getRemainingTime();
		if (remainTimedash <= 0) {
			dashCounter = 1;
		}
	}



	
}

void player::playerUpdate(Stove& stove,RecipeSystem& recipeSystem, QTE &QTE_Gauge) {
	if (playerCheckCollison(stove.getX(), stove.getY(), stove.getW(), stove.getH()) &&
		stove.canCook(*this))
	{
		if (AEInputCheckTriggered(AEVK_Q) && !QTE_Gauge.isActive) {  // Press Q to Cook
			QTE_Gauge.start();
		}
	}
	if (QTE_Gauge.isActive) {
		QTE_Gauge.update(AEFrameRateControllerGetFrameTime());
		if (QTE_Gauge.isCompleted) {
			if (QTE_Gauge.isSuccess) {
				std::cout << "QTE Successful! Cooking started." << std::endl;
				stove.startCooking(recipeSystem.getActiveRecipes());
			}
			else {
				std::cout << "QTE Failed! Ingredients thrown away." << std::endl;
				stove.clearWok(); // Clear the wok if QTE fails
			}
			QTE_Gauge.reset(); // Reset QTE state
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