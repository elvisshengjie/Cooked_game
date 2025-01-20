
// includes
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include <math.h> 

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

    // Game Loop
    while (gGameRunning) {
      
        AESysFrameStart();

        if (AEInputCheckTriggered(AEVK_ESCAPE) || !AESysDoesWindowExist())
            gGameRunning = false;
        AEGfxSetBackgroundColor(0.4f, 0.26f, 0.13f); // Dark brown color


        // Draw circles
        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		
			
	        AEMtx33 ingredientboxTransform;
			AEMtx33Scale(&ingredientboxTransform, 200.0f, 200.0f);
			AEMtx33TransApply(&ingredientboxTransform, &ingredientboxTransform, 200.0f, 200.0f);
			AEGfxSetTransform(ingredientboxTransform.m);
            AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 1.0f);
            AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
            AEGfxSetBlendMode(AE_GFX_BM_BLEND);
            AEGfxSetBlendColor(1.0f, 0.0f, 0.0f, 1.0f);
            AEGfxSetTransparency(1.0f);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		
        
    }

    // Cleanup
   
    AESysExit();
    return 0;
}

