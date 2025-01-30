#include <iostream>
// includes
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include <math.h> 
#include "render.hpp"
#include "player.hpp"
#include "collison.hpp"

// ---------------------------------------------------------------------------
// main
                   // Increases health

// Function to check if player is within a circle
class CoreEngine
{
    bool gGameRunning = true;
    AEGfxVertexList* pMesh = nullptr;
    AEGfxTexture* bTex = nullptr;
    AEGfxTexture* dTex = nullptr;
public:
    void Init();
    void Update();
    void Exit();

};

void CoreEngine::Init()
{
    

    // Initialization of your own variables go here

    // Using custom window procedure
 

    // Changing the window title
    AESysSetWindowTitle("Health Bar Demo");


    AESysReset();


    AEGfxMeshStart();


    AEGfxTriAdd(
        -0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,  // bottom-left: red
        0.5f, -0.5f, 0xFF00FF00, 1.0f, 1.0f,   // bottom-right: green
        -0.5f, 0.5f, 0xFF0000FF, 0.0f, 0.0f);  // top-left: blue

    AEGfxTriAdd(
        0.5f, -0.5f, 0xFF00FF00, 1.0f, 1.0f,   // bottom-right: green
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,    // top-right: white
        -0.5f, 0.5f, 0xFF0000FF, 0.0f, 0.0f);  // top-left: blue

    pMesh = AEGfxMeshEnd();
    bTex = AEGfxTextureLoad("Assets/floor.png");
    dTex = AEGfxTextureLoad("Assets/dustbin.png");

}

void CoreEngine::Update()
{

    while (gGameRunning) {

        AESysFrameStart();

        if (AEInputCheckTriggered(AEVK_ESCAPE) || !AESysDoesWindowExist())
            gGameRunning = false;


        players1.playerMove(6.0);
        players1.ClampToScreen();
        //AEGfxSetBackgroundColor(0.35f, 0.2f, 0.1f);
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        Renderbackground(pMesh, bTex);
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        RenderDustbin(pMesh, dTex);
        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        RenderIngredientbox(pMesh);


        RenderStove(pMesh);
        players1.playerdraw(pMesh);

        for (size_t i = 0; i < collisionBoxes.size(); i++) {
            const Rect& collBox = collisionBoxes[i];
            const Rect& visualBox = highingredientBoxes[i];

            if (players1.playerCheckCollison(collBox.x, collBox.y, collBox.width, collBox.height)) {
                // Highlight the linked visual box
                RenderhighlightIngredientBox(pMesh, visualBox);
            }
        }



        AESysFrameEnd();
    }

}

void CoreEngine::Exit(){
    if (pMesh) AEGfxMeshFree(pMesh);
    if (bTex) AEGfxTextureUnload(bTex);
    if (dTex) AEGfxTextureUnload(dTex);
        AESysExit();
    
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, false, NULL);

    CoreEngine ce;
    ce.Init();
    ce.Update();
    ce.Exit();
}


/*
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    int gGameRunning = 1;

    // Initialization of your own variables go here

    // Using custom window procedure
    AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, false, NULL);

    // Changing the window title
    AESysSetWindowTitle("Health Bar Demo");

    
    AESysReset();

    
    AEGfxMeshStart();


    AEGfxTriAdd(
        -0.5f, -0.5f, 0xFFFF0000, 0.0f, 1.0f,  // bottom-left: red
        0.5f, -0.5f, 0xFF00FF00, 1.0f, 1.0f,   // bottom-right: green
        -0.5f, 0.5f, 0xFF0000FF, 0.0f, 0.0f);  // top-left: blue

    AEGfxTriAdd(
        0.5f, -0.5f, 0xFF00FF00, 1.0f, 1.0f,   // bottom-right: green
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,    // top-right: white
        -0.5f, 0.5f, 0xFF0000FF, 0.0f, 0.0f);  // top-left: blue

    
    AEGfxVertexList* pMesh = AEGfxMeshEnd();
    AEGfxTexture* bTex = AEGfxTextureLoad("Assets/floor.png");
    AEGfxTexture* dTex = AEGfxTextureLoad("Assets/dustbin.png");
    
    // Game Loop
    while (gGameRunning) {
      
        AESysFrameStart();

        if (AEInputCheckTriggered(AEVK_ESCAPE) || !AESysDoesWindowExist())
            gGameRunning = false;
       
       
        players1.playerMove(6.0);
        players1.ClampToScreen();
        //AEGfxSetBackgroundColor(0.35f, 0.2f, 0.1f);
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        Renderbackground(pMesh, bTex);
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        RenderDustbin(pMesh, dTex);
        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        RenderIngredientbox(pMesh);
        
        
        RenderStove(pMesh);
        players1.playerdraw(pMesh);

        for (size_t i = 0;i < collisionBoxes.size(); i++) {
            const Rect& collBox = collisionBoxes[i];
            const Rect& visualBox = highingredientBoxes[i];

            if (players1.playerCheckCollison(collBox.x, collBox.y, collBox.width, collBox.height)) {
                // Highlight the linked visual box
                RenderhighlightIngredientBox(pMesh, visualBox);
            }
        }

        

        AESysFrameEnd();
    }

    // Cleanup
   
    AESysExit();
    return 0;
}
*/
