// render.cpp
#include "render.hpp"
#include <assert.h>
#include <crtdbg.h> // To check for memory leaks
#include <math.h> 
#include <AEEngine.h> // Replace with the actual header for your graphics framework
// Function to Render Dustbin with Texture

Rect background1{ 1600.0f,900.0f,0.0f,0.0f };
Rect dustbin1{ 150.0f, 200.0f,-700.0f , -300.0f };
Rect ingredient1_box{ 80.0f, 80.0f,-200.0f ,175.0f };
Rect stove1{ 200.0f, 100.0f,-50.0f, -200.0f };

Rect collison_ingredient_box1{ 150.0f,210.0f, -235.0f, 175.0f };
Rect highlight_ingredient_box1{ 80.0f, 80.0f,-200.0f ,175.0f };

void Renderbackground(AEGfxVertexList* mesh, AEGfxTexture* tex) {
    AEMtx33 background;
    AEMtx33Scale(&background, background1.width, background1.height);
    AEMtx33TransApply(&background, &background, background1.x, background1.y);
    AEGfxSetTransform(background.m);
    
    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(tex, 0, 0);
    AEGfxSetTransform(background.m);
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void RenderDustbin(AEGfxVertexList * mesh, AEGfxTexture * tex) {
    AEMtx33 dustbin;
    AEMtx33Scale(&dustbin, dustbin1.width, dustbin1.height);
    AEMtx33TransApply(&dustbin, &dustbin, dustbin1.x, dustbin1.y);
    AEGfxSetTransform(dustbin.m);
    
    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(tex, 0, 0);
    
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}
void RendercollisonIngredientBox(AEGfxVertexList * mesh){

    AEMtx33 collisonIngBox;
    AEMtx33Scale(&collisonIngBox, collison_ingredient_box1.width, collison_ingredient_box1.height);
    AEMtx33TransApply(&collisonIngBox, &collisonIngBox, collison_ingredient_box1.x, collison_ingredient_box1.y);
    AEGfxSetTransform(collisonIngBox.m);
    AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetBlendColor(1.0f, 0.0f, 0.0f, 1.0f);
    AEGfxSetTransparency(0.5f);
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

}
void RenderhighlightIngredientBox(AEGfxVertexList* mesh)
{
    AEMtx33 highingredientboxTransform;
    AEMtx33Scale(&highingredientboxTransform, highlight_ingredient_box1.width, highlight_ingredient_box1.height);
    AEMtx33TransApply(&highingredientboxTransform, &highingredientboxTransform, highlight_ingredient_box1.x, highlight_ingredient_box1.y);
    AEGfxSetTransform(highingredientboxTransform.m);
    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.2f, 0.2f, 0.2f, 0.2f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetBlendColor(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetTransparency(0.2f);
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

// Function to Render Three Circles with White Boundaries
void RenderIngredientbox(AEGfxVertexList* mesh) {
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    for (int i = 0; i < 3; i++) {
        AEMtx33 ingredientboxTransform;
        AEMtx33Scale(&ingredientboxTransform, ingredient1_box.width, ingredient1_box.height);
        AEMtx33TransApply(&ingredientboxTransform, &ingredientboxTransform, ingredient1_box.x + 151.0f * i, ingredient1_box.y);
        AEGfxSetTransform(ingredientboxTransform.m);
        AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 1.0f);
        AEGfxSetColorToAdd(1.0f, 0.0f + 1.0f * i,0.0f + 1.0f * (i-1), 1.0f);
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        AEGfxSetBlendColor(1.0f, 0.0f + 1.0f * i ,0.0f + 1.0f * (i-1), 1.0f);
        AEGfxSetTransparency(1.0f);
        AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
    }
}


// Function to Render Stove with Red Color
void RenderStove(AEGfxVertexList* mesh) {
    AEMtx33 stoveTransform;
    AEMtx33Scale(&stoveTransform, stove1.width, stove1.height);
    AEMtx33TransApply(&stoveTransform, &stoveTransform, stove1.x, stove1.y);
    AEGfxSetTransform(stoveTransform.m);
    AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetBlendColor(1.0f, 0.0f, 0.0f, 1.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}


