// render.hpp
#pragma once

#include <AEEngine.h> // Include necessary headers first
#include <vector>

// Define Rect class before any function declarations
class Rect {
public:
    float width{};
    float height{};
    float x{};
    float y{};

    

};


// ... Other boxes ...

// Forward declare your rendering functions

// Function declarations using Rect
void Renderchicken(AEGfxVertexList* mesh, AEGfxTexture* tex);
void Renderbeef(AEGfxVertexList* mesh, AEGfxTexture* tex);
void Rendercheese(AEGfxVertexList* mesh, AEGfxTexture* tex);
void Renderrice(AEGfxVertexList* mesh, AEGfxTexture* tex);
void Renderpotato(AEGfxVertexList* mesh, AEGfxTexture* tex);
void Renderegg(AEGfxVertexList* mesh, AEGfxTexture* tex);
void Renderbackground(AEGfxVertexList* mesh, AEGfxTexture* tex);
void RenderDustbin(AEGfxVertexList* mesh, AEGfxTexture* tex);
void RenderIngredientbox(AEGfxVertexList* mesh);
void RenderStove(AEGfxVertexList* mesh);
void RenderCollisionBox(AEGfxVertexList* mesh, const Rect& box);
void RenderhighlightIngredientBox(AEGfxVertexList* mesh, const Rect& highlightBox);
//void RenderIngredientsOnBoxes(AEGfxVertexList* mesh);
void RenderIngredientsOnBoxes(
    AEGfxVertexList* mesh,
    AEGfxTexture* chickenTex,
    AEGfxTexture* beefTex,
    AEGfxTexture* cheeseTex,
    AEGfxTexture* eggTex,
    AEGfxTexture* riceTex,
    AEGfxTexture* potatoTex);

// Extern declarations for global variables
extern Rect background1;
extern Rect dustbin1;
extern Rect ingredient1_box;
extern Rect stove1;
extern std::vector<Rect> highingredientBoxes;
extern std::vector<Rect> collisionBoxes;
extern std::vector<Rect> objectcollision;

