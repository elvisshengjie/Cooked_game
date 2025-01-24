#pragma once
// render.hpp


#include <crtdbg.h> // To check for memory leaks
#include <math.h> 
#include <AEEngine.h> // Replace with the actual header for your graphics framework

void Renderbackground(AEGfxVertexList* mesh, AEGfxTexture* tex);
// Renders the dustbin with texture
void RenderDustbin(AEGfxVertexList * mesh, AEGfxTexture* tex);

// Renders three circles with white boundaries
void RenderIngredientbox(AEGfxVertexList* mesh);

// Renders the stove with a red color
void RenderStove(AEGfxVertexList* mesh);
void RendercollisonIngredientBox(AEGfxVertexList* mesh);
void RenderhighlightIngredientBox(AEGfxVertexList* mesh);
class Rect {
	public:
	float width{};
	float height{};
	float x{};
	float y{};


};
extern Rect background1;
extern Rect dusbin1;
extern Rect ingredient1_box;
extern Rect stove1;
extern Rect collison_ingredient_box1;
//variable


