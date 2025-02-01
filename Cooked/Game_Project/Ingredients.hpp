#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib> 
#include "utils.hpp"

//class Timer;
/*
	Ingredients :
	chicken, rice ,egg , cheese , potato , beef


	Recipes:
	Cheesy Potato Mash (Potato, Cheese) -2

	Cheese Omelette (Cheese, Egg) -2

	Beef stir-fry with rice (Beef , rice ,egg) -3

	Chicken Fried Rice (Chicken, Rice, Egg)-3

	Beef & Cheese Stuffed Potato (Potato , Beef ,Cheese ,Egg)-4

	Loaded Protein Bowl (Chicken, Rice, Egg, Cheese, Potato, Beef)-6
*/

enum Ingredients { EMPTY = 0, CHICKEN, RICE, EGG, CHEESE, POTATO, BEEF };
inline std::string IngredientToString(Ingredients ing)
{
	switch (ing)
	{
	case CHICKEN: return "CHICKEN";
	case RICE:    return "RICE";
	case EGG:     return "EGG";
	case CHEESE:  return "CHEESE";
	case POTATO:  return "POTATO";
	case BEEF:    return "BEEF";
	default:      return "???";
	}
}

// Forward declare (prototype) only, no function body
Ingredients GetRandomIngredient();
std::string IngredientToString(Ingredients ing);
extern std::vector<Ingredients> g_currentBoxIngredients;





const std::string validIngredients[] = { "chicken", "rice", "egg", 
										"cheese", "potato", "beef" };

class Recipe {
public:
	std::string Name;
	std::vector<std::string> Ingredients; // List of ingredients

	Recipe(std::string recipeName, std::vector<std::string> ingredientsList);

	bool matchesWok(const std::vector<std::string>& wokIngredients) const;
};

class RecipeSystem {
private:
	std::vector<Recipe> allRecipes;  // Store all possible recipes
	std::vector<Recipe> activeRecipes; // Store 3 currently active recipes
	Timer recipeTimer;  // Timer to refresh recipes

public:
	RecipeSystem();

	void update();
	const std::vector<Recipe>& getActiveRecipes() const;
};