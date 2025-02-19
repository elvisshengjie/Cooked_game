#include <iostream>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include <AEGraphics.h>
#include "main_menu.hpp"
#include "render.hpp"
#include "utils.hpp"
#include "collison.hpp"
#include "player.hpp"
#include <math.h>

// ---------------------------------------------------------------------------
// Define your game states
enum class GameState {
    MAIN_MENU,
    GAME
};

// CoreEngine class
class CoreEngine
{
    bool gGameRunning = true;
    GameState currentState = GameState::MAIN_MENU;

    // Meshes
    AEGfxVertexList* pMesh = nullptr;
    AEGfxVertexList* IngredientMesh = nullptr;

    // Textures
    AEGfxTexture* bTex = nullptr;
    AEGfxTexture* dTex = nullptr;
    AEGfxTexture* chickenTex = nullptr;
    AEGfxTexture* beefTex = nullptr;
    AEGfxTexture* cheeseTex = nullptr;
    AEGfxTexture* eggTex = nullptr;
    AEGfxTexture* riceTex = nullptr;
    AEGfxTexture* potatoTex = nullptr;

    // Systems
    RecipeSystem recipeSystem;
    MainMenu mainMenu;

public:
    void Init();
    void Update();
    void Exit();
};

// ------------------------------------------------------------
// CoreEngine::Init
void CoreEngine::Init()
{
    AESysSetWindowTitle("Health Bar Demo");
    AESysReset();

    // Seed the random generator once
    srand(static_cast<unsigned>(time(nullptr)));

  
    mainMenu.Init();

  
    InitFont();

    // Initialize random box ingredients
    for (int i = 0; i < 3; ++i)
    {
        g_currentBoxIngredients[i] = GetRandomIngredient();
    }

    // Create a mesh (pMesh) for generic rectangles
    AEGfxMeshStart();
    AEGfxTriAdd(
        -0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFF00FF00, 1.0f, 1.0f,
        -0.5f, 0.5f, 0xFF0000FF, 0.0f, 0.0f);
    AEGfxTriAdd(
        0.5f, -0.5f, 0xFF00FF00, 1.0f, 1.0f,
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
        -0.5f, 0.5f, 0xFF0000FF, 0.0f, 0.0f);
    pMesh = AEGfxMeshEnd();

    // Load textures for floor, dustbin, ingredients, etc.
    bTex = AEGfxTextureLoad("Assets/floor.png");
    dTex = AEGfxTextureLoad("Assets/dustbin.png");
    chickenTex = AEGfxTextureLoad("Assets/chicken.png");
    beefTex = AEGfxTextureLoad("Assets/beef.png");
    cheeseTex = AEGfxTextureLoad("Assets/cheese.png");
    eggTex = AEGfxTextureLoad("Assets/egg.png");
    riceTex = AEGfxTextureLoad("Assets/rice.png");
    potatoTex = AEGfxTextureLoad("Assets/potato.png");

    // Create a mesh (IngredientMesh) for ingredient rectangles
    AEGfxMeshStart();
    AEGfxTriAdd(
        -0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
    AEGfxTriAdd(
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
    IngredientMesh = AEGfxMeshEnd();
}

// ------------------------------------------------------------
// CoreEngine::Update
void CoreEngine::Update()
{
    while (gGameRunning)
    {
       
        AESysFrameStart();

        // Check global exit conditions (Esc or window closed)
        if (AEInputCheckTriggered(AEVK_ESCAPE) || !AESysDoesWindowExist())
            gGameRunning = false;

        
        switch (currentState)
        {
        case GameState::MAIN_MENU:
            // Update & Render Main Menu
            mainMenu.Update();
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            mainMenu.Render(pMesh);

            // Check menu selection
            if (mainMenu.IsStartGameSelected()) {
                currentState = GameState::GAME;
            }
            else if (mainMenu.IsQuitSelected()) {
                gGameRunning = false;
            }
            break;

        case GameState::GAME:
            // ------------------------------
            // 1. Player & Collisions
            players1.playerMove(6.0);
            players1.ClampToScreen();

            for (size_t i = 0; i < objectcollision.size(); i++) {
                const Rect& object = objectcollision[i];
                players1.playerCheckCollisonobject(object.x, object.y, object.width, object.height);
            }

            // ------------------------------
            // 2. Render the game world
            // Floor
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            Renderbackground(pMesh, bTex);

            // Dustbin
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            RenderDustbin(pMesh, dTex);

            // Player logic
            players1.playerUpdate(Wok, recipeSystem);

            // Stove / Wok logic
            Wok.update(recipeSystem);

            // Ingredient boxes, recipes, etc.
            AEGfxSetRenderMode(AE_GFX_RM_COLOR);
            RenderIngredientbox(pMesh);
            RenderActiveRecipes(pMesh, recipeSystem);

            // Stove & Player
            RenderStove(pMesh, Wok, players1);
            players1.playerdraw(pMesh, IngredientMesh);

            // Collision boxes for ingredients or special objects
            for (size_t i = 0; i < collisionBoxes.size(); i++) {
                const Rect& collBox = collisionBoxes[i];
                const Rect& visualBox = highingredientBoxes[i];

                if (players1.playerCheckCollison(collBox.x, collBox.y, collBox.width, collBox.height)) {
                    // Render highlight
                    RenderhighlightIngredientBox(pMesh, visualBox);
                    // Handle pickup
                    players1.playerPickUp(g_currentBoxIngredients[i]);
                }
                // Drop logic
                if (players1.playerCheckCollison(Wok.getX(), Wok.getY(), Wok.getW(), Wok.getH()) ||
                    players1.playerCheckCollison(objectcollision[0].x, objectcollision[0].y,
                        objectcollision[0].width, objectcollision[0].height))
                {
                    players1.playerDrop(Wok);
                }
            }

            // Render ingredients on boxes
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            RenderIngredientsOnBoxes(pMesh,
                chickenTex, beefTex, cheeseTex,
                eggTex, riceTex, potatoTex);
            break;
        }

        // End the frame
        AESysFrameEnd();
    }
}

// ------------------------------------------------------------
// CoreEngine::Exit
void CoreEngine::Exit()
{
 
    mainMenu.Cleanup();

  
    if (pMesh)           AEGfxMeshFree(pMesh);
    if (IngredientMesh)  AEGfxMeshFree(IngredientMesh);
    if (bTex)            AEGfxTextureUnload(bTex);
    if (dTex)            AEGfxTextureUnload(dTex);

  

    AESysExit();
}

// ------------------------------------------------------------
// WinMain
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, false, NULL);

    
    CoreEngine ce;
    ce.Init();
    ce.Update();
    ce.Exit();
    return 0;
}
