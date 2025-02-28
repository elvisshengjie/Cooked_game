#pragma once

#include "AEEngine.h"
#include <vector>
#include <string>

class RecipeSystem;

class player;

class Recipe;

class Timer {
private:

	double countdownDuration; //Countdown in s

	double startTime; //Start Time in s

public:

	void start(double duration);

	double getRemainingTime() const;

	bool completed() const;
};

class Stove
{
private:
	std::vector<std::string> stoveItems;

	Timer cookingTimer{};

	std::string cookingRecipeName;

	bool isCooking;

	float x{ -50.0f };
	float y = { -200.0f };
	float width = {200.0f};
	float height = { 100.0f };

	bool recipeMatched;
public:

	bool putIngredient(const std::string& ingredient);

	void clearWok();

	bool canCook(player& player) const;

	void startCooking(const std::vector<Recipe>& activeRecipes);

	void update(RecipeSystem &recipeSystem);

	double remainingCookingTime();

	float getX() const;

	float getY() const;

	float getW() const;

	float getH() const;
	
	bool isCurrentlyCooking()const;

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

		void render(AEGfxVertexList* mesh)const;

		void start();

		bool isActive = false;

		bool isCompleted = false;

		bool isSuccess = false;

};
extern int score;
int updateScore(bool);
