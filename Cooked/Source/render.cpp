// render.cpp
#include "render.hpp"

s8 FontID = -1;

void InitFont()
{
    FontID = AEGfxCreateFont("./Assets/Cute Dino.otf", 24); 
    assert(FontID >= 0 && "Failed to load font!");
}


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
    { 80.0f, 80.0f,102.0f ,175.0f },
    { 330.0f, 200.0f, -350.0f, 340.0f },  // Recipe 1 Collision
    { 330.0f, 200.0f,   -0.0f, 340.0f },  // Recipe 2 Collision
    { 330.0f, 200.0f,  350.0f, 340.0f }   // Recipe 3 Collision
};

std::vector<Rect> recipeBoxes = {
    { 350.0f, 120.0f, -350.0f, 340.0f },  // Recipe 1 (Wider & Higher)
    { 350.0f, 120.0f,   -0.0f, 340.0f },  // Recipe 2 (Centered)
    { 350.0f, 120.0f,  350.0f, 340.0f }   // Recipe 3 (Right)
};


Rect background1{ 1600.0f,900.0f,0.0f,0.0f };
Rect dustbin1{ 150.0f, 200.0f,-720.0f , -300.0f };
Rect ingredient1_box{ 80.0f, 80.0f,-200.0f ,175.0f };
Rect stove1{ 200.0f, 100.0f,-50.0f, -200.0f };
Rect backgroundMain_menu{ 1600.0f,900.0f,0.0f,0.0f };


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
        AEGfxSetColorToAdd(1.0f, 0.0f + 1.0f * i,0.0f + 1.0f * (i-1), 1.0f);
        AEGfxSetBlendMode(AE_GFX_BM_BLEND);
        AEGfxSetBlendColor(1.0f, 0.0f + 1.0f * i ,0.0f + 1.0f * (i-1), 1.0f);
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
void RenderStove(AEGfxVertexList* mesh, Stove& stove, player& Player) {
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

    if (!stove.isCurrentlyCooking() && stove.canCook(Player)) {
        AEGfxPrint(FontID, "Press Q to Cook!", -0.6f, -0.1f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    if (stove.isCurrentlyCooking()) {
        std::string timerText = "Cooking: " + stove.getCookingRecipeName() +
            " (" + std::to_string((int)stove.remainingCookingTime()) + "s)";
        AEGfxPrint(FontID, timerText.c_str(), -0.4f, -0.1f, 0.7f, 0.0f, 0.0f, 0.0f, 1.0f);
    }
}

void RenderRecipeBox(AEGfxVertexList* mesh, const Recipe& recipe, float x, float y)
{

    // Move Boxes Higher
    //y += 50.0f;
    // Render recipe box background
    AEMtx33 recipeTransform;
    AEMtx33Scale(&recipeTransform, 330.0f, 200.0f);
    AEMtx33TransApply(&recipeTransform, &recipeTransform, x, y);
    AEGfxSetTransform(recipeTransform.m);

    AEGfxSetColorToMultiply(0.9f, 0.9f, 0.9f, 1.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

    // Print Recipe Name
    if (FontID < 0) return;

    // Adjust text alignment for wider box
    float textX = (x - 160.0f) / 800.0f;  // Left-align for wider box
    float nameY = (y + 50.0f) / 450.0f;   // Position recipe name higher
    float ingYStart = y / 450.0f; // Ingredients start slightly lower

    float nameScale = 0.85f;  // Slightly larger for better readability
    float ingScale = 0.75f;   // Maintain clarity for ingredients

    // Split long recipe names over two lines
    std::string nameLine1 = recipe.Name;
    std::string nameLine2 = "";

    if (recipe.Name.length() > 16) { // If too long, break into two lines
        size_t spacePos = recipe.Name.find(' ', 12);
        if (spacePos != std::string::npos) {
            nameLine1 = recipe.Name.substr(0, spacePos);
            nameLine2 = recipe.Name.substr(spacePos + 1);
        }
    }

    // Print Name (Left-aligned)
    AEGfxPrint(FontID, nameLine1.c_str(), textX, nameY, nameScale, 0.0f, 0.0f, 0.0f, 1.0f);
    if (!nameLine2.empty()) {
        AEGfxPrint(FontID, nameLine2.c_str(), textX, nameY - 0.05f, nameScale, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    // Handle Ingredients Overflow (Split into two columns, flowing into right half)
    float ingTextY = ingYStart;
    float ingColumnX = textX;  // Start in left half
    size_t midPoint = (recipe.Ingredients.size() + 1) / 2;  // Halfway point for two columns

    for (size_t i = 0; i < recipe.Ingredients.size(); ++i) {
        AEGfxPrint(FontID, recipe.Ingredients[i].c_str(), ingColumnX, ingTextY, ingScale, 0.0f, 0.0f, 1.0f, 1.0f); // Blue text
        ingTextY -= 0.05f;  // **Reduced spacing between ingredients (was 0.07f)**

        // Move to second column if halfway through the ingredient list
        if (i + 1 == midPoint) {
            ingTextY = ingYStart;  // Reset Y for second column
            ingColumnX += 0.20f;  // **Added extra space for clearer separation**
        }
    }
}

void RenderActiveRecipes(AEGfxVertexList* mesh,const RecipeSystem& recipeSystem)
{
    const std::vector<Recipe>& activeRecipes = recipeSystem.getActiveRecipes();

    for (size_t i = 0; i < activeRecipes.size(); i++)
    {
        if (i >= recipeBoxes.size()) break; // Prevent overflow
        RenderRecipeBox(mesh, activeRecipes[i], recipeBoxes[i].x, recipeBoxes[i].y);
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
void displayScore(int score)
{
    std::string scoreStr = std::to_string(score);
    AEGfxPrint(FontID, scoreStr.c_str(), 0.8f, 0.6f, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}
void displayTimer(double gTimer)
{
    std::string str = std::to_string(static_cast<int>(gTimer));
    AEGfxPrint(FontID, str.c_str(), 0.7f, -0.8f, 2.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}