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

// bool Stove::matchesCurrentRecipe(const Recipe& recipe) const {
// 	return recipe.matchesWok(stoveItems);
// }

//bool Stove::matchesAnyActiveRecipe(const std::vector<Recipe>& activeRecipes) const {
//	for (const Recipe& recipe : activeRecipes) {
//		if (recipe.matchesWok(stoveItems)) {
//			return true;
//		}
//	}
//	return false;
//}
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
