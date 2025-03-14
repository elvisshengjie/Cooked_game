#pragma once

#include "AEEngine.h"
#include <vector>
#include <string>

class RecipeSystem;

class player;

class Recipe;


class Timer {

public:


	double countdownDuration; //Countdown in s

	double startTime; //Start Time in s


	double pausedTime{};

	bool pauseTimer = false;



	void start(double duration);

	double getRemainingTime() const;

	void pauseresume();

	bool completed() const  ;
};

class Stove
{
private:
	std::vector<std::string> stoveItems;

	std::string cookingRecipeName;


public:

	Timer cookingTimer{};

	bool isCooking=false;

	bool isCleaning = false;

	bool isDirty = false;

	bool recipeMatched = false;

	float x{ -50.0f };
	float y = { -200.0f };
	float width = { 200.0f };
	float height = { 100.0f };


public:

	bool putIngredient(const std::string& ingredient);

	void clearWok();

	bool canCook(player& player) const;

	void startCooking(const std::vector<Recipe>& activeRecipes);

	void update(RecipeSystem &recipeSystem);

	double remainingCookingTime();

	std::string getCookingRecipeName()const;

	std::vector<std::string> getStoveItems()const;


};
extern Stove Wok;

class QTE {
private:
	float x{ 0.0f }; // Center of the gauge on screen
	float y{ -0.4f };
	float w = { 600.0f };
	float h = { 20.0f };

	float sliderPos = { 0.0f }; // Start of the slider Position (0 to 1) - NOMNOMlised
	float sliderSpd = { 0.8f};

	float targetZoneStart = { 0.3f }; // Start of the target zone (0 to 1) - NOMNOMlised
	float targetZoneEnd = {0.5f};  // End of the target zone (0 to 1) - NOMNOMlisesd 

	bool movingRight = true;

	public:

		QTE();

		void update(float dt);

		bool checkTarget() const;

		void reset();

		void render(AEGfxVertexList* mesh , AEGfxTexture* BarTex , AEGfxTexture* targetTex , AEGfxTexture* sliderTex)const;

		void start();

		bool isActive = false;

		bool isCompleted = false;

		bool isSuccess = false;

};
extern int score;
int updateScore(bool);
