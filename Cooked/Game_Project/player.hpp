#pragma once
#include <crtdbg.h>		// To check for memory leaks
#include <math.h> 
#include <AEEngine.h> // Replace with the actual header for your graphics framework
#include "Ingredients.hpp"
#include "collison.hpp"
#include <assert.h>
#include <iostream>
#include <math.h>


class player
{
public:
	void playerdraw(AEGfxVertexList* mesh, AEGfxVertexList* mesh2) const;
	void playerMove(float speed);
	bool playerCheckCollison(float x1, float y1, float width1, float height1)const;
	void playerCheckCollisonobject(float x1, float y1, float width1, float height1);
	void ClampToScreen();
	void playerThrow();
	void playerPickUp(Ingredients& boxIngredient);
	void playerDrop(Stove& stove);
	void playerUpdate(Stove& stove, RecipeSystem& recipeSystem, QTE& QTE_Gauge);
	void playerDash();
private:
	float x{};
	float y{};
	float width{ 50 };
	float height{ 50 };
	float normalize_speed{};
	float dt{};

	// dash
	float dy{}, dx{}, angle{}, normdy{}, normdx{};
	float mangnituded{};
	
	float dashspeed{ 1000.0f };
	float dashCooldown{0.5f};
	float dashDuration{0.2f};
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

	//animation
	float frameTime = 0.1f;  // Time per frame
	float frameTimer = 0.0f; // Tracks frame timing
	int currentFrame = 0;    // Current animation frame
	const int totalFrames = 4; // Number of frames in sprite sheet
	bool isMoving = false;   // Flag for animation control

public:
	void playerdraw(AEGfxVertexList* mesh, AEGfxTexture* texture) const;
	void updateAnimation(float dt);

	Timer cooldown;
	Timer cooldown2;

};

extern player players1;

//hello