#include <iostream>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include <AEGraphics.h>
#include "main_menu.hpp"
#include "render.hpp"
#include "utils.hpp"
#include "collison.hpp"
#include "player.hpp"
#include "mouse.hpp"
#include <math.h>
#include <vector>

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
    Timer mouseDeviceCooldownTimer{};

    // Meshes
    AEGfxVertexList* pMesh = nullptr;          // Generic mesh (background, dustbin, etc.)
    AEGfxVertexList* IngredientMesh = nullptr; // Generic mesh for ingredients
    AEGfxVertexList* pStoveMesh = nullptr; // Generic mesh for Stove
    AEGfxVertexList* uiMesh = nullptr;     //untextured rect for UI

    // Textures
    AEGfxTexture* bTex = nullptr; // Background/floor
    AEGfxTexture* dTex = nullptr; // Dustbin
    AEGfxTexture* chickenTex = nullptr;
    AEGfxTexture* beefTex = nullptr;
    AEGfxTexture* cheeseTex = nullptr;
    AEGfxTexture* eggTex = nullptr;
    AEGfxTexture* riceTex = nullptr;
    AEGfxTexture* potatoTex = nullptr;
    AEGfxTexture* boxTex = nullptr;
    AEGfxTexture* backgroundTex{ nullptr };
    AEGfxTexture* stoveTex{ nullptr };
    AEGfxTexture* stoveDirtyTex{ nullptr };
    AEGfxTexture* stoveCookTex{ nullptr };
    AEGfxTexture* deviceTex{ nullptr };
    AEGfxTexture* paperTex{ nullptr };
    AEGfxTexture* buttonTex{ nullptr };
    AEGfxTexture* recipeTex{ nullptr };

    std::vector<AEGfxTexture*>playerIdle{nullptr, nullptr, nullptr, nullptr};
    std::vector<AEGfxTexture*>playerWalkUp{ nullptr, nullptr, nullptr, nullptr };
    std::vector<AEGfxTexture*>playerWalkDown{ nullptr, nullptr, nullptr, nullptr };
    std::vector<AEGfxTexture*>playerWalkLeft{ nullptr, nullptr, nullptr, nullptr };
    std::vector<AEGfxTexture*>playerWalkRight{ nullptr, nullptr, nullptr, nullptr };

    std::vector<AEGfxTexture*>mouseUp{ nullptr, nullptr, nullptr, nullptr };
    std::vector<AEGfxTexture*>mouseDown {nullptr, nullptr, nullptr, nullptr };
    std::vector<AEGfxTexture*>mouseLeft{ nullptr, nullptr, nullptr, nullptr };
    std::vector<AEGfxTexture*>mouseRight{ nullptr, nullptr, nullptr, nullptr };

    
    

    // Systems
    RecipeSystem recipeSystem;
   MainMenu     mainMenu;
   PauseMenu    pauseMenu;

    QTE          qteGauge;
    Stove        Wok;
    WinScreen    winScreen;
    WinScreen    loseScreen;

    Timer gTimer{};

public:
    void Init();
    void Update();
    void Exit();

};

// ------------------------------------------------------------
// CoreEngine::Init
void CoreEngine::Init()
{
    currentState = GameState::MAIN_MENU;
    // Changing the window title

    gTimer.start(300);
    AESysSetWindowTitle("Cooked!");

    // AESysReset() re-initializes various engine systems
    AESysReset();

    // Seed the random generator once
    srand(static_cast<unsigned>(time(nullptr)));

    // Initialize the main menu
    mainMenu.Init();
    winScreen.Init();
    loseScreen.Init();
    pauseMenu.Init();

    // Start the timer

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
    uiMesh = CreateMesh();

    // 2. Load textures
   
    bTex = AEGfxTextureLoad("Assets/floor.png");
    dTex = AEGfxTextureLoad("Assets/dustbin.png");
    chickenTex = AEGfxTextureLoad("Assets/chicken.png");
    beefTex = AEGfxTextureLoad("Assets/beef.png");
    cheeseTex = AEGfxTextureLoad("Assets/cheese.png");
    eggTex = AEGfxTextureLoad("Assets/egg.png");
    riceTex = AEGfxTextureLoad("Assets/rice.png");
    potatoTex = AEGfxTextureLoad("Assets/potato.png");
    boxTex = AEGfxTextureLoad("Assets/box.png");
    backgroundTex = AEGfxTextureLoad("Assets/cafe.jpg");
    stoveTex = AEGfxTextureLoad("Assets/Stove.png");
    stoveDirtyTex = AEGfxTextureLoad("Assets/Stovedirty.png");
    stoveCookTex = AEGfxTextureLoad("Assets/StoveCook.png");
    deviceTex = AEGfxTextureLoad("Assets/repellent.png");
    paperTex = AEGfxTextureLoad("Assets/paperUI.png");
    buttonTex = AEGfxTextureLoad("Assets/paperUIButton.png");
    recipeTex = AEGfxTextureLoad("Assets/recipeUI.png");

    mouseUp[0] = AEGfxTextureLoad("Assets/mouse_walk_up-1.png");
    mouseUp[1] = AEGfxTextureLoad("Assets/mouse_walk_up-2.png");
    mouseUp[2] = AEGfxTextureLoad("Assets/mouse_walk_up-3.png");
    mouseUp[3] = AEGfxTextureLoad("Assets/mouse_walk_up-4.png");

    mouseDown[0] = AEGfxTextureLoad("Assets/mouse_walk_down-1.png");
    mouseDown[1] = AEGfxTextureLoad("Assets/mouse_walk_down-2.png");
    mouseDown[2] = AEGfxTextureLoad("Assets/mouse_walk_down-3.png");
    mouseDown[3] = AEGfxTextureLoad("Assets/mouse_walk_down-4.png");

    mouseLeft[0] = AEGfxTextureLoad("Assets/mouse_walk_left-1.png");
    mouseLeft[1] = AEGfxTextureLoad("Assets/mouse_walk_left-2.png");
    mouseLeft[2] = AEGfxTextureLoad("Assets/mouse_walk_left-3.png");
    mouseLeft[3] = AEGfxTextureLoad("Assets/mouse_walk_left-4.png");

    mouseRight[0] = AEGfxTextureLoad("Assets/mouse_walk_right-1.png");
    mouseRight[1] = AEGfxTextureLoad("Assets/mouse_walk_right-2.png");
    mouseRight[2] = AEGfxTextureLoad("Assets/mouse_walk_right-3.png");
    mouseRight[3] = AEGfxTextureLoad("Assets/mouse_walk_right-4.png");


    playerIdle[0] = AEGfxTextureLoad("Assets/player_idle-1.png");
    playerIdle[1] = AEGfxTextureLoad("Assets/player_idle-2.png");
    playerIdle[2] = AEGfxTextureLoad("Assets/player_idle-3.png");
    playerIdle[3] = AEGfxTextureLoad("Assets/player_idle-4.png");

    playerWalkUp[0] = AEGfxTextureLoad("Assets/player_walk_up-1.png");
    playerWalkUp[1] = AEGfxTextureLoad("Assets/player_walk_up-2.png");
    playerWalkUp[2] = AEGfxTextureLoad("Assets/player_walk_up-3.png");
    playerWalkUp[3] = AEGfxTextureLoad("Assets/player_walk_up-4.png");

    playerWalkDown[0] = AEGfxTextureLoad("Assets/player_walk_down-1.png");
    playerWalkDown[1] = AEGfxTextureLoad("Assets/player_walk_down-2.png");
    playerWalkDown[2] = AEGfxTextureLoad("Assets/player_walk_down-3.png");
    playerWalkDown[3] = AEGfxTextureLoad("Assets/player_walk_down-4.png");

    playerWalkLeft[0] = AEGfxTextureLoad("Assets/player_walk_left-1.png");
    playerWalkLeft[1] = AEGfxTextureLoad("Assets/player_walk_left-2.png");
    playerWalkLeft[2] = AEGfxTextureLoad("Assets/player_walk_left-3.png");
    playerWalkLeft[3] = AEGfxTextureLoad("Assets/player_walk_left-4.png");

    playerWalkRight[0] = AEGfxTextureLoad("Assets/player_walk_right-1.png");
    playerWalkRight[1] = AEGfxTextureLoad("Assets/player_walk_right-2.png");
    playerWalkRight[2] = AEGfxTextureLoad("Assets/player_walk_right-3.png");
    playerWalkRight[3] = AEGfxTextureLoad("Assets/player_walk_right-4.png");


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
                gTimer.start(300);
                currentState = GameState::GAME;
            }
            else if (mainMenu.IsQuitSelected())
            {
                std::cout << "Out";
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
                gTimer.start(300);
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
            
            winScreen.Render(pMesh, backgroundTex, paperTex,buttonTex, "You Win!");
            
        }
        break;

        case GameState::LOSE_SCREEN:
        {
            // Update & render Main Menu
            int check = loseScreen.Update();

            // Check menu selection
            if (check == 1)
            {
                gTimer.start(300);
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

           // AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            loseScreen.Render(pMesh, backgroundTex, paperTex,buttonTex, "You Lose :(");
        }
        break;
        case GameState::PAUSE_MENU:
        {
            // Update and render the pause menu
            int result = pauseMenu.Update();
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            pauseMenu.Render(pMesh, backgroundTex,buttonTex); // Reuse MainMenu logo if desired

            // If the user clicks "Resume Game", return to gameplay.
            if (result == 1) // "Resume Game"
            {
                // Unpause the timer here
                gTimer.pauseresume(); // This sets pauseTimer = false and recalculates startTime

                currentState = GameState::GAME;
            }
            // If "Quit Game" is selected, exit the application.
            else if (result == 2)
            {
                gGameRunning = false;
            }
        }
        break;
        // ------------------------------
        // GAME
        // ------------------------------
        case GameState::GAME:
        {
            // 1. Update Player & Collisions
            players1.playerDash();
            players1.playerMove(400.0);
            
            players1.ClampToScreen();

            for (size_t i = 0; i < objectcollision.size(); i++)
            {
                const Rect& object = objectcollision[i];
                players1.playerCheckCollisonobject(object.x, object.y, object.width, object.height);
            }
			// 2. Update Mouse
            mouse1.mouseMove(200.0f);
            mouse2.mouseMove(150.0f);
            mouse3.mouseMove(170.0f);
            // 2. Render the game world
            // Check for pause input (R key)
            if (AEInputCheckTriggered(AEVK_R))
            {
                // Pause the timer here
                gTimer.pauseresume(); // This sets pauseTimer = true internally

                currentState = GameState::PAUSE_MENU;
                break; // exit GAME state update immediately
            }
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
            

            // Only show device UI when player is colliding with the device.
            if (players1.playerCheckCollison(collisionBoxes[3].x, collisionBoxes[3].y, collisionBoxes[3].width, collisionBoxes[3].height))
            {
                if (!mouseDeviceCooldownTimer.completed())
                {
                    float remaining = static_cast<float>(mouseDeviceCooldownTimer.getRemainingTime());
                    std::string cooldownStr = "Device cooldown: " + std::to_string(static_cast<int>(remaining)) + " s";
                    AEGfxPrint(FontID, cooldownStr.c_str(), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
                }
                else
                {
                    AEGfxPrint(FontID, "Press E to activate device", 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
                    if (AEInputCheckTriggered(AEVK_E))
                    {
                        // Generate a random chase duration between 20 and 30 seconds.
                        float chaseDuration = 20.0f + static_cast<float>(rand()) / RAND_MAX * 10.0f;
                        mouse1.chaseAway(chaseDuration);
                        mouse2.chaseAway(chaseDuration);
                        mouse3.chaseAway(chaseDuration);
                        mouseDeviceCooldownTimer.start(25.0);
                    }
                }
            }

            
            // Ingredient boxes (3 boxes at top?), Active recipes, etc.
            RenderIngredientbox(pMesh, boxTex);
            AEGfxSetRenderMode(AE_GFX_RM_COLOR);
            RenderActiveRecipes(pMesh, recipeTex, recipeSystem);
            //mouse Device
            mouseDevicefun(pMesh, deviceTex);
            // Render Stove & Player
            AEGfxSetRenderMode(AE_GFX_RM_COLOR);
            RenderStove(pStoveMesh,Wok, players1,qteGauge,stoveTex,stoveDirtyTex,stoveCookTex);
            players1.playerdraw(pMesh, IngredientMesh, playerIdle,playerWalkUp , playerWalkDown , playerWalkLeft, playerWalkRight);
            mouse1.mousedraw(pMesh,mouseUp, mouseDown , mouseLeft, mouseRight);
            mouse2.mousedraw(pMesh, mouseUp, mouseDown, mouseLeft, mouseRight);
            mouse3.mousedraw(pMesh, mouseUp, mouseDown, mouseLeft, mouseRight);
            RenderQTEGauge(pMesh, qteGauge);

            // Collision boxes for ingredients or special objects
            for (size_t i = 0; i < g_currentBoxIngredients.size(); i++)
            {
                const Rect& collBox = collisionBoxes[i];
                const Rect& visualBox = highingredientBoxes[i];

                // If player is colliding with ingredient box
                if (players1.playerCheckCollison(collBox.x, collBox.y, collBox.width, collBox.height)&&!mouse1.mouseCheckCollison(collBox.x, collBox.y, collBox.width, collBox.height) && !mouse2.mouseCheckCollison(collBox.x, collBox.y, collBox.width, collBox.height) && !mouse3.mouseCheckCollison(collBox.x, collBox.y, collBox.width, collBox.height))
                {
                    // Render highlight
                    RenderhighlightIngredientBox(pMesh, visualBox);
                    // Handle pickup
                    players1.playerPickUp(g_currentBoxIngredients[i]);
                }

                // Drop logic (stove or dustbin, etc.)
                if (players1.playerCheckCollison(Wok.x, Wok.y, Wok.width, Wok.height) ||
                    players1.playerCheckCollison(objectcollision[0].x, objectcollision[0].y,
                        objectcollision[0].width, objectcollision[0].height))
                {
                    players1.playerDrop(Wok);
                }
            }
            // Check collision with the mouse device
            if (players1.playerCheckCollison(collisionBoxes[3].x, collisionBoxes[3].y, collisionBoxes[3].width, collisionBoxes[3].height)) {
                // Render highlight for the mouse device.
                RenderhighlightIngredientBox(pMesh, collisionBoxes[3]);

               
            }


            // Render ingredients on the boxes
            RenderIngredientsOnBoxes(pMesh,
                chickenTex, beefTex, cheeseTex,
                eggTex, riceTex, potatoTex);

            // Show score & timer at the top
            displayScore(score);
            displayTimer(gTimer.getRemainingTime());

            if (score >= 30 && gTimer.getRemainingTime() > 0)
            {
                currentState = GameState::WIN_SCREEN;
            }
            if (gTimer.getRemainingTime() <= 0)
            {
                currentState = GameState::LOSE_SCREEN;
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
    DestroyFront();
    // Free memory
    if (backgroundTex)    AEGfxTextureUnload(backgroundTex);
    if (pMesh)            AEGfxMeshFree(pMesh);
    if (IngredientMesh)   AEGfxMeshFree(IngredientMesh);
    if (pStoveMesh)       AEGfxMeshFree(pStoveMesh);
    if (uiMesh)           AEGfxMeshFree(uiMesh);
    if (bTex)             AEGfxTextureUnload(bTex);
    if (dTex)             AEGfxTextureUnload(dTex);
    if (chickenTex)       AEGfxTextureUnload(chickenTex);
    if (beefTex)          AEGfxTextureUnload(beefTex);
    if (cheeseTex)        AEGfxTextureUnload(cheeseTex);
    if (eggTex)           AEGfxTextureUnload(eggTex);
    if (riceTex)          AEGfxTextureUnload(riceTex);
    if (potatoTex)        AEGfxTextureUnload(potatoTex);
    if (stoveTex)         AEGfxTextureUnload(stoveTex);
    if (stoveDirtyTex)    AEGfxTextureUnload(stoveDirtyTex);
    if (stoveCookTex)     AEGfxTextureUnload(stoveCookTex);
    if (paperTex)         AEGfxTextureUnload(paperTex);
    if (buttonTex)        AEGfxTextureUnload(buttonTex);
    if (recipeTex)        AEGfxTextureUnload(recipeTex);

    for (size_t x{}; x < playerIdle.size(); ++x) {
        if (playerIdle[x])       AEGfxTextureUnload(playerIdle[x]);
        if (playerWalkUp[x])     AEGfxTextureUnload(playerWalkUp[x]);
        if (playerWalkDown[x])   AEGfxTextureUnload(playerWalkDown[x]);
        if (playerWalkLeft[x])   AEGfxTextureUnload(playerWalkLeft[x]);
        if (playerWalkRight[x])  AEGfxTextureUnload(playerWalkRight[x]);
    }
    for (size_t x{}; x < mouseUp.size(); ++x) {
        if (mouseUp[x])       AEGfxTextureUnload(mouseUp[x]);
        if (mouseDown[x])     AEGfxTextureUnload(mouseDown[x]);
        if (mouseLeft[x])   AEGfxTextureUnload(mouseLeft[x]);
        if (mouseRight[x])   AEGfxTextureUnload(mouseRight[x]);
    }


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
