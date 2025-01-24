// render.cpp
#include "render.hpp"
#include <assert.h>
#include <crtdbg.h> // To check for memory leaks
#include <math.h> 
#include <AEEngine.h> // Replace with the actual header for your graphics framework
// Function to Render Dustbin with Texture

Rect background1{ 1600.0f,900.0f,0.0f,0.0f };
Rect dustbin1{ 250.0f, 300.0f,-700.0 , -300.0f };
Rect ingredient1_box{ 150.0f, 150.0f,-200.0f ,175.0f };
Rect stove1{ 300.0f, 200.0f,-50.0f, -200.0f };

void Renderbackground(AEGfxVertexList* mesh, AEGfxTexture* tex) {
    AEMtx33 background;
    AEMtx33Scale(&background, background1.x, background1.y);
    AEMtx33TransApply(&background, &background, background1.width, background1.height);
    AEGfxSetTransform(background.m);
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
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
    AEMtx33Scale(&dustbin, dustbin1.x, dustbin1.y);
    AEMtx33TransApply(&dustbin, &dustbin, dustbin1.width, dustbin1.height);
    AEGfxSetTransform(dustbin.m);
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(tex, 0, 0);
    AEGfxSetTransform(dustbin.m);
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

// Function to Render Three Circles with White Boundaries
void RenderIngredientbox(AEGfxVertexList* mesh) {
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    for (int i = 0; i < 3; i++) {
        AEMtx33 ingredientboxTransform;
        AEMtx33Scale(&ingredientboxTransform, ingredient1_box.x, ingredient1_box.y);
        AEMtx33TransApply(&ingredientboxTransform, &ingredientboxTransform, ingredient1_box.width + 151.0f * i, ingredient1_box.height);
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
    AEMtx33Scale(&stoveTransform, stove1.x, stove1.y);
    AEMtx33TransApply(&stoveTransform, &stoveTransform, stove1.width, stove1.height);
    AEGfxSetTransform(stoveTransform.m);
    AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetBlendColor(1.0f, 0.0f, 0.0f, 1.0f);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}


