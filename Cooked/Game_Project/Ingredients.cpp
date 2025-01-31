
#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include "Ingredients.hpp"
#include "utils.hpp"

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
	std::srand(std::time(0)); // Srand Seed with time

	allRecipes.push_back(Recipe("Cheesy Potato Mash", { "Potato", "Cheese" }));
	allRecipes.push_back(Recipe("Cheese Omelette", { "Cheese", "Egg" }));
	allRecipes.push_back(Recipe("Beef Stir-Fry with Rice", { "Beef", "Rice", "Egg" }));
	allRecipes.push_back(Recipe("Chicken Fried Rice", { "Chicken", "Rice", "Egg" }));
	allRecipes.push_back(Recipe("Beef & Cheese Stuffed Potato", { "Potato", "Beef", "Cheese", "Egg" }));
	allRecipes.push_back(Recipe("Loaded Protein Bowl", { "Chicken", "Rice", "Egg", "Cheese", "Potato", "Beef" }));

	// Start with 3 random recipes
	for (int i = 0; i < 2; i++) {
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
//void randomizenIngredient()
//
//
//void print_c(const std::vector < std::string > & x) {
//	for (std::string element : x) {
//>>>>>>> main
//
//		std::cout << element << " ";
//	}
//	std::cout << '\n';
//}
//
//int main()
//{
//	std::random_device rd;
//	std::mt19937 g(rd());
//	std::vector<std::string> v{ "apple","cake","egg","juice"};
//	std::vector < std::string > original_v;
//	
//	std::copy(v.begin(), v.end(), std::back_inserter(original_v));
//	print_c(original_v);
//	
//print_c(v);
//
//std::swap(v[0], v.back());
//std::shuffle(v.begin(), v.end() - 1, g);
//print_c(v);
//
//
//
//}
//*/