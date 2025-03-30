/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file utils.cpp
@author1 Norman Chan (chan.f)
- Timer Class
-
@author2
@course csd1451s25 Software Engineering Project 2
@section a
*//*______________________________________________________________________*/
#include "AEEngine.h"
#include <crtdbg.h>
#include "utils.hpp"
#include "Ingredients.hpp"
#include "player.hpp"
#include <iostream>

int score{};
double baseTime{ 2.0 };
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
int maxSize{ 6 };
bool Stove::putIngredient(const Ingredients ingredient)
{
	if (currentState == StoveState::IDLE && stoveItems.size() < maxSize) {
		stoveItems.push_back(ingredient);
		return true;
	}
	return false;
}

//clears items in stove after cooking
void Stove::clearWok() {
	stoveItems.clear();
	cookingRecipeName = "";
}

int minSize{ 2 };
bool Stove::canCook(player& player) const
{
	return currentState == StoveState::IDLE && stoveItems.size() >= minSize && player.playerCheckCollison(x, y, width, height);
}

void Stove::startCooking(const std::vector<Recipe>& activeRecipes, AEAudio cookingSound, AEAudioGroup sfx)
{
	if (currentState != StoveState::IDLE || stoveItems.size() < minSize) return;
	currentState = StoveState::COOKING;
	double cookingTime = baseTime + stoveItems.size();

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
	// Play cooking sound
	AEAudioPlay(cookingSound, sfx, 1.0f, 1.0f, 0); // false for non-looping playback
}

double Stove::remainingCookingTime()
{
	if (currentState != StoveState::COOKING && currentState != StoveState::CLEANING) return 0.0;

	double remainTime = cookingTimer.getRemainingTime();
	return remainTime;
}

void Stove::update(RecipeSystem& recipeSystem, AEAudioGroup sfx) {
	if (currentState == StoveState::COOKING && cookingTimer.completed()) {
		static std::random_device rd;
		static std::mt19937 engine(rd());
		std::uniform_int_distribution<int> distribution(1, 10); // valid indices: 1 to 10
		if (distribution(engine) >7) {
			currentState = StoveState::DIRTY;
		}
		else 
		{
			currentState = StoveState::IDLE;
		}
		for (const Recipe& recipe : recipeSystem.getActiveRecipes()) {
			if (recipe.Name == cookingRecipeName) {
				recipeSystem.replaceRecipe(recipe);
				break;	
			}
		}
		
		score = updateScore(recipeMatched, stoveItems.size());
		clearWok();

		AEAudioStopGroup(sfx);
	}
	if (currentState == StoveState::CLEANING && cookingTimer.getRemainingTime() <= 0) {
		currentState = StoveState::IDLE;
	}
	
}
// Getter Functions 

std::string Stove::getCookingRecipeName() const {
	return cookingRecipeName;
}

std::vector<Ingredients> Stove::getStoveItems()const {
	return stoveItems;
}

QTE::QTE() {
	reset();
}

float scaleEnd{ 1.0f };
float scaleStart{ 0.0f };
void QTE::update(float dt) {
	if (!isActive) {
		return;
	}
	if (movingRight) {
		sliderPos += sliderSpd * dt;
		if (sliderPos >= scaleEnd) {
			sliderPos = scaleEnd;
			movingRight = false;
		}
	}
	else {
		sliderPos -= sliderSpd * dt;
		if (sliderPos <= scaleStart) {
			sliderPos = scaleStart;
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
	sliderPos = scaleStart;

	// Randomize the target zone position
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(0.1f, 0.8f);
	float zoneWidth = 0.2f; // 20% of the gauge as the target zone
	targetZoneStart = dist(gen);
	targetZoneEnd = targetZoneStart + zoneWidth;
}

int updateScore(bool recipeMatched, size_t stoveItems)
{
	int multiplier{ 2 };
	if (recipeMatched)
	{
		score += static_cast<int>(stoveItems) * multiplier;
	}
	else
	{
		score -= 3;
	}
	return score;
}

