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
    GAME,
    PAUSE_MENU,
    WIN_SCREEN,
    LOSE_SCREEN
};


// CoreEngine class
class CoreEngine
{
    bool gGameRunning = true;
    GameState currentState = GameState::MAIN_MENU;

    // Meshes
    AEGfxVertexList* pMesh = nullptr;          // Generic mesh (background, dustbin, etc.)
    AEGfxVertexList* IngredientMesh = nullptr; // Generic mesh for ingredients
    AEGfxVertexList* pStoveMesh = nullptr; // Generic mesh for Stove

    // Textures
    AEGfxTexture* bTex = nullptr; // Background/floor
    AEGfxTexture* dTex = nullptr; // Dustbin
    AEGfxTexture* chickenTex = nullptr;
    AEGfxTexture* beefTex = nullptr;
    AEGfxTexture* cheeseTex = nullptr;
    AEGfxTexture* eggTex = nullptr;
    AEGfxTexture* riceTex = nullptr;
    AEGfxTexture* potatoTex = nullptr;
    AEGfxTexture* backgroundTex{ nullptr };

    // Systems
    RecipeSystem recipeSystem;
    MainMenu     mainMenu;

    QTE          qteGauge;
    Stove        Wok;
    WinScreen    winScreen;

    Timer gTimer;

public:
    void Init();
    void Update();
    void Exit();
};

// ------------------------------------------------------------
// CoreEngine::Init
void CoreEngine::Init()
{


    // Changing the window title
    AESysSetWindowTitle("Cooked!");

    // AESysReset() re-initializes various engine systems
    AESysReset();

    // Seed the random generator once
    srand(static_cast<unsigned>(time(nullptr)));

    // Initialize the main menu
    mainMenu.Init();
    winScreen.Init();

    // Start the timer
    gTimer.start(300);

    // Initialize fonts (used for both the menu and the game)
    InitFont();

    // Initialize random box ingredients
    for (int i = 0; i < 3; ++i)
    {
        g_currentBoxIngredients[i] = GetRandomIngredient();
    }

    // 1. Create a mesh (pMesh) for generic rectangles
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

    AEGfxMeshStart();
    AEGfxTriAdd(
        -0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,
        0.5f, -0.5f, 0xFF00FF00, 1.0f, 1.0f,
        -0.5f, 0.5f, 0xFF0000FF, 0.0f, 0.0f);
    AEGfxTriAdd(
        0.5f, -0.5f, 0xFF00FF00, 1.0f, 1.0f,
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
        -0.5f, 0.5f, 0xFF0000FF, 0.0f, 0.0f);
    pStoveMesh = AEGfxMeshEnd();

    // 2. Load textures
    bTex = AEGfxTextureLoad("Assets/floor.png");
    dTex = AEGfxTextureLoad("Assets/dustbin.png");
    chickenTex = AEGfxTextureLoad("Assets/chicken.png");
    beefTex = AEGfxTextureLoad("Assets/beef.png");
    cheeseTex = AEGfxTextureLoad("Assets/cheese.png");
    eggTex = AEGfxTextureLoad("Assets/egg.png");
    riceTex = AEGfxTextureLoad("Assets/rice.png");
    potatoTex = AEGfxTextureLoad("Assets/potato.png");
    backgroundTex = AEGfxTextureLoad("Assets/cafe.jpg");

    // 3. Create a mesh (IngredientMesh) for ingredient rectangles
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

        // Global exit conditions (Esc key or window closed)
        if (AEInputCheckTriggered(AEVK_ESCAPE) || !AESysDoesWindowExist())
            gGameRunning = false;

        // -- SWITCH ON CURRENT STATE --
        switch (currentState)
        {
            // ------------------------------
            // MAIN MENU
            // ------------------------------
        case GameState::MAIN_MENU:
        {
            // Update & render Main Menu
            mainMenu.Update();

            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            mainMenu.Render(pMesh);

            // Check menu selection
            if (mainMenu.IsStartGameSelected())
            {
                currentState = GameState::GAME;
            }
            else if (mainMenu.IsQuitSelected())
            {
                gGameRunning = false;
            }
        }
        break;

        case GameState::WIN_SCREEN:
        {
            // Update & render Main Menu
            int check = winScreen.Update();

            // Check menu selection
            if (check == 1)
            {
                currentState = GameState::GAME;
            }
            else if (check == 2)
            {
                currentState = GameState::MAIN_MENU;
            }
            else if (check == 3)
            {
                gGameRunning = false;
            }

            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            winScreen.Render(pMesh, backgroundTex);
        }
        break;

        // ------------------------------
        // GAME
        // ------------------------------
        case GameState::GAME:
        {
            // 1. Update Player & Collisions
            players1.playerMove(6.0);
            players1.ClampToScreen();

            for (size_t i = 0; i < objectcollision.size(); i++)
            {
                const Rect& object = objectcollision[i];
                players1.playerCheckCollisonobject(object.x, object.y, object.width, object.height);
            }

            // 2. Render the game world
            // Background / Floor
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            Renderbackground(pMesh, bTex);

            // Dustbin
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            RenderDustbin(pMesh, dTex);

            // Player update logic (picking up, dropping, etc.)
            players1.playerUpdate(Wok, recipeSystem, qteGauge);

            // Stove / Wok logic (cooking)
            Wok.update(recipeSystem);

            // Ingredient boxes (3 boxes at top?), Active recipes, etc.
            AEGfxSetRenderMode(AE_GFX_RM_COLOR);
            RenderIngredientbox(pMesh);
            RenderActiveRecipes(pMesh, recipeSystem);

            // Render Stove & Player
            AEGfxSetRenderMode(AE_GFX_RM_COLOR);
            RenderStove(pStoveMesh, Wok, players1,qteGauge);
            players1.playerdraw(pMesh, IngredientMesh);
            RenderQTEGauge(pMesh, qteGauge);

            // Collision boxes for ingredients or special objects
            for (size_t i = 0; i < collisionBoxes.size(); i++)
            {
                const Rect& collBox = collisionBoxes[i];
                const Rect& visualBox = highingredientBoxes[i];

                // If player is colliding with ingredient box
                if (players1.playerCheckCollison(collBox.x, collBox.y, collBox.width, collBox.height))
                {
                    // Render highlight
                    RenderhighlightIngredientBox(pMesh, visualBox);
                    // Handle pickup
                    players1.playerPickUp(g_currentBoxIngredients[i]);
                }

                // Drop logic (stove or dustbin, etc.)
                if (players1.playerCheckCollison(Wok.getX(), Wok.getY(), Wok.getW(), Wok.getH()) ||
                    players1.playerCheckCollison(objectcollision[0].x, objectcollision[0].y,
                        objectcollision[0].width, objectcollision[0].height))
                {
                    players1.playerDrop(Wok);
                }
            }

            // Render ingredients on the boxes
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            RenderIngredientsOnBoxes(pMesh,
                chickenTex, beefTex, cheeseTex,
                eggTex, riceTex, potatoTex);

            // Show score & timer at the top
            displayScore(score);
            displayTimer(gTimer.getRemainingTime());

            if (score > 30)
            {
                currentState = GameState::WIN_SCREEN;
            }
        }
        break;
        } // End of switch

        // --------------------------------
        AESysFrameEnd(); // End the frame
    }
}

// ------------------------------------------------------------
// CoreEngine::Exit
void CoreEngine::Exit()
{
    // Cleanup main menu
    mainMenu.Cleanup();

    // Free memory
    if (pMesh)            AEGfxMeshFree(pMesh);
    if (IngredientMesh)   AEGfxMeshFree(IngredientMesh);
    if (pStoveMesh)   AEGfxMeshFree(pStoveMesh);

    if (bTex)             AEGfxTextureUnload(bTex);
    if (dTex)             AEGfxTextureUnload(dTex);
    if (chickenTex)       AEGfxTextureUnload(chickenTex);
    if (beefTex)          AEGfxTextureUnload(beefTex);
    if (cheeseTex)        AEGfxTextureUnload(cheeseTex);
    if (eggTex)           AEGfxTextureUnload(eggTex);
    if (riceTex)          AEGfxTextureUnload(riceTex);
    if (potatoTex)        AEGfxTextureUnload(potatoTex);

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

    // Initialize the engine
    AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, false, NULL);

    // Create and run our CoreEngine
    CoreEngine ce;
    ce.Init();
    ce.Update();
    ce.Exit();

    return 0;
}
