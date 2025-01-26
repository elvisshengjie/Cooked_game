#pragma once
#include <crtdbg.h>		// To check for memory leaks
#include <math.h> 
#include <AEEngine.h> // Replace with the actual header for your graphics framework
#include "Ingredients.hpp"

class player
{
	private:
		float x{ 0 };
		float y{ 0 };
		static constexpr float width = 50;
		static constexpr float height = 50;
	public:
		void playerdraw(AEGfxVertexList* mesh);
		void playerMove(float speed);
		bool playerCheckCollison(float x1, float y1, float width1, float height1);
		void playerPickUp(bool& isHolding, Ingredient& heldItem, const Ingredient& nearbyItem);
};

extern player players1;