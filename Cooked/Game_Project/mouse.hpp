#pragma once
#include <crtdbg.h>		// To check for memory leaks
#include <math.h> 
#include <AEEngine.h> // Replace with the actual header for your graphics framework
#include "Ingredients.hpp"
#include "collison.hpp"
#include <assert.h>
#include <iostream>
#include <math.h>
#include "mouse.hpp"


class mouse
{
public:
	void mousedraw(AEGfxVertexList* mesh, AEGfxVertexList* mesh2)const;
	void mouseMove(float speed);
	bool mouseCheckCollison(float x1, float y1, float width1, float height1)const;
	void mouseCheckCollisonobject(float x1, float y1, float width1, float height1);
	void ClampToScreen();
	//void playerThrow();
	void mouseEating(Ingredients& boxIngredient);
	//void playerDrop(Stove& stove);
	//void playerUpdate(Stove& stove, RecipeSystem& recipeSystem, QTE& QTE_Gauge);
	//void playerDash();
private:
	float x{};
	float y{};
	float width{ 50 };
	float height{ 50 };
	float normalize_speed{};
	float dt{};
	// dash

	float dashspeed{ 700 };
	float dashCooldown{ 0.5 };
	float dashDuration{ 0.2 };
	int rawX{};
	int rawY{};
	float mouseX{};
	float mouseY{};
	bool isDashing{ false };
	float DirectX{};
	float DirectY{};
	float DirectionX{};
	float DirectionY{};
	float Magnitude{};
	int dashCounter{ 1 };
	Ingredients Hand = EMPTY;

	Timer cooldown;
	Timer cooldown2;

};

extern mouse mouse1;

//hello