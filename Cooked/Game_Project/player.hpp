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
		float width = 50;
		float height = 50;
		Ingredients Hand = EMPTY;
		

	public:
		void playerdraw(AEGfxVertexList* mesh, AEGfxVertexList* mesh2)const;
		void playerMove(float speed);
		bool playerCheckCollison(float x1, float y1, float width1, float height1)const;
		void playerCheckCollisonobject(float x1, float y1, float width1, float height1);
		void ClampToScreen();
		void playerThrow();
		void playerPickUp(Ingredients& boxIngredient);
		

};

extern player players1;