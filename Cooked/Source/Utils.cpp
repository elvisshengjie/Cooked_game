
#include "AEEngine.h"
#include <crtdbg.h>
#include "utils.hpp"


Timer::Timer(f64 duration) : countdownDuration(duration), startTime(0.0) {}

void Timer::start() {
	startTime = AEGetTime(nullptr);
}

f64 Timer::getRemainingTime() const {
	f64 currTime = AEGetTime(nullptr);
	f64 elapsedTime = currTime - startTime;
	return (countdownDuration - elapsedTime) > 0.0 ? (countdownDuration - elapsedTime) : 0.0;
}

bool Timer::completed() const {
	return getRemainingTime() <=0.0;
}









Stove::Stove(f64 duration) : cookingTimer(duration) {}

f64 Stove::remainingCookingTime() const 
{
	return this->cookingTimer.getRemainingTime();
}

bool Stove::canCook() const
{
	return this->stoveItems.size() >= 2 && this->remainingCookingTime() <= 0.0;
}

void Stove::putIngredients(Ingredients &ingredient)  
{
	this->stoveItems.push_back(ingredient);
}

f64 Stove::cookIngredients()  
{
	if(AEInputCheckTriggered(AEVK_E) && this->canCook() )
	{
		this->stoveItems.clear();
		this->cookingTimer.start();
		return this->cookingTimer.getRemainingTime();
	}
	else return 0.0;

	//add check for number of ingredients , take in cooking time.
}
Stove Wok;
