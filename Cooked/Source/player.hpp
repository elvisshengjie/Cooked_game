#pragma once
#include <crtdbg.h> // To check for memory leaks
#include <math.h> 
#include <AEEngine.h> // Replace with the actual header for your graphics framework

enum Ingredients{
	EMPTY = 0,
	CHICKEN,
	RICE,
	EGG,
	CHEESE,	
	POTATO,
	BEEF
};

class player
{
private:
	float x{ 0 };
	float y{ 0 };
	static constexpr float width = 50;
	static constexpr float height = 50;
	int Hand = EMPTY;

public:
	void playerdraw(AEGfxVertexList* mesh);
	void playerMove(float speed);
	bool playerCheckCollison(float x1, float y1, float width1, float height1);
	void playerThrow();
	void ClampToScreen();
	void playerPickUp(bool& isHolding, Ingredients& heldItem, const Ingredients& nearbyItem);
};

extern player players1;