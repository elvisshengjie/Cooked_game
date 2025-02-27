#pragma once

#include "AEEngine.h"
#include <vector>
#include <string>


class RecipeSystem;

class player;

class Recipe;

class Timer {
private:

	double countdownDuration; //Countdown in s

	double startTime; //Start Time in s

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

class QTE {
	private:
		float x = 0.0f; // Center of the gauge on screen
		float y = -0.4f;
		float w = 600.0f;
		float h = 20.0f;
		
		float sliderPos = 0.0f;
		float sliderSpd = 0.01f; 

		float targetZoneStart = 0.3f; // Start of the target zone (0 to 1) - NOMNOMlised
		float targetZoneEnd = 0.5f;  // End of the target zone (0 to 1) - NOMNOMlised 

		bool movingRight = true;

	public:
		QTE();

		void update(float dt);

		//void render(AEGfxVertexList* mesh);

		bool checkTarget() const;

		void reset();

		void render(AEGfxVertexList* mesh)const;
		////getters
		//float getX()const;
		//float getY()const;
		//float getW()const;
		//float getH()const;
		//float getTargetStart()const;
		//float getTargetZoneEnd()const;
		//float getSliderPos()const;
};