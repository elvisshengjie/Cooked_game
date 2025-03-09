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

    //reset color
    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);


    // Transform matrix for positioning the rectangle
    AEMtx33 transform;
    AEMtx33Scale(&transform, rect.width, rect.height);
    AEMtx33TransApply(&transform, &transform, rect.x, rect.y);
    AEGfxSetTransform(transform.m);

    AEGfxSetColorToMultiply(r, g, b, a);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(a);
    AEGfxSetTransform(transform.m);

    // Draw the rectangle using a built-in mesh or custom vertex data
    AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
    printf("Current color: 0x%X\n", color);
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
    assert(FontID >= 0 && "Failed to load font!");
}

void DestroyFront() {
    AEGfxDestroyFont(FontID);
}
std::vector<Rect> highingredientBoxes = {
    {90.0f, 90.0f,-200.0f ,175.0f},
    {90.0f,90.0f, -49.0f, 175.0f},
    {90.0f, 90.0f, 102.0f, 175.0f },
    { 210.0f, 210.0f,200.0f, -400.0f },
    { 190.0f, 190.0f,200.0f, -350.0f }
    
};
std::vector<Rect> collisionBoxes = {
    {100.0f, 100.0f, -200.0f, 175.0f},
    {100.0f,100.0f, -49.0f, 175.0f},
    { 100.0f, 100.0f, 102.0f, 175.0f },
    { 180.0f, 180.0f,200.0f, -350.0f }

   
};
std::vector<Rect> objectcollision = {
    { 150.0f, 200.0f,-750.0f , -300.0f },
    { 200.0f, 100.0f,-50.0f, -200.0f },
    { 80.0f, 80.0f,-200.0f ,175.0f },
    { 80.0f, 80.0f,-49.0f ,175.0f },
    { 80.0f, 80.0f,102.0f ,175.0f },
    { 330.0f, 200.0f, -350.0f, 340.0f },  // Recipe 1 Collision
    { 330.0f, 200.0f,   -0.0f, 340.0f },  // Recipe 2 Collision
    { 330.0f, 200.0f,  350.0f, 340.0f },// Recipe 3 Collision
    { 170.0f, 170.0f,200.0f, -350.0f }
};

std::vector<Rect> recipeBoxes = {
    { 350.0f, 120.0f, -350.0f, 340.0f },  // Recipe 1 (Wider & Higher)
    { 350.0f, 120.0f,   -0.0f, 340.0f },  // Recipe 2 (Centered)
    { 350.0f, 120.0f,  350.0f, 340.0f }   // Recipe 3 (Right)
};


Rect background1{ 1600.0f,900.0f,0.0f,0.0f };
Rect dustbin1{ 150.0f, 200.0f,-720.0f , -300.0f };
Rect ingredient1_box{ 80.0f, 80.0f,-200.0f ,175.0f };
Rect backgroundMain_menu{ 1600.0f,900.0f,0.0f,0.0f };
Rect digipen_logo{ 1000, 455 * 1000 / 1525,0.0f,0.0f };
Rect mouseDevice{ 170.0f, 170.0f,200.0f, -350.0f };

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
        AEMtx33Scale(&ingredientboxTransform, ingredient1_box.width, ingredient1_box.height);
        AEMtx33TransApply(&ingredientboxTransform, &ingredientboxTransform, ingredient1_box.x + 151.0f * i, ingredient1_box.y);
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

void mouseDevicefun(AEGfxVertexList* mesh)
{
    AEMtx33 mousedev;
    AEMtx33Scale(&mousedev, mouseDevice.width, mouseDevice.height);
    AEMtx33TransApply(&mousedev, &mousedev, mouseDevice.x, mouseDevice.y);
    AEGfxSetTransform(mousedev.m);

    // Example color settings
    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 1.0f, 1.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetBlendColor(1.0f, 0.0f, 1.0f, 1.0f);
    AEGfxSetTransparency(1.0f);

    // Draw the mesh for the mouse
    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
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
        float posY = ingredient1_box.y + 15.0f; // slight vertical offset.
        float ingW = ingredient1_box.width + 20.0f;
        float ingH = ingredient1_box.height + 20.0f;

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
            //AEGfxSetColorToMultiply(0.6f, 0.4f, 0.2f, 1.0f);
            
            break;
        default:
            continue; // Skip if unknown.
        }

        // Draw the box (a neutral shape, typically a rectangle).
        AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);
    }
}



// Function to Render Stove with Red Color
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

    if (selectedTexture) {
        AEGfxTextureSet(selectedTexture, 0, 0); // Ensure texture is properly set
    }

    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetTransparency(1.0f);

    AEGfxMeshDraw(mesh, AE_GFX_MDM_TRIANGLES);

    // Debugging: If the texture still doesn't show, print an error
    if (!selectedTexture) {
        std::cerr << "Error: Stove texture is NULL!" << std::endl;
    }


    if (!stove.isCooking && stove.canCook(Player) && !qteGauge.isActive ) {
        AEGfxPrint(FontID, "Press Q to Cook!", -0.6f, -0.1f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    if (stove.isCooking) {
        std::string timerText = "Cooking: " + stove.getCookingRecipeName() +
            " (" + std::to_string((int)stove.remainingCookingTime()) + "s)";
        AEGfxPrint(FontID, timerText.c_str(), -0.4f, -0.1f, 0.7f, 0.0f, 0.0f, 0.0f, 1.0f);        
    }
    if (stove.isDirty && !stove.isCleaning) {
        AEGfxPrint(FontID, "Stove is dirty! Press C to clean", -0.6f, -0.1f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f);
    }
    if (stove.isDirty && stove.isCleaning) {
        AEGfxPrint(FontID, "Cleaning Stove!", -0.6f, -0.1f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f);
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

void RenderMain_digipenLogo(AEGfxVertexList* mesh, AEGfxTexture* tex)
{
  
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


void RenderQTEGauge(AEGfxVertexList* mesh, const QTE& qteGauge) {
    if (!qteGauge.isActive) { return; }
    else {

        qteGauge.render(mesh);
        AEGfxPrint(FontID, "Press R !", -0.1f, -0.2f, 0.8f, 0.0f, 0.0f, 0.0f, 1.0f);
    }
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
