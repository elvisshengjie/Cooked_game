/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file Ingredients.hpp
@author1 
@author2
@course csd1451s25 Software Engineering Project 2
@section a
*//*______________________________________________________________________*/
#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib> 
#include <random>
#include <iostream>
#include "utils.hpp"

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
Ingredients GetRandomIngredient(Ingredients previousIngredient = EMPTY);
std::string IngredientToString(Ingredients ing);
extern std::vector<Ingredients> g_currentBoxIngredients;


class Recipe {
public:
	std::string Name;
	std::vector<Ingredients> Ingredients; // List of ingredients

	Recipe(std::string recipeName, std::vector<::Ingredients> ingredientsList);

	bool matchesWok(const std::vector<::Ingredients>& wokIngredients) const;

	Timer recipeTimer;  // Timer to refresh recipes


};

class RecipeSystem {
private:
	std::vector<Recipe> allRecipes;  // Store all possible recipes
	std::vector<Recipe> activeRecipes; // Store 3 currently active recipes

public:

	bool isPaused = false;

	RecipeSystem();

	void update();

	const std::vector<Recipe>& getActiveRecipes()const ;

	Recipe generateRandomRecipe();

	void replaceRecipe(const Recipe& completedRecipe);

	void pauseRecipeTimers();
};

