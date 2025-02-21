#pragma once

#include "AEEngine.h"
#include <vector>
#include <string>


class RecipeSystem;

class player;

class Recipe;

class Timer {
private:
	double countdownDuration; //countdown in s
	double startTime; //start time in s

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
	float x, y, width, height;
	bool recipeMatched;

public:

	Stove(float posX, float posY, float w, float h);

	bool putIngredient(const std::string& ingredient);

	void clearWok();

	bool canCook(player& player) const;

	void startCooking(const std::vector<Recipe>& activeRecipes);

	void update(RecipeSystem &recipeSystem);

	double remainingCookingTime();

	//bool matchesAnyActiveRecipe(const std::vector<Recipe>& activeRecipes) const;

	float getX() const;

	float getY() const;

	float getW() const;

	float getH() const;
	
	bool isCurrentlyCooking()const;

	std::string getCookingRecipeName()const;

	std::vector<std::string> getStoveItems()const;
};
extern Stove Wok;
extern int score;
int updateScore(bool);