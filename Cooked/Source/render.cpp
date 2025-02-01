// render.cpp
#include "render.hpp"
#include "Ingredients.hpp"
#include <AEGraphics.h>
#include <assert.h>
#include <crtdbg.h> // To check for memory leaks
#include <math.h> 
#include <vector>
#include <AEEngine.h> // Replace with the actual header for your graphics framework
// Function to Render Dustbin with Texture

std::vector<Rect> highingredientBoxes = {
    {90.0f, 90.0f,-200.0f ,175.0f},
    {90.0f,90.0f, -49.0f, 175.0f},
    {90.0f, 90.0f, 102.0f, 175.0f }

};
std::vector<Rect> collisionBoxes = {
    {100.0f, 100.0f, -200.0f, 175.0f},
    {100.0f,100.0f, -49.0f, 175.0f},
    { 100.0f, 100.0f, 102.0f, 175.0f }
};
std::vector<Rect> objectcollision = {
    { 150.0f, 200.0f,-750.0f , -300.0f },
    { 200.0f, 100.0f,-50.0f, -200.0f },
    { 80.0f, 80.0f,-200.0f ,175.0f },
    { 80.0f, 80.0f,-49.0f ,175.0f },
    { 80.0f, 80.0f,102.0f ,175.0f }
};
Rect background1{ 1600.0f,900.0f,0.0f,0.0f };
Rect dustbin1{ 150.0f, 200.0f,-720.0f , -300.0f };
Rect ingredient1_box{ 80.0f, 80.0f,-200.0f ,175.0f };
Rect stove1{ 200.0f, 100.0f,-50.0f, -200.0f };



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

void RenderDustbin(AEGfxVertexList* mesh, AEGfxTexture* tex) {
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
void RenderCollisionBox(AEGfxVertexList* mesh, const Rect& box)
{
    AEMtx33 collisionTransform;
    AEMtx33Scale(&collisionTransform, box.width, box.height);
    AEMtx33TransApply(&collisionTransform, &collisionTransform, box.x, box.y);
    AEGfxSetTransform(collisionTransform.m);
    AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetBlendColor(1.0f, 0.0f, 0.0f, 1.0f);
    AEGfxSetTransparency(0.5f);
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}
void RenderhighlightIngredientBox(AEGfxVertexList* mesh, const Rect& highlightBox)
{
    AEMtx33 highingredientboxTransform;
    AEMtx33Scale(&highingredientboxTransform, highlightBox.width, highlightBox.height);
    AEMtx33TransApply(&highingredientboxTransform, &highingredientboxTransform, highlightBox.x, highlightBox.y);
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
        AEGfxSetColorToAdd(1.0f, 0.0f + 1.0f * i, 0.0f + 1.0f * (i - 1), 1.0f);
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        AEGfxSetBlendColor(1.0f, 0.0f + 1.0f * i, 0.0f + 1.0f * (i - 1), 1.0f);
        AEGfxSetTransparency(1.0f);
        AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
    }
}



void RenderIngredientsOnBoxes(
    AEGfxVertexList* mesh,
    AEGfxTexture* chickenTex,
    AEGfxTexture* beefTex,
    AEGfxTexture* cheeseTex,
    AEGfxTexture* eggTex,
    AEGfxTexture* riceTex,
    AEGfxTexture* potatoTex)
{
    // Use texture rendering mode.
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

    // Loop over the 3 boxes.
    for (int i = 0; i < 3; i++)
    {
        // Retrieve which ingredient is in this box.
        Ingredients ing = g_currentBoxIngredients[i];
        if (ing == EMPTY)
            continue; // Skip rendering if no ingredient.

        // Compute position & size for drawing.
        float posX = ingredient1_box.x + 151.0f * i;
        float posY = ingredient1_box.y + 10.0f; // slight vertical offset.
        float ingW = ingredient1_box.width - 20.0f;
        float ingH = ingredient1_box.height - 20.0f;

        // Setup transformation matrix.
        AEMtx33 ingredientTransform;
        AEMtx33Scale(&ingredientTransform, ingW, ingH);
        AEMtx33TransApply(&ingredientTransform, &ingredientTransform, posX, posY);
        AEGfxSetTransform(ingredientTransform.m);

        // Set blend & color to white so that the texture appears as is.
        AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
        AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        AEGfxSetTransparency(1.0f);

        // Select the correct texture (and optionally, a color tint) based on the ingredient.
        switch (ing)
        {
        case CHICKEN:
            AEGfxTextureSet(chickenTex, 0, 0);
            // Optionally, you can tint it:
            AEGfxSetColorToMultiply(1.0f, 0.9f, 0.8f, 1.0f);
            break;
        case BEEF:
            AEGfxTextureSet(beefTex, 0, 0);
            AEGfxSetColorToMultiply(0.5f, 0.1f, 0.1f, 1.0f);
            break;
        case CHEESE:
            AEGfxTextureSet(cheeseTex, 0, 0);
            AEGfxSetColorToMultiply(1.0f, 0.9f, 0.2f, 1.0f);
            break;
        case EGG:
            AEGfxTextureSet(eggTex, 0, 0);
            AEGfxSetColorToMultiply(1.0f, 1.0f, 0.5f, 1.0f);
            break;
        case RICE:
            AEGfxTextureSet(riceTex, 0, 0);
            AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
            break;
        case POTATO:
            AEGfxTextureSet(potatoTex, 0, 0);
            AEGfxSetColorToMultiply(0.6f, 0.4f, 0.2f, 1.0f);
            break;
        default:
            continue; // Skip if unknown.
        }

        // Draw the box (a neutral shape, typically a rectangle).
        AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
    }
}




    // Function to Render Stove with Red Color
    void RenderStove(AEGfxVertexList * mesh) {
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


