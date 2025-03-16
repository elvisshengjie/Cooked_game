#include "AEEngine.h"
#include <crtdbg.h>
#include "utils.hpp"
#include "Ingredients.hpp"
#include "player.hpp"
#include <iostream>

int score{};
void Timer::start(double duration) {
	countdownDuration = duration;
	startTime = AEGetTime(nullptr);
	pausedTime = 0.0;
}

double Timer::getRemainingTime() const {
	if (pauseTimer) { return pausedTime; }
	double elapsedTime = AEGetTime(nullptr) - startTime;
	return (countdownDuration - elapsedTime > 0.0) ? (countdownDuration - elapsedTime) : 0.0;
}

bool Timer::completed() const {
	return getRemainingTime() <= 0.0;
}

void Timer::pauseresume() {
	if (!pauseTimer) {
		 pausedTime = getRemainingTime();
		 pauseTimer = true;
	}
	else {
		startTime = AEGetTime(nullptr) - (countdownDuration - pausedTime);
		pauseTimer = false;
	}
}
// Constructor initializes the Wok position

bool Stove::putIngredient(const std::string& ingredient)
{
	if (isCooking) {
		return false;
	}
	//Add return codes for edge cases, testing.
	if (!isCooking && stoveItems.size() < 7) {
		stoveItems.push_back(ingredient);
		return true;
	}
	return false;
}

//clears items in stove after cooking
void Stove::clearWok() {
	stoveItems.clear();
	isCooking = false;
	cookingRecipeName = "";
}

bool Stove::canCook(player& player) const
{
	return !isCooking && stoveItems.size() >= 2 && player.playerCheckCollison(x, y, width, height) && !isDirty;
}

void Stove::startCooking(const std::vector<Recipe>& activeRecipes)
{
	if (isCooking || stoveItems.size() < 2 || isDirty)return;
	isCooking = true;

	double cookingTime = 2.0 + (1 * stoveItems.size());

	cookingTimer.start(cookingTime);

	recipeMatched = false;

	cookingRecipeName = "Wrong Dish";

	for (auto const recipe : activeRecipes) {
		if (recipe.matchesWok(stoveItems)) {
			cookingRecipeName = recipe.Name;
			recipeMatched = true;
			break;
		}
	}

}

double Stove::remainingCookingTime()
{
	if (!isCooking) return 0.0;

	double remainTime = cookingTimer.getRemainingTime();
	if (remainTime <= 0.0) {
		isCooking = false;
	}
	return remainTime;
}
void Stove::update(RecipeSystem& recipeSystem) {
	if (isCooking && cookingTimer.completed()) {
		std::cout << "Cooking completed";
		static std::random_device rd;
		static std::mt19937 engine(rd());
		std::uniform_int_distribution<int> distribution(1, 10); // valid indices: 1 to 10
		if (distribution(engine) >7) {
			isDirty = true;
			std::cout << "Stove needs cleaning!\n";
		}
		for (const Recipe& recipe : recipeSystem.getActiveRecipes()) {
			if (recipe.Name == cookingRecipeName) {
				recipeSystem.replaceRecipe(recipe);
				break;	
			}
		}
		clearWok();
		score = updateScore(recipeMatched);
	}
	if (isDirty) {
		if (isCleaning && cookingTimer.getRemainingTime() <= 0) {
			isDirty = false;
			isCleaning = false;
			std::cout << "|-just cleaned-|";
		}
	}
}
// Getter Functions -> actually i can just put everything public .. no client gonna have access to my source code... im dumb

std::string Stove::getCookingRecipeName() const {
	return cookingRecipeName;
}

std::vector<std::string> Stove::getStoveItems()const {
	return stoveItems;
}

QTE::QTE() {
	reset();
}

void QTE::update(float dt) {
	if (!isActive) {
		return;
	}
	if (movingRight) {
		sliderPos += sliderSpd * dt;
		if (sliderPos >= 1.0f) {
			sliderPos = 1.0f;
			movingRight = false;
		}
	}
	else {
		sliderPos -= sliderSpd * dt;
		if (sliderPos <= 0.0f) {
			sliderPos = 0.0f;
			movingRight = true;
		}
	}
	if (AEInputCheckTriggered(AEVK_R)) {
		isCompleted = true;

		if (checkTarget()) {
			isSuccess = true;
		}
		else {
			isSuccess = false;
		}
	}
}
bool QTE::checkTarget()const {
	return (sliderPos >= targetZoneStart && sliderPos <= targetZoneEnd);
}

void QTE::render(AEGfxVertexList* mesh , AEGfxTexture* barTex , AEGfxTexture* sliderTex , AEGfxTexture* targetTex) const{

	if (!isActive) {
		return;
	}
	AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
	AEMtx33 bgTransform, sliderTransform, targetTransform;

	AEMtx33Scale(&bgTransform, w, h);
	AEMtx33TransApply(&bgTransform, &bgTransform, x, y);
	AEGfxSetTransform(bgTransform.m);
	AEGfxSetColorToAdd(0.5f, 0.5f, 0.5f, 1.0f);
	AEGfxTextureSet(barTex, 0, 0);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
	

	float targetStartX = x - w / 2 + targetZoneStart * w;
	float targetWidth = (targetZoneEnd - targetZoneStart) * w;


	AEMtx33Scale(&targetTransform, targetWidth, h);
	AEMtx33TransApply(&targetTransform, &targetTransform, targetStartX + targetWidth / 2, y);
	AEGfxSetTransform(targetTransform.m);
	AEGfxSetColorToAdd(0.0f, 1.0f, 0.0f, 1.0f);
	AEGfxTextureSet(targetTex, 0, 0);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	float sliderX = x - w / 2 + sliderPos * w;

	AEMtx33Scale(&sliderTransform, 10.0f, h * 1.5f);
	AEMtx33TransApply(&sliderTransform, &sliderTransform, sliderX, y);
	AEGfxSetTransform(sliderTransform.m);
	AEGfxSetColorToAdd(1.0f, 0.0f, 0.0f, 1.0f);
	AEGfxTextureSet(sliderTex, 0, 0);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void QTE::reset() {
	isActive = false; // Make sure QTE is deactivated on reset
	isCompleted = false;
	isSuccess = false;

}
	

void QTE::start() {
	if (isActive) return;
	isActive = true;
	isCompleted = false;
	isSuccess = false;
	sliderPos = 0.0f;

	std::cout << isActive;
	// Randomize the target zone position
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.1f, 0.8f);
	float zoneWidth = 0.2f; // 20% of the gauge as the target zone
	targetZoneStart = dist(gen);
	targetZoneEnd = targetZoneStart + zoneWidth;
}

int updateScore(bool recipeMatched)
{
	if (recipeMatched)
	{
		score += 5;
	}
	else
	{
		score -= 2;
	}
	return score;
}

