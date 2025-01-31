
#include "AEEngine.h"
#include <crtdbg.h>
#include "utils.hpp"


//Timer::Timer(double duration) : countdownDuration(duration), startTime(0.0) {}

void Timer::start(double duration) {
	this->countdownDuration = duration;
	startTime = AEGetTime(nullptr);
}

double Timer::getRemainingTime() const {
	double currTime = AEGetTime(nullptr);
	double elapsedTime = currTime - startTime;
	return (countdownDuration - elapsedTime) > 0.0 ? (countdownDuration - elapsedTime) : 0.0;
}

bool Timer::completed() const {
	return getRemainingTime() <=0.0;
}









//Stove::Stove(double duration) : cookingTimer(duration) {}

double Stove::remainingCookingTime() const 
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

double Stove::cookIngredients()  
{
	if(AEInputCheckTriggered(AEVK_E) && this->canCook() )
	{
		
		if(this->stoveItems.size() == 2)
		{
			this->cookingTimer.start(3.0);
		}
		else if (this->stoveItems.size() == 3)
		{
			this->cookingTimer.start(4.0);
		}
		else if (this->stoveItems.size() == 4)
		{
			this->cookingTimer.start(5.0);
		}
		else if (this->stoveItems.size() == 5)
		{
			this->cookingTimer.start(6.0);
		}
		else if (this->stoveItems.size() == 6)
		{
			this->cookingTimer.start(7.0);
		}

		this->stoveItems.clear();
		return this->cookingTimer.getRemainingTime();
	}
	else return 0.0;

	//add check for number of ingredients , take in cooking time.
}
Stove Wok;
