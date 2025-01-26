#include <iostream>
// includes
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include <math.h> 
#include "render.hpp"
#include "player.hpp"
#include "collison.hpp"
#include "utils.hpp"

// ---------------------------------------------------------------------------
// main
                   // Increases health

// Function to check if player is within a circle


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
    AESysSetWindowTitle("Cooked!");

    
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
        /*AEGfxSetBackgroundColor(0.35f, 0.2f, 0.1f);*/ 
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        Renderbackground(pMesh, bTex);
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        RenderDustbin(pMesh, dTex);
        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        RenderIngredientbox(pMesh);
        RendercollisonIngredientBox(pMesh);
        RenderStove(pMesh);
        players1.playerdraw(pMesh);
        if (players1.playerCheckCollison(collison_ingredient_box1.x, collison_ingredient_box1.y, collison_ingredient_box1.width, collison_ingredient_box1.height)) {
            AEGfxSetRenderMode(AE_GFX_RM_COLOR);
            RenderhighlightIngredientBox(pMesh);
        }

        AESysFrameEnd();
    }

    // Cleanup
   
    AESysExit();
    return 0;
}

