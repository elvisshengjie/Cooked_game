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

// Function declarations using Rect
void Renderbackground(AEGfxVertexList* mesh, AEGfxTexture* tex);
void RenderDustbin(AEGfxVertexList* mesh, AEGfxTexture* tex);
void RenderIngredientbox(AEGfxVertexList* mesh);
void RenderStove(AEGfxVertexList* mesh);
void RenderCollisionBox(AEGfxVertexList* mesh, const Rect& box);
void RenderhighlightIngredientBox(AEGfxVertexList* mesh, const Rect& highlightBox);

// Extern declarations for global variables
extern Rect background1;
extern Rect dustbin1;
extern Rect ingredient1_box;
extern Rect stove1;
extern std::vector<Rect> highingredientBoxes;
extern std::vector<Rect> collisionBoxes;
extern std::vector<Rect> objectcollision;

