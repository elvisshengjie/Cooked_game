#pragma once

#include "AEEngine.h"
#include <vector>
#include "player.hpp"

class Timer {
private:
	f64 countdownDuration; //countdown in s
	f64 startTime; //start time in s

public:
	Timer(f64 duration);

	void start();

	f64 getRemainingTime() const;

	bool completed() const;
};

class Stove
{
	private:
		std::vector<int> stoveItems;
		Timer cookingTimer;

	public:
		Stove(f64 duration);

		bool canCook() const;
		
		void putIngredients(Ingredients &ingredient);

		f64 cookIngredients();

		f64 remainingCookingTime()const;
};

extern Stove Wok;