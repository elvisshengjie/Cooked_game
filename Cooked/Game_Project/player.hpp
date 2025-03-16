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
	void playerInit();
	void playerdraw(AEGfxVertexList* mesh, AEGfxVertexList* mesh2, std::vector<AEGfxTexture*> idle, std::vector<AEGfxTexture*> up, std::vector<AEGfxTexture*> down, std::vector<AEGfxTexture*> left, std::vector<AEGfxTexture*> right ,AEGfxTexture* chickenTex, AEGfxTexture* beefTex, AEGfxTexture* riceTex, AEGfxTexture* eggTex, AEGfxTexture* cheeseTex, AEGfxTexture* potatoTex) ;
	void playerMove(float speed);
	bool playerCheckCollison(float x1, float y1, float width1, float height1)const;
	void playerCheckCollisonobject(float x1, float y1, float width1, float height1);
	void ClampToScreen();
	void playerThrow();
	void playerPickUp(Ingredients& boxIngredient);
	void playerDrop(Stove& stove);
	void playerUpdate(Stove& stove, RecipeSystem& recipeSystem, QTE& QTE_Gauge);
	void playerDash();

	int spriteDirection{}; // 0- idle , 1 - up , 2- down , 3 - left , 4 - right 
	int currentFrame{};
	bool isMoving = false;
	float frameTimer = 0.0f;
	float idleTime = 0.0f;

private:
	float x{};
	float y{};
	float width{ 80 };
	float height{ 80 };
	float normalize_speed{};
	float dt{};

	// dash
	float dy{}, dx{}, angle{}, normdy{}, normdx{};
	float mangnituded{};
	
	float dashspeed{ 1000.0f };
	float dashCooldown{0.3f};
	float dashDuration{0.2f};
	int	  rawX{};
	int   rawY{};
	float mouseX{};
	float mouseY{};
	bool  isDashing{ false };
	float DirectX{};
	float DirectY{};
	float DirectionX{};
	float DirectionY{};
	float Magnitude{};
	int  dashCounter{ 1 };
	Ingredients Hand = EMPTY;


public:

	Timer cooldown;
	Timer cooldown2;

};

//void RenderAnimatedSprite(AEGfxVertexList* mesh, AEGfxTexture* texture, float frameWidth, float frameHeight, int frameIndex, int totalFrames);

extern player players1;

//hello