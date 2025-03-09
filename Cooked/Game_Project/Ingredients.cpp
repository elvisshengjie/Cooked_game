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

	allRecipes.push_back(Recipe("Cheesy Potato Mash", { "POTATO", "CHEESE" }));
	allRecipes.push_back(Recipe("Cheese Omelette", { "CHEESE", "EGG" }));
	allRecipes.push_back(Recipe("Beef Stir-Fry with Rice", { "BEEF", "RICE", "EGG" }));
	allRecipes.push_back(Recipe("Chicken Fried Rice", { "CHICKEN", "RICE", "EGG" }));
	allRecipes.push_back(Recipe("Beef & Cheese Stuffed Potato", { "POTATO", "BEEF", "CHEESE", "EGG" }));
	allRecipes.push_back(Recipe("Loaded Protein Bowl", { "CHICKEN", "RICE", "EGG", "CHEESE", "POTATO", "BEEF" }));

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
			return;
		}
	}
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
