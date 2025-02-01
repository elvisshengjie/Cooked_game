#pragma once

#include "AEEngine.h"
#include <vector>
#include <string>


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
	bool isCooking;
	float x, y, width, height;


public:

	Stove(float posX, float posY, float w, float h);

	void putIngredient(const std::string& ingredient);

	void clearWok();

	bool canCook(player& player) const;

	//bool matchesCurrentRecipe(const Recipe& recipe) const;

	void startCooking();

	double remainingCookingTime();

	bool matchesAnyActiveRecipe(const std::vector<Recipe>& activeRecipes) const;

	float getX() const;

	float getY() const;

	float getW() const;

	float getH() const;

};
extern Stove Wok;
