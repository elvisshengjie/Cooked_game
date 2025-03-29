#include "player.hpp"

void RenderAnimatedSprite(AEGfxVertexList* mesh, AEGfxTexture* texture, int frameIndex, int totalFrames) {
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	// Define frame size (each texture has multiple frames in 1 row)
	const float frameWidth = 1.0f / totalFrames;

	// Calculate UV coordinates
	float uMin = frameIndex * frameWidth;
	float uMax = uMin + frameWidth;
	float vMin = 0.0f;
	float vMax = 1.0f;

	// Apply UV mapping
	AEGfxTextureSet(texture, uMin, vMin);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}
player players1;


void player::playerdraw(AEGfxVertexList* mesh, AEGfxVertexList* mesh2, std::vector<AEGfxTexture*> idle, std::vector<AEGfxTexture*> up, std::vector<AEGfxTexture*> down, std::vector<AEGfxTexture*> left, std::vector<AEGfxTexture*> right,
	AEGfxTexture* chickenTex , AEGfxTexture* beefTex , AEGfxTexture* riceTex , AEGfxTexture* eggTex , AEGfxTexture* cheeseTex , AEGfxTexture* potatoTex) {
	// Draw the player (blue rectangle)
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

	AEGfxTexture* selectedTexture = idle[currentFrame];

	switch (spriteDirection)
	{
	case 0:
		selectedTexture = idle[currentFrame];
		break;
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

	AEMtx33 rectplayer;
	AEMtx33Scale(&rectplayer, width, height);
	AEMtx33TransApply(&rectplayer, &rectplayer, x, y);
	AEGfxSetTransform(rectplayer.m);

	AEGfxTextureSet(selectedTexture, 0, 0);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	//RenderAnimatedSprite(mesh, selectedTexture, currentFrame, 2);
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	
	if (Hand != EMPTY) {
		float offsetX = 0.0f;
		float offsetY = height +0.2f;

		AEMtx33 ingredientTransform;
		AEMtx33Scale(&ingredientTransform, width * 1.0f, height * 1.0f);
		AEMtx33TransApply(&ingredientTransform, &ingredientTransform, x + offsetX, y + offsetY);
		AEGfxSetTransform(ingredientTransform.m);

		// Set the color based on the ingredient type held.
		switch (Hand)
		{
		case CHICKEN:
			/*AEGfxSetColorToMultiply(1.0f, 0.9f, 0.8f, 1.0f);
			AEGfxSetColorToAdd(1.0f, 0.9f, 0.8f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(1.0f, 0.9f, 0.8f, 1.0f);*/
			AEGfxTextureSet(chickenTex, 0, 0);
			break;
		case RICE:
			/*AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
			AEGfxSetColorToAdd(1.0f, 1.0f, 1.0f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(1.0f, 1.0f, 1.0f, 1.0f);*/
			AEGfxTextureSet(riceTex, 0, 0);
			break;
		case EGG:
			/*AEGfxSetColorToMultiply(1.0f, 1.0f, 0.5f, 1.0f);
			AEGfxSetColorToAdd(1.0f, 1.0f, 0.5f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(1.0f, 1.0f, 0.5f, 1.0f);*/
			AEGfxTextureSet(eggTex, 0, 0);
			break;
		case CHEESE:
			/*AEGfxSetColorToMultiply(1.0f, 0.9f, 0.2f, 1.0f);
			AEGfxSetColorToAdd(1.0f, 0.9f, 0.2f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(1.0f, 0.9f, 0.2f, 1.0f);*/
			AEGfxTextureSet(cheeseTex, 0, 0);
			break;
		case POTATO:
			/*AEGfxSetColorToMultiply(0.6f, 0.4f, 0.2f, 1.0f);
			AEGfxSetColorToAdd(0.6f, 0.4f, 0.2f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(0.6f, 0.4f, 0.2f, 1.0f);*/
			AEGfxTextureSet(potatoTex, 0, 0);
			break;
		case BEEF:
			/*AEGfxSetColorToMultiply(0.5f, 0.1f, 0.1f, 1.0f);
			AEGfxSetColorToAdd(0.5f, 0.1f, 0.1f, 1.0f);
			AEGfxSetBlendMode(AE_GFX_BM_BLEND);
			AEGfxSetBlendColor(0.5f, 0.1f, 0.1f, 1.0f);*/
			AEGfxTextureSet(beefTex, 0, 0);
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
	isMoving = false;
	if (AEIsF32Zero(dx) && AEIsF32Zero(dy) ) {
		
	}
	if (AEInputCheckCurr(AEVK_W)) {
		spriteDirection = 1;
		isMoving = true;
		dy += 1;
		
	}if (AEInputCheckCurr(AEVK_S)) {
		spriteDirection = 2;
		isMoving = true;
		dy -= 1;
		
	}if (AEInputCheckCurr(AEVK_A)) {
		spriteDirection = 3;
		isMoving = true;
		dx -= 1;
		
	}
	if (AEInputCheckCurr(AEVK_D)) {
		spriteDirection = 4;
		isMoving = true;
		dx += 1;
	}
	

	if (!AEIsF32Zero(dx) || !AEIsF32Zero(dy)) {
		angle = atan2(dy, dx);

	}
	dt = static_cast<float>(AEFrameRateControllerGetFrameTime());
	frameTimer += dt; // Accumulate time
	
	if (isDashing ) {
		

		mangnituded = sqrt(dx * dx + dy * dy);
		if (mangnituded != 0) {
			normdx = dx / mangnituded;
			normdy = dy / mangnituded;
		}
		else {
			normdx = 0;
				normdy = 0;
		}
		

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

	if (isMoving) {
		if (frameTimer >= 0.1f) { // Change frame every 0.1s
			currentFrame = (currentFrame + 1) % 4;
			frameTimer = 0.0f;
		}
		idleTime = 0.0f; // Reset idle timer
	}
	else {
		idleTime += dt;
		spriteDirection = 0;
		if (idleTime >= 0.2f) { // Change idle frame every 0.2s
			spriteDirection = 0;
			if (frameTimer >= 0.2f) {
				currentFrame = (currentFrame + 1) % 4;
				frameTimer = 0.0f;
			}
		}
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
			return;
		}
			Hand = boxIngredient;                // Player picks up the current ingredient.
			boxIngredient = GetRandomIngredient(boxIngredient); // Randomize the box immediately.
	}
}

void player::playerDrop(Stove& stove) {
	if (AEInputCheckTriggered(AEVK_E)) {
		if (Hand != EMPTY && stove.isDirty==false) {
			if (playerCheckCollison(stove.x, stove.y, stove.width, stove.height))
			{
				if (stove.putIngredient(IngredientToString(Hand))) {
					Hand = EMPTY;
				}
				return;				
				 // Player no longer holds the ingredient
			}
			else if (playerCheckCollison(-720.0f, -300.0f,100.0f, 100.0f))
			{
				Hand = EMPTY;  // Ingredient is removed
			}
			else {
				return;
			}
		}
	}
	if (AEInputCheckTriggered(AEVK_C)) {
		if (playerCheckCollison(stove.x, stove.y, stove.width, stove.height)) {
			if (stove.isDirty) {
				stove.cookingTimer.start(4);
				stove.isCleaning = true;
			}
		}
	}
}
	
void player::playerDash() {

	

	if (dashCounter == 1) {
		if (AEInputCheckTriggered(AEVK_LSHIFT)) {
			
				// Prevent dashing if the player is not moving
			if (AEIsF32Zero(dx) && AEIsF32Zero(dy) ) {
				return;  // Stop execution if no movement direction
			}
		

			isDashing = true;
			cooldown.start(dashDuration);

			}

		}
	if (isDashing) {
		float remainTimedash2 = static_cast<float>( cooldown.getRemainingTime());
	
		if (AEIsF32Zero(remainTimedash2)) {
			dashCounter = 0;
			isDashing = false;
			cooldown2.start(dashCooldown);
		}

	}

	 
	if (AEIsF32Zero(dashCounter)  && !isDashing)
	{
		float remainTimedash = static_cast<float>(cooldown2.getRemainingTime());
		if (remainTimedash <= 0) {
			dashCounter = 1;
		}
	}



	
}

void player::playerUpdate(Stove& stove,RecipeSystem& recipeSystem, QTE &QTE_Gauge) {
	if (playerCheckCollison(stove.x, stove.y, stove.width, stove.height) &&
		stove.canCook(*this))
	{
		if (AEInputCheckTriggered(AEVK_Q) && !QTE_Gauge.isActive) {  // Press Q to Cook
			QTE_Gauge.start();
		}
	}
	if (QTE_Gauge.isActive) {
		QTE_Gauge.update(static_cast<float>(AEFrameRateControllerGetFrameTime()));
		if (QTE_Gauge.isCompleted) {
			if (QTE_Gauge.isSuccess) {
				stove.startCooking(recipeSystem.getActiveRecipes());
			}
			else {
				stove.clearWok(); // Clear the wok if QTE fails
			}
			QTE_Gauge.reset(); // Reset QTE state
		}
	}
}

void player::playerInit()
{
	x={};
	y={};
	normalize_speed={};
	dt={};

	// dash
	dy={}, dx={}, angle={}, normdy={}, normdx={};
	mangnituded={};

    dashCooldown={ 0.5f };
	/*int	  rawX{};
	int   rawY{};*/
	isDashing={ false };
	DirectX={};
	DirectY={};
	DirectionX={};
	DirectionY={};
	Magnitude={};
	dashCounter={ 1 };
	Hand = EMPTY;
}