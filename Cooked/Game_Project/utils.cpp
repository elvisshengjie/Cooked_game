#include "AEEngine.h"
#include <crtdbg.h>
#include "utils.hpp"
#include "Ingredients.hpp"
#include "player.hpp"
#include <iostream>

//Timer::Timer(double duration) : countdownDuration(duration), startTime(0.0) {}

void Timer::start(double duration) {
	this->countdownDuration = duration;
	startTime = AEGetTime(nullptr);
}

double Timer::getRemainingTime() const {
	double currTime = AEGetTime(nullptr);
	double elapsedTime = currTime - startTime;
	return (countdownDuration - elapsedTime) > 0.0 ? (countdownDuration - elapsedTime) : 0.0;
}

bool Timer::completed() const {
	return getRemainingTime() <= 0.0;
}

// Constructor initializes the Wok position
Stove::Stove(float posX, float posY, float w, float h)
	: x{ posX }, y{ posY }, width{ w }, height{ h }, isCooking{ false } {}

Stove Wok(-50.0f, -200.0f, 200.0f, 100.0f);

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
	return !isCooking && stoveItems.size() >= 2 && player.playerCheckCollison(x, y, width, height);
}

void Stove::startCooking(const std::vector<Recipe>& activeRecipes)
{
	if (isCooking || stoveItems.size() < 2) {
		return;
	}
	isCooking = true;

	double cookingTime = 2.0 + (1 * stoveItems.size());

	cookingTimer.start(cookingTime);

	bool recipeMatched = false;

	cookingRecipeName = "Unknown Dish";

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
		for (const Recipe& recipe : recipeSystem.getActiveRecipes()) {
			if (recipe.Name == cookingRecipeName) {
				recipeSystem.replaceRecipe(recipe);
				break;	
			}
		}
		clearWok();
	}
}

// Getter Functions
float Stove::getX() const
{
	return x;
}

float Stove::getY() const
{
	return y;
}

float Stove::getW() const {
	return width;
}

float Stove::getH() const {
	return height;
}

bool Stove::isCurrentlyCooking() const {
	return isCooking;
}

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
}
bool QTE::checkTarget()const {
	return (sliderPos >= targetZoneStart && sliderPos <= targetZoneEnd);
}

void QTE::render(AEGfxVertexList* mesh) const{

	AEMtx33 bgTransform, sliderTransform, targetTransform;

	AEMtx33Scale(&bgTransform, w, h);
	AEMtx33TransApply(&bgTransform, &bgTransform, x, y);
	AEGfxSetTransform(bgTransform.m);
	AEGfxSetBlendColor(0.5f, 0.5f, 0.5f, 1.0f);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	float targetStartX = x - w / 2 + targetZoneStart * w;
	float targetWidth = (targetZoneEnd - targetZoneStart) * w;


	AEMtx33Scale(&targetTransform, targetWidth, h);
	AEMtx33TransApply(&targetTransform, &targetTransform, targetStartX + targetWidth / 2, y);
	AEGfxSetTransform(targetTransform.m);
	AEGfxSetBlendColor(0.0f, 1.0f, 0.0f, 1.0f);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

	float sliderX = x - w / 2 + sliderPos * w;

	AEMtx33Scale(&sliderTransform, 10.0f, h * 1.5f);
	AEMtx33TransApply(&sliderTransform, &sliderTransform, sliderX, y);
	AEGfxSetTransform(sliderTransform.m);
	AEGfxSetBlendColor(1.0f, 0.0f, 0.0f, 1.0f);
	AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

}

void QTE::reset() {
	sliderPos = 0.0f;
	movingRight = true;

	// Randomize the target zone position
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.1f, 0.8f);
	float zoneWidth = 0.2f; // 20% of the gauge as the target zone
	targetZoneStart = dist(gen);
	targetZoneEnd = targetZoneStart + zoneWidth;
}
//float QTE::getX()const { return x; }
//float QTE::getY()const { return y; }
//float QTE::getW()const { return w; }
//float QTE::getH()const { return h; }
//float QTE::getTargetStart()const { return targetZoneStart; }
//float QTE::getTargetZoneEnd()const { return targetZoneEnd; }
//float QTE::getSliderPos()const { return sliderPos; }