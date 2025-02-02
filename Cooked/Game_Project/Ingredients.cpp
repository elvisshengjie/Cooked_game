
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include "Ingredients.hpp"
#include "utils.hpp"


Ingredients GetRandomIngredient(Ingredients previousIngredient)
{
	// Use a static random engine so that it isn't re-seeded on every call.
	static std::random_device rd;
	static std::mt19937 engine(rd());
	std::uniform_int_distribution<int> distribution(1, 6); // valid indices: 1 to 6

	Ingredients newIngredient;
	do {
		newIngredient = static_cast<Ingredients>(distribution(engine));
	} while (previousIngredient != EMPTY && newIngredient == previousIngredient);

	return newIngredient;
}
std::vector<Ingredients> g_currentBoxIngredients(3);

//std::string IngredientToString(Ingredients ing)
//{
//	switch (ing)
//	{
//	case CHICKEN: return "CHICKEN";
//	case RICE:    return "RICE";
//	case EGG:     return "EGG";
//	case CHEESE:  return "CHEESE";
//	case POTATO:  return "POTATO";
//	case BEEF:    return "BEEF";
//	default:      return "???";
//	}
//}
//Constructor
Recipe::Recipe(std::string recipeName, std::vector<std::string> ingredientList)
	: Name(recipeName), Ingredients(ingredientList) {}

bool Recipe::matchesWok(const std::vector<std::string> &wokIngredients)const
{
	if(wokIngredients.size() != Ingredients.size()) {
		return false;
	}

	//sorting both lists for comparisons - so the order does not matter
	std::vector<std::string> sortedWok = wokIngredients;
	std::vector<std::string> sortedRecipe = Ingredients;

	std::sort(sortedWok.begin(), sortedWok.end());
	std::sort(sortedRecipe.begin(), sortedRecipe.end());

	return sortedWok == sortedRecipe;
}

RecipeSystem::RecipeSystem() {
	std::srand(static_cast<unsigned int>(std::time(0)));; // Srand Seed with time

	allRecipes.push_back(Recipe("Cheesy Potato Mash", { "Potato", "Cheese" }));
	allRecipes.push_back(Recipe("Cheese Omelette", { "Cheese", "Egg" }));
	allRecipes.push_back(Recipe("Beef Stir-Fry with Rice", { "Beef", "Rice", "Egg" }));
	allRecipes.push_back(Recipe("Chicken Fried Rice", { "Chicken", "Rice", "Egg" }));
	allRecipes.push_back(Recipe("Beef & Cheese Stuffed Potato", { "Potato", "Beef", "Cheese", "Egg" }));
	allRecipes.push_back(Recipe("Loaded Protein Bowl", { "Chicken", "Rice", "Egg", "Cheese", "Potato", "Beef" }));

	// Start with 3 random recipes
	for (int i = 0; i < 3; i++) {
		activeRecipes.push_back(allRecipes[std::rand() % allRecipes.size()]);
	}

	recipeTimer.start(10.0); // Timer for refreshing recipes
}
void RecipeSystem::update() {
	if (recipeTimer.completed()) {
		activeRecipes.erase(activeRecipes.begin()); // Remove the oldest recipe
		activeRecipes.push_back(allRecipes[std::rand() % allRecipes.size()]); // Add a new random recipe
		recipeTimer.start(10.0); // Restart timer
	}
}

const std::vector<Recipe>& RecipeSystem::getActiveRecipes() const {
	return activeRecipes;
}
