#pragma once

#include "AEEngine.h"
#include <vector>
#include "player.hpp"

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
		std::vector<int> stoveItems;
		Timer cookingTimer;
		int numIngredients;
		

	public:

		bool canCook() const;
		
		void putIngredients(Ingredients &ingredient);

		double cookIngredients();

		double remainingCookingTime()const;
};

extern Stove Wok;