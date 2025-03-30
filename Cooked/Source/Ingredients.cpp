/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file Ingredients.cpp
@author1 Elvis lim sheng jie(elvisshengjie.lim)
- Ingredients GetRandomIngredient
@author2
@course csd1451s25 Software Engineering Project 2
@section a
*//*______________________________________________________________________*/

#include "Ingredients.hpp"
#include "utils.hpp"

int minIngredients{ 1 };
int maxIngredients{ 6 };

Ingredients GetRandomIngredient(Ingredients previousIngredient)
{
	// Use a static random engine so that it isn't re-seeded on every call.
	static std::random_device rd;
	static std::mt19937 engine(rd());
	std::uniform_int_distribution<int> distribution(minIngredients, maxIngredients); // valid indices: 1 to 6

	Ingredients newIngredient;
	do {
		newIngredient = static_cast<Ingredients>(distribution(engine));
	} while (previousIngredient != EMPTY && newIngredient == previousIngredient);

	return newIngredient;
}
std::vector<Ingredients> g_currentBoxIngredients(3);

//Constructor
Recipe::Recipe(std::string recipeName, std::vector<::Ingredients> ingredientList)
	: Name(recipeName), Ingredients(ingredientList) {}

bool Recipe::matchesWok(const std::vector<::Ingredients> &wokIngredients)const
{
	if(wokIngredients.size() != Ingredients.size()) {
		return false;
	}
	std::vector<::Ingredients> sortedRecipe = Ingredients;
	std::vector<::Ingredients> sortedWok = wokIngredients;

	std::sort(sortedRecipe.begin(), sortedRecipe.end());
	std::sort(sortedWok.begin(), sortedWok.end());

	return sortedRecipe == sortedWok;

}

int maxRecipesDisplay{ 3 };
double baseTimer{ 15.0f };
RecipeSystem::RecipeSystem() {
	std::srand(static_cast<unsigned int>(std::time(0)));; // Srand Seed with time

	allRecipes.push_back(Recipe("Cheesy Potato Mash", { POTATO, CHEESE }));
	allRecipes.push_back(Recipe("Cheese Omelette", { CHEESE, EGG }));
	allRecipes.push_back(Recipe("Beef Stir-Fry with Rice", { BEEF, RICE, EGG }));
	allRecipes.push_back(Recipe("Chicken Fried Rice", { CHICKEN, RICE, EGG }));
	allRecipes.push_back(Recipe("Beef & Cheese Stuffed Potato", { POTATO, BEEF, CHEESE, EGG }));
	allRecipes.push_back(Recipe("Loaded Protein Bowl", { CHICKEN, RICE, EGG, CHEESE, POTATO, BEEF }));

	// Start with 3 random recipes
	for (int i = 0; i < maxRecipesDisplay; i++) {
		activeRecipes.push_back(allRecipes[std::rand() % allRecipes.size()]);
		activeRecipes[i].recipeTimer.start(activeRecipes[i].Ingredients.size() * baseTimer);
	}

}

void RecipeSystem::update() {
	for (int i = 0; i < maxRecipesDisplay; ++i) {
		if (activeRecipes[i].recipeTimer.getRemainingTime() <= 0.0f) {
			activeRecipes[i] = generateRandomRecipe();
			activeRecipes[i].recipeTimer.start(activeRecipes[i].Ingredients.size() * baseTimer); // Restart timer
		}
	}
}

const std::vector<Recipe>& RecipeSystem::getActiveRecipes() const{
	return activeRecipes;
}

Recipe RecipeSystem::generateRandomRecipe() {
	if (allRecipes.empty()) {
		std::cerr << "Error: No available recipes in allRecipes!" << std::endl;
		return Recipe("", {}); // Return an empty recipe if no options exist
	}

	int randomIndex = rand() % allRecipes.size();  // Pick a random index
	return allRecipes[randomIndex];  // Return a randomly chosen recipe
}

void RecipeSystem::replaceRecipe(const Recipe& completedRecipe) {
	for (size_t i = 0; i < activeRecipes.size(); ++i) {
		if (activeRecipes[i].Name == completedRecipe.Name) {
			activeRecipes[i] = generateRandomRecipe();
			activeRecipes[i].recipeTimer.start(activeRecipes[i].Ingredients.size() * 15.0f);
			return;
		}
	}
}

void RecipeSystem::pauseRecipeTimers() {
	for (auto& recipe : activeRecipes) {
		if (!recipe.recipeTimer.completed()) {
			recipe.recipeTimer.pauseresume(); // Toggle pause/resume
		}
	}
}