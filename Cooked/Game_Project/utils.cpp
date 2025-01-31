#include "AEEngine.h"
#include <crtdbg.h>
#include "utils.hpp"
#include "Ingredients.hpp"
#include "player.hpp"

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
	: x(posX), y(posY), width(w), height(h), isCooking(false) {}

Stove Wok(300.0f, 200.0f, 50.0f, 50.0f);


void Stove::putIngredient(const std::string& ingredient)
{
	//Add return codes for edge cases, testing.
	if (!isCooking) {
		stoveItems.push_back(ingredient);
	}
}

//clears items in stove after cooking
void Stove::clearWok() {
	stoveItems.clear();
}

bool Stove::canCook(player& player) const
{
	return !isCooking && stoveItems.size() >= 2 && player.playerCheckCollison(x, y, width, height);
}

// bool Stove::matchesCurrentRecipe(const Recipe& recipe) const {
// 	return recipe.matchesWok(stoveItems);
// }

bool Stove::matchesAnyActiveRecipe(const std::vector<Recipe>& activeRecipes) const {
	for (const Recipe& recipe : activeRecipes) {
		if (recipe.matchesWok(stoveItems)) {
			return true; 
		}
	}
	return false; 
}
void Stove::startCooking()
{
	if (!isCooking) {
		int numIngredients = stoveItems.size();
		double cookingTime = 2.0 + numIngredients;
		cookingTimer.start(cookingTime);
		isCooking = true;
		stoveItems.clear();
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

float Stove::getX() const
{
	return x;
}

float Stove::getY() const
{
	return y;
}