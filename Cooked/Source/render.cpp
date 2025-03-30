/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file render.cpp
@author1 Elvis lim sheng jie(elvisshengjie.lim)
- void RenderCollisionBox
- void RenderhighlightIngredientBox
- void mouseDeviceRender
- void RenderMain_menu_background
- void RenderMain_digipenLogo
- Rect class
@author2
@course csd1451s25 Software Engineering Project 2
@section a
*//*______________________________________________________________________*/
// render.cpp
#include "render.hpp"

////////////////////////////helper functions :D////////////////////////////////////////////
AEGfxVertexList* CreateMesh()
{
    AEGfxVertexList* pMesh{};
    AEGfxMeshStart();
    AEGfxTriAdd(
        -0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
    AEGfxTriAdd(
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
    pMesh = AEGfxMeshEnd();
    return pMesh;
}

//input color in HEX code format (RR GG BB AA) pls :>
void DrawRect(Rect rect, unsigned int color, AEGfxVertexList* pMesh)
{
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);

    // Extract each color component using bitwise operations
    float r = ((color >> 24) & 0xFF) / 255.0f; // Red
    float g = ((color >> 16) & 0xFF) / 255.0f; // Green
    float b = ((color >> 8) & 0xFF) / 255.0f;  // Blue
    float a = (color & 0xFF) / 255.0f;         // Alpha

    AEGfxSetColorToMultiply(1.0f,1.0f,1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f,0.0f);

    AEGfxSetColorToMultiply(r, g, b, a);

    AEGfxSetBlendMode(AE_GFX_BM_BLEND);

    AEGfxSetTransparency(a);


    // Transform matrix for positioning the rectangle
    AEMtx33 transform;
    AEMtx33Scale(&transform, rect.width, rect.height);
    AEMtx33TransApply(&transform, &transform, rect.x, rect.y);
    AEGfxSetTransform(transform.m);

    // Draw the rectangle using a built-in mesh or custom vertex data
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
    //printf("Current color: 0x%X\n", color);
}

//draw overload for texture :>
void DrawRect(Rect rect, AEGfxTexture* tex, AEGfxVertexList* pMesh)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

    // Transform matrix for positioning the rectangle
    AEMtx33 transform;
    AEMtx33Scale(&transform, rect.width, rect.height);
    AEMtx33TransApply(&transform, &transform, rect.x, rect.y);
    AEGfxSetTransform(transform.m);

    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(tex, 0, 0);
    AEGfxSetTransform(transform.m);
    
    // Draw the rectangle using a built-in mesh
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
}

s8 FontID = -1;

void InitFont()
{
    FontID = AEGfxCreateFont("./Assets/Cute Dino.otf", 24); 

}

void DestroyFront() {
    AEGfxDestroyFont(FontID);
}
std::vector<Rect> highingredientBoxes = {
    {100.0f, 100.0f,-200.0f ,175.0f},
    {100.0f,100.0f, -49.0f, 175.0f},
    {100.0f, 100.0f, 102.0f, 175.0f },
    { 210.0f, 210.0f,200.0f, -400.0f },
    { 190.0f, 190.0f,200.0f, -350.0f }
    
};
std::vector<Rect> collisionBoxes = {
    {110.0f, 110.0f, -200.0f, 175.0f},
    {110.0f,110.0f, -49.0f, 175.0f},
    { 110.0f, 110.0f, 102.0f, 175.0f },
    { 60.0f, 100.0f, 200.0f, -360.0f }
   
};
std::vector<Rect> objectcollision = {
    { 50.0f, 40.0f, -720.0f , -270.0f }, //Dustbin
    { 200.0f, 100.0f,-50.0f, -200.0f }, // stove
    { 100.0f, 100.0f,-200.0f ,175.0f }, //Ing Box 1
    { 100.0f, 100.0f,-49.0f ,175.0f }, //Ing Box 2
    { 100.0f, 100.0f,102.0f ,175.0f }, //Ing Box 3
    { 330.0f, 200.0f, -350.0f, 340.0f },  // Recipe 1 Collision
    { 330.0f, 200.0f, -0.0f, 340.0f },  // Recipe 2 Collision
    { 330.0f, 200.0f, 350.0f, 340.0f },  // Recipe 3 Collision
    { 20.0f, 70.0f, 200.0f, -350.0f } //mouse device
};

std::vector<Rect> recipeBoxes = {
    { 350.0f, 120.0f, -350.0f, 340.0f },  // Recipe 1 (Wider & Higher)
    { 350.0f, 120.0f,   -0.0f, 340.0f },  // Recipe 2 (Centered)
    { 350.0f, 120.0f,  350.0f, 340.0f }   // Recipe 3 (Right)
};


Rect backgroundRect{ 1600.0f,900.0f,0.0f,0.0f };
Rect dustbinRect{ 100.0f, 100.0f,-720.0f , -300.0f };
Rect ingredientBoxRect{ 100.0f, 100.0f,-200.0f ,175.0f };
Rect backgroundMain_menu{ 1600.0f,900.0f,0.0f,0.0f };
Rect digipen_logo{ 1000, 455 * 1000 / 1525,0.0f,0.0f };
Rect mouseDevice{ 120.0f, 120.0f,200.0f, -350.0f };

void Renderbackground(AEGfxVertexList* mesh, AEGfxTexture* tex) {
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEMtx33 background;
    AEMtx33Scale(&background, backgroundRect.width, backgroundRect.height);
    AEMtx33TransApply(&background, &background, backgroundRect.x, backgroundRect.y);
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

    DrawRect(dustbinRect, tex, mesh);
}
void RenderCollisionBox(AEGfxVertexList* mesh, const Rect& box)
{
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
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
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);

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
void RenderIngredientbox(AEGfxVertexList* mesh, AEGfxTexture* tex) {
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    for (int i = 0; i < 3; i++) {
        AEMtx33 ingredientboxTransform;
        AEMtx33Scale(&ingredientboxTransform, ingredientBoxRect.width, ingredientBoxRect.height);
        AEMtx33TransApply(&ingredientboxTransform, &ingredientboxTransform, ingredientBoxRect.x + 151.0f * i, ingredientBoxRect.y);
        AEGfxSetTransform(ingredientboxTransform.m);
        AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
        AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        AEGfxSetTransparency(1.0f);
        AEGfxTextureSet(tex, 0, 0);
        AEGfxSetTransform(ingredientboxTransform.m);
        AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
    }
}

// draw repellent
void mouseDeviceRender(AEGfxVertexList* mesh, AEGfxTexture* tex)
{
    DrawRect(mouseDevice, tex, mesh);
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

        // Compute position & size for drawing
        float posX = ingredientBoxRect.x + 151.0f * i;
        float posY = ingredientBoxRect.y + 35.0f; // slight vertical offset.
        float ingW = ingredientBoxRect.width - 40.0f;
        float ingH = ingredientBoxRect.height - 40.0f;

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
            
            break;
        case BEEF:
            AEGfxTextureSet(beefTex, 0, 0);
            
            break;
        case CHEESE:
            AEGfxTextureSet(cheeseTex, 0, 0);
            
            break;
        case EGG:
            AEGfxTextureSet(eggTex, 0, 0);
            
            break;
        case RICE:
            AEGfxTextureSet(riceTex, 0, 0);
           
            break;
        case POTATO:
            AEGfxTextureSet(potatoTex, 0, 0);
            
            break;
        default:
            continue; // Skip if unknown.
        }

        // Draw the box (a neutral shape, typically a rectangle).
        AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
    }
}



// Function to Render Stove
void RenderStove(AEGfxVertexList* mesh, Stove& stove, player& Player, const  QTE& qteGauge,
    AEGfxTexture* stoveTex, AEGfxTexture*stoveDirty , AEGfxTexture* stoveCook) {
        
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE); // Ensure it's using texture mode

    // Transformation matrix setup
    AEMtx33 stoveTransform;
    AEMtx33Scale(&stoveTransform, stove.width, stove.height);
    AEMtx33TransApply(&stoveTransform, &stoveTransform, stove.x, stove.y);
    AEGfxSetTransform(stoveTransform.m);

    // Set default texture
    AEGfxTexture* selectedTexture = stoveTex;

    if (stove.isCooking) {
        selectedTexture = stoveCook;
    }
    else if (stove.isDirty) {
        selectedTexture = stoveDirty;
    }

    
    AEGfxTextureSet(selectedTexture, 0, 0); // Ensure texture is properly set

    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);

    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

    // Debugging: If the texture still doesn't s
    // 
    // , print an error
    if (!selectedTexture) {
        std::cerr << "Error: Stove texture is NULL!" << std::endl;
    }


    if (!stove.isCooking && stove.canCook(Player) && !qteGauge.isActive ) {
        AEGfxPrint(FontID, "Press Q to Cook!", -0.6f, -0.1f, 1.2f, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    if (stove.isCooking) {
        std::string timerText = "Cooking: " + stove.getCookingRecipeName() +
            " (" + std::to_string((int)stove.remainingCookingTime()) + "s)";
        AEGfxPrint(FontID, timerText.c_str(), -0.4f, -0.1f, 1.2f, 0.0f, 0.0f, 0.0f, 1.0f);        
    }
    if (stove.isDirty && !stove.isCleaning) {
        AEGfxPrint(FontID, "Stove is dirty! Press C to clean", -0.6f, -0.1f, 1.2f, 0.0f, 0.0f, 0.0f, 1.0f);
    }
    if (stove.isDirty && stove.isCleaning) {
        AEGfxPrint(FontID, "Cleaning Stove!", -0.6f, -0.1f, 1.2f, 0.0f, 0.0f, 0.0f, 1.0f);
    }


}
//Ingredients :
//chicken, rice, egg, cheese, potato, beef
void renderStoveIngredient(AEGfxVertexList* mesh, AEGfxTexture* chickenTex, AEGfxTexture* eggTex , AEGfxTexture* cheeseTex , AEGfxTexture* riceTex, AEGfxTexture* beefTex, AEGfxTexture* potatoTex, Stove& stove)
{
    std::vector<Ingredients> stoveIngredients {stove.getStoveItems()}; //list of ingredients in stove
    if (stoveIngredients.size() == 0) return; //if nothing in stove

    float offsety{ 15.0f };
    float offsetx{ 7.5f };
    float offsetHeight{ 0.47f };
    float offsetWidth{ 0.25f };
    Rect rec{ stove.width * offsetWidth, stove.height * offsetHeight, stove.x-stove.width/3 - offsetx, stove.y + offsety };
    float gap{ 30.0f };
    
    for (size_t i = 0; i < stoveIngredients.size(); ++i) {
        AEGfxTexture* selectedTexture{ nullptr };
        if (stoveIngredients[i] == Ingredients::CHICKEN)
        {
			selectedTexture = chickenTex;
        }
        else if (stoveIngredients[i] == Ingredients::EGG)
        {
            selectedTexture = eggTex;
        }
        else  if (stoveIngredients[i] == Ingredients::CHEESE)
        {
			selectedTexture = cheeseTex;
        }
		else  if (stoveIngredients[i] == Ingredients::RICE)
        {
			selectedTexture = riceTex;
        }
        else if (stoveIngredients[i] == Ingredients::BEEF)
        {
			selectedTexture = beefTex;
        }
        else if (stoveIngredients[i] == Ingredients::POTATO)
        {
			selectedTexture = potatoTex;
        }
        if (i != 0) {
            rec.x += gap;
        }
        DrawRect(rec, selectedTexture, mesh);
    }
}
int maxChar{ 16 };

void RenderRecipeBox(AEGfxVertexList* mesh, AEGfxTexture* tex, const Recipe& recipe, float x, float y,
    AEGfxTexture* chickenTex, AEGfxTexture* beefTex, AEGfxTexture* cheeseTex,
    AEGfxTexture* eggTex, AEGfxTexture* riceTex, AEGfxTexture* potatoTex)
{

    Rect recipeBox{ 330.0f, 200.0f, x, y };
    DrawRect(recipeBox, tex, mesh);

    if (FontID < 0) return;

    float textX = (x - 110.0f) / 800.0f;
    float nameY = (y + 30.0f) / 450.0f;

    float nameScale = 0.85f;

    std::string nameLine1 = recipe.Name;
    std::string nameLine2 = "";

    if (recipe.Name.length() > maxChar) { // If too long, break into two lines
        size_t spacePos = recipe.Name.find(' ', 12);
        if (spacePos != std::string::npos) {
            nameLine1 = recipe.Name.substr(0, spacePos);
            nameLine2 = recipe.Name.substr(spacePos + 1);
        }
    }
    // Print Name (Left-aligned)
    float textOffset{ 0.05f };
   
    AEGfxPrint(FontID, nameLine1.c_str(), textX, nameY, nameScale, 0.0f, 0.0f, 0.0f, 1.0f);
    if (!nameLine2.empty()) {
        AEGfxPrint(FontID, nameLine2.c_str(), textX, nameY - textOffset, nameScale, 0.0f, 0.0f, 0.0f, 1.0f);
    }
    // Draw ingredient icons instead of text
    float iconSize = 60.0f;
    float iconSpacing = 50.0f;
    float iconStartY = y - 25.0f;
    float iconXLeft = x - 120.0f;

    
    for (size_t i = 0; i < recipe.Ingredients.size(); ++i)
    {

        AEGfxTexture* ingTex = nullptr;

        if (recipe.Ingredients[i] == Ingredients::CHICKEN) ingTex = chickenTex;
        else if (recipe.Ingredients[i] == Ingredients::BEEF) ingTex = beefTex;
        else if (recipe.Ingredients[i] == Ingredients::CHEESE) ingTex = cheeseTex;
        else if (recipe.Ingredients[i] == Ingredients::EGG) ingTex = eggTex;
        else if (recipe.Ingredients[i] == Ingredients::RICE) ingTex = riceTex;
        else if (recipe.Ingredients[i] == Ingredients::POTATO) ingTex = potatoTex;
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        if (ingTex) {
            AEMtx33 transform;
            AEMtx33Scale(&transform, iconSize, iconSize);
            AEMtx33TransApply(&transform, &transform, iconXLeft + iconSpacing * i, iconStartY);
            AEGfxSetTransform(transform.m);
            AEGfxTextureSet(ingTex, 0.0f, 0.0f);
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            AEGfxSetTransparency(1.0f);
            AEGfxSetBlendMode(AE_GFX_BM_BLEND);
            AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
        }
    }
}

void RenderActiveRecipes(AEGfxVertexList* mesh, AEGfxTexture* tex, const RecipeSystem& recipeSystem,
    AEGfxTexture* chickenTex, AEGfxTexture* beefTex, AEGfxTexture* cheeseTex,
    AEGfxTexture* eggTex, AEGfxTexture* riceTex, AEGfxTexture* potatoTex)
{
    
    const std::vector<Recipe>& activeRecipes = recipeSystem.getActiveRecipes();

    for (size_t i = 0; i < activeRecipes.size(); i++)
    {
        if (i >= recipeBoxes.size()) break; // Prevent overflow
        RenderRecipeBox(mesh, tex, activeRecipes[i],
            recipeBoxes[i].x, recipeBoxes[i].y,
            chickenTex, beefTex, cheeseTex, eggTex, riceTex, potatoTex);       
         std::string remainTime = std::to_string(static_cast<int>(activeRecipes[i].recipeTimer.getRemainingTime()));
        AEGfxPrint(FontID, remainTime.c_str(), -0.3f + i * 0.45f , 0.58f, 1.0, 0.0f, 0.0f, 0.0f, 1.0f); // Blue text
    }
}


void RenderMain_menu_background(AEGfxVertexList* mesh, AEGfxTexture* tex)
{
    AEMtx33 background_main_menu;
    AEMtx33Scale(&background_main_menu, backgroundMain_menu.width, backgroundMain_menu.height);
    AEMtx33TransApply(&background_main_menu, &background_main_menu, backgroundMain_menu.x, backgroundMain_menu.y);
    AEGfxSetTransform(background_main_menu.m);

    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(tex, 0, 0);
    AEGfxSetTransform(background_main_menu.m);
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}

void RenderMain_digipenLogo(AEGfxVertexList* mesh, AEGfxTexture* tex)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEMtx33 digipen_logo1;
    AEMtx33Scale(&digipen_logo1, digipen_logo.width, digipen_logo.height);
    AEMtx33TransApply(&digipen_logo1, &digipen_logo1, digipen_logo.x, digipen_logo.y);
    AEGfxSetTransform(digipen_logo1.m);

    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);
    AEGfxTextureSet(tex, 0, 0);
    AEGfxSetTransform(digipen_logo1.m);
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
}


void RenderQTEGauge(AEGfxVertexList* mesh, const QTE& qteGauge , AEGfxTexture* barTex, AEGfxTexture* sliderTex, AEGfxTexture* targetTex) {
    if (!qteGauge.isActive) { return; }
    else {
        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        qteGauge.render(mesh , barTex , sliderTex , targetTex);
        AEGfxPrint(FontID, "Press R!", -0.1f, 0.1f, 1.2f, 0.0f, 0.0f, 0.0f, 1.0f);
    }
}


void displayScore(int Score)
{
    std::string scoreStr = std::to_string(Score);
    AEGfxPrint(FontID, scoreStr.c_str(), 0.8f, 0.6f, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}
void displayTimer(double gTimer)
{
    std::string str = std::to_string(static_cast<int>(gTimer));
    AEGfxPrint(FontID, str.c_str(), 0.7f, -0.8f, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}
