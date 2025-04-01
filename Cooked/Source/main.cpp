/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file main.cpp
@author1 Elvis lim sheng jie(elvisshengjie.lim)
- game state mangement Core Engine class
@author2 Justin Kong (yimo.kong)
@author3 Norman Chan (chan.f)
@author4 Kerrin Lemin Khoo ( kerrinlemin.k)
@course csd1451s25 Software Engineering Project 2
@section a
*//*______________________________________________________________________*/
#include <iostream>
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include <AEGraphics.h>
#include <math.h>
#include <vector>
#include "main_menu.hpp"
#include "render.hpp"
#include "utils.hpp"
#include "collison.hpp"
#include "player.hpp"
#include "mouse.hpp"
#include "AssetLoader.hpp"


// ---------------------------------------------------------------------------
// Define your game states
enum class GameState {

    DIGIPEN_LOGO,
    MAIN_MENU,
    CONFIRM_SCREEN,
    GAME,
    CREDITS,
    PAUSE_MENU,
	OPTIONS_MENU,
    WIN_SCREEN,
    LOSE_SCREEN
};


// CoreEngine class
class CoreEngine
{
    bool mainMenuFlag = false;
    bool pauseFlag = false;
   
    bool gGameRunning = true;
    GameState currentState = GameState::DIGIPEN_LOGO;
    Timer mouseDeviceCooldownTimer{};
    int gameTimer{ 300 };

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
    AEGfxTexture* barTex{ nullptr };
    AEGfxTexture* sliderTex{ nullptr };
    AEGfxTexture* targetTex{ nullptr };
    AEGfxTexture* htpTex{ nullptr };
    AEGfxTexture* htpButtonTex{ nullptr };





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
    Digipen digi;
    MainMenu     mainMenu;
    PauseMenu    pauseMenu;
    Credits     creditMenu;
    QTE          qteGauge;
    Stove        Wok;
    WinScreen    winScreen;
    WinScreen    loseScreen;
    OptionsMenu optionsMenu;
    ConfirmScreen confirmSN;

    float g_bgmVolume = 0.1f; // default volume
    Timer gTimer{};

public:
    void Init();
    void Update();
    void Exit();

};

//audio
bool hasPlayed = false;
AEAudio cookingSound{}; // Cooking sound effect
AEAudio winPtsSound{}; //sound when cooking finished and points added
AEAudio losePtsSound{}; //sound when cooking finished and points deducted
AEAudio qteSuccessSound{}; // QTE Success  sound effect
AEAudio qteFailSound{}; // QTE fail  sound effect
AEAudio winSound{}; //win screen sound effect
AEAudio loseSound{};//lose screen sound effect
AEAudio cleaningSound{}; //cleaning sound effect
AEAudio spraySound{};
AEAudio pauseSound{};
AEAudio bouken{}; //bgm

AEAudioGroup bgm; // short for 'background music'
AEAudioGroup sfx; //sound effects
AEAudioGroup points; //sound effects for points
AEAudioGroup mice;
AEAudioGroup pause;


// ------------------------------------------------------------
// CoreEngine::Init
void CoreEngine::Init()
{
    if (!RectLoader::LoadRectangles("Assets/Rect.json")) {
        std::cerr << "Failed to load rectangles!\n";
        //AESysExit();  // Safely exit or handle gracefully
    }
    currentState = GameState::DIGIPEN_LOGO;
    // Changing the window title

    gTimer.start(gameTimer);
    AESysSetWindowTitle("Cooked!");

    // AESysReset() re-initializes various engine systems
    AESysReset();

    // Seed the random generator once
    srand(static_cast<unsigned>(time(nullptr)));

    // Initialize the main menu
    digi.Init();
    mainMenu.Init();
    confirmSN.Init();
    winScreen.Init();
    loseScreen.Init();
    pauseMenu.Init();
    creditMenu.setTexture(mainMenu.GetHtpButtonTexture());
    creditMenu.Init();
    optionsMenu.Init();  // set up the Options menu
    
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
    barTex = AEGfxTextureLoad("Assets/paperUIButton.png");
    sliderTex = AEGfxTextureLoad("Assets/red.png");
    targetTex = AEGfxTextureLoad("Assets/red.png");
    htpTex = AEGfxTextureLoad("Assets/howtoplay.png");
    htpButtonTex = AEGfxTextureLoad("Assets/X.png");


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

    // 4. Create sound and music
    
    // Configure audio group
    
    bouken = AEAudioLoadMusic("Assets/bm.mp3");
    cookingSound = AEAudioLoadSound("Assets/cookingSound.mp3"); 
    winSound = AEAudioLoadSound("Assets/winSound.mp3");
    loseSound = AEAudioLoadSound("Assets/loseSound.mp3");
    cleaningSound = AEAudioLoadSound("Assets/cleaningSound.mp3");
    qteFailSound = AEAudioLoadSound("Assets/qteFailSound.mp3");
    qteSuccessSound = AEAudioLoadSound("Assets/qteSuccessSound.mp3");
    winPtsSound = AEAudioLoadSound("Assets/winPts.mp3");
    losePtsSound = AEAudioLoadSound("Assets/losePts.mp3");
    spraySound = AEAudioLoadSound("Assets/spraySound.mp3");
    pauseSound = AEAudioLoadSound("Assets/pauseSound.mp3");

    bgm = AEAudioCreateGroup(); // short for 'background music'
    sfx = AEAudioCreateGroup();
    points = AEAudioCreateGroup();
    mice = AEAudioCreateGroup();
    pause = AEAudioCreateGroup();

    AEAudioPlay(bouken, bgm, g_bgmVolume, 1.f, -1); // we can start playing here.
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

        case GameState::DIGIPEN_LOGO:
         {
            digi.Update();
            digi.Render(pMesh);
            if (digi.GetFlag()) {
                currentState = GameState::MAIN_MENU;
            }
          }
         break;
            // ------------------------------
            // MAIN MENU
            // ------------------------------
        case GameState::MAIN_MENU:
        {
            AEAudioResumeGroup(bgm);
            // Update & render Main Menu
            mainMenu.Update();

            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            mainMenu.Render(pMesh);

            // Check menu selection
            if (mainMenu.IsStartGameSelected())
            {
                gTimer.start(gameTimer);
                mouse1.init(-2500.0f, 100.0f);
                mouse2.init(2200.0f, 500.0f);
                mouse3.init(3300.0f, 0.0f);
                currentState = GameState::GAME;
            }
            else if (mainMenu.isCreditsSelected())
            {
                currentState = GameState::CREDITS;
            }
            else if(mainMenu.IsOptionsSelected())
            {
                currentState = GameState::OPTIONS_MENU;
            }
            else if (mainMenu.IsQuitSelected())
            {
                mainMenuFlag = true;
                  currentState = GameState::CONFIRM_SCREEN;
                
                
            }
        }
        break;
        case GameState::CONFIRM_SCREEN:
        {
            confirmSN.Update();
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            confirmSN.Render(pMesh, backgroundTex, buttonTex);
            if (confirmSN.GetFlag()) {
                gGameRunning = false;
            }
            else if (confirmSN.GetflagToUpdate() && mainMenuFlag) {
                confirmSN.ModflagToUpdate(false);
                mainMenuFlag = false;
                currentState = GameState::MAIN_MENU;
            }
            else if (confirmSN.GetflagToUpdate() && pauseFlag) {
                confirmSN.ModflagToUpdate(false);
                pauseFlag = false;
                currentState = GameState::PAUSE_MENU;
            }
                
        }
        break;
        case GameState::OPTIONS_MENU:
        {
            // Update returns an int indicating user action
            int result = optionsMenu.Update(g_bgmVolume, bgm);
            optionsMenu.Render(pMesh, backgroundTex, buttonTex);
            // If result == 1 => user clicked "Back"
            if (result == 1)
            {
                currentState = GameState::MAIN_MENU;
            }
        }
        break;
        case GameState::CREDITS:
        {

            creditMenu.Update();
            if (creditMenu.shouldExitToMain())  // Use Q or X to exit credits
            {
                creditMenu.ResetExitFlag();
                currentState = GameState::MAIN_MENU;
            }
            AEGfxSetRenderMode(AE_GFX_RM_COLOR);
            creditMenu.Render(pMesh);
           
        }
        break;
        case GameState::WIN_SCREEN:
        {
            AEAudioPauseGroup(bgm);
            // Update & render Main Menu

            int check = winScreen.Update();

            // Check menu selection
            if (check == 1)
            {
                gTimer.start(gameTimer);
                currentState = GameState::GAME;
            }
            else if (check == 2)
            {
                currentState = GameState::MAIN_MENU;
            }
            else if (check == 3)
            {
                mainMenuFlag = true;
                currentState = GameState::CONFIRM_SCREEN;
            }
            
            winScreen.Render(pMesh, backgroundTex, paperTex,buttonTex, "You Win!");
            
            if (!hasPlayed)
            {
                AEAudioPlay(winSound, sfx, 0.7f, 1.0f, 0);
                hasPlayed = true;
            }
            

            //reinit
            // reinitialize random box ingredients
            for (int i = 0; i < 3; ++i)
            {
                g_currentBoxIngredients[i] = GetRandomIngredient();
            }
            //reinit player
            players1.playerInit();
            score = 0;
            Wok.clearWok();
            Wok.currentState = Stove::StoveState::IDLE;
            mouse1.init(-2500.0f, 100.0f);
            mouse2.init(2200.0f, 500.0f);
            mouse3.init(3300.0f, 0.0f);
        }
        break;
        

        case GameState::LOSE_SCREEN:
        {
            AEAudioPauseGroup(bgm);
            // Update & render Main Menu
            int check = loseScreen.Update();

            // Check menu selection
            if (check == 1)
            {
                gTimer.start(gameTimer);
                currentState = GameState::GAME;
            } 
            else if (check == 2)
            {
                currentState = GameState::MAIN_MENU;
            }
            else if (check == 3)
            {
                mainMenuFlag = true;
                currentState = GameState::CONFIRM_SCREEN;
            }

           // AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            loseScreen.Render(pMesh, backgroundTex, paperTex,buttonTex, "You Lose :(");
            if (!hasPlayed) {
                AEAudioPlay(loseSound, sfx, 1.0f, 1.0f, 0);
                hasPlayed = true;

            }

            //reinit
            // reinitialize random box ingredients
            for (int i = 0; i < 3; ++i)
            {
                g_currentBoxIngredients[i] = GetRandomIngredient();
            }
            //reinit player
            players1.playerInit();
            score = 0;
            Wok.clearWok();
            Wok.currentState = Stove::StoveState::IDLE;
            mouse1.init(-2500.0f, 100.0f);
            mouse2.init(2200.0f, 500.0f);
            mouse3.init(3300.0f, 0.0f);
        }
        break;
        case GameState::PAUSE_MENU:
        {
            // Update and render the pause menu
            int result = pauseMenu.Update();
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            pauseMenu.Render(pMesh, backgroundTex,buttonTex ,htpTex ,htpButtonTex); // Reuse MainMenu logo if desired

            // If the user clicks "Resume Game", return to gameplay.
            if (result == 1) // "Resume Game"
            {
                // Unpause the timer here
                gTimer.pauseresume(); // This sets pauseTimer = false and recalculates startTime
                Wok.cookingTimer.pauseresume();
                recipeSystem.pauseRecipeTimers();
                currentState = GameState::GAME;
            }
            // If "Quit Game" is selected, exit the application.
            else if (result == 3)
            {
                pauseFlag = true;
                currentState = GameState::CONFIRM_SCREEN;
            }

            AEAudioPauseGroup(bgm);
            AEAudioPauseGroup(sfx);
            AEAudioPauseGroup(points);
            AEAudioPauseGroup(mice);
            
            if (!hasPlayed)
            {   
                AEAudioPlay(pauseSound, pause, 0.02f, 1.0f, -1);
                hasPlayed = true;
            }
        }
        break;
        // ------------------------------
        // GAME
        // ------------------------------
        case GameState::GAME:
        {
            AEAudioResumeGroup(bgm);
            AEAudioResumeGroup(sfx);
            AEAudioResumeGroup(points);
            AEAudioResumeGroup(mice);
            AEAudioStopGroup(pause);
            hasPlayed = false;
            static bool ratSoundTriggered = false;

       
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
            if (AEInputCheckTriggered(AEVK_T))
            {
                // Pause the timer here
                gTimer.pauseresume(); // This sets pauseTimer = true internally

                currentState = GameState::PAUSE_MENU;

                recipeSystem.pauseRecipeTimers();
                Wok.cookingTimer.pauseresume(); // Resume stove timer
                break; // exit GAME state update immediately
            }
            // Background / Floor
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            Renderbackground(pMesh, bTex);

            // Dustbin
            AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
            RenderDustbin(pMesh, dTex);



            // Player update logic (picking up, dropping, etc.)
            players1.playerUpdate(Wok, recipeSystem, qteGauge, cookingSound,qteFailSound,qteSuccessSound, sfx);

            // Stove / Wok logic (cooking)
            Wok.update(recipeSystem, winPtsSound, losePtsSound, sfx, points);
            

            recipeSystem.update();
            
            mouse::handleDeviceInteraction(collisionBoxes[3], mouseDeviceCooldownTimer, players1, spraySound, mice);
            // Ingredient boxes (3 boxes at top?), Active recipes, etc.
            RenderIngredientbox(pMesh, boxTex);
            AEGfxSetRenderMode(AE_GFX_RM_COLOR);
            RenderActiveRecipes(pMesh, recipeTex, recipeSystem , chickenTex, beefTex, cheeseTex, eggTex, riceTex, potatoTex);
            //mouse Device
            mouseDeviceRender(pMesh, deviceTex);
            // Render Stove & Player
            AEGfxSetRenderMode(AE_GFX_RM_COLOR);
            RenderStove(pStoveMesh,Wok, players1,qteGauge,stoveTex,stoveDirtyTex,stoveCookTex);
            renderStoveIngredient(pMesh, chickenTex, eggTex, cheeseTex, riceTex, beefTex, potatoTex,Wok);
            players1.playerdraw(pMesh, IngredientMesh, playerIdle,playerWalkUp , playerWalkDown , playerWalkLeft, playerWalkRight ,chickenTex , beefTex , riceTex, eggTex , cheeseTex , potatoTex  );
            mouse1.mousedraw(pMesh,mouseUp, mouseDown , mouseLeft, mouseRight);
            mouse2.mousedraw(pMesh, mouseUp, mouseDown, mouseLeft, mouseRight);
            mouse3.mousedraw(pMesh, mouseUp, mouseDown, mouseLeft, mouseRight);
            RenderQTEGauge(pMesh, qteGauge , barTex, sliderTex ,targetTex);

            
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
                    players1.playerDrop(Wok,cleaningSound, sfx);
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

    AEAudioUnloadAudio(bouken);
    AEAudioUnloadAudio(cookingSound);
    AEAudioUnloadAudio(winSound);
    AEAudioUnloadAudio(loseSound);
    AEAudioUnloadAudio(qteSuccessSound);
    AEAudioUnloadAudio(qteFailSound);
    AEAudioUnloadAudio(cleaningSound);
    AEAudioUnloadAudio(winPtsSound);
    AEAudioUnloadAudio(losePtsSound);
    AEAudioUnloadAudio(spraySound);
    AEAudioUnloadAudio(pauseSound);

    AEAudioUnloadAudioGroup(sfx);
    AEAudioUnloadAudioGroup(bgm);
    AEAudioUnloadAudioGroup(points);
    AEAudioUnloadAudioGroup(mice);
    AEAudioUnloadAudioGroup(pause);

    digi.Cleanup();

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
    if (boxTex)           AEGfxTextureUnload(boxTex);
    if (deviceTex)        AEGfxTextureUnload(deviceTex);
    if (barTex)           AEGfxTextureUnload(barTex);
    if (sliderTex)        AEGfxTextureUnload(sliderTex);
    if (targetTex)        AEGfxTextureUnload(targetTex);
    if (htpTex)           AEGfxTextureUnload(htpTex);
    if (htpButtonTex)     AEGfxTextureUnload(htpButtonTex);

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
