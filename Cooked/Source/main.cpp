#include <iostream>
// includes
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include <AEGraphics.h>

#include <math.h>
#include "player.hpp"
#include "render.hpp"
#include "utils.hpp"
#include "collison.hpp"


// ---------------------------------------------------------------------------
// main
                   // Increases health


// Function to check if player is within a circle
class CoreEngine
{
    bool gGameRunning = true;
    AEGfxVertexList* pMesh = nullptr;
    AEGfxVertexList* IngredientMesh = nullptr;
    AEGfxTexture* bTex = nullptr;
    AEGfxTexture* dTex = nullptr;
	AEGfxTexture* chickenTex = nullptr;
    AEGfxTexture* beefTex = nullptr;
    AEGfxTexture* cheeseTex = nullptr;
    AEGfxTexture* eggTex = nullptr;
    AEGfxTexture* riceTex = nullptr;
    AEGfxTexture* potatoTex = nullptr;
    RecipeSystem recipeSystem;
    
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
    srand(static_cast<unsigned>(time(nullptr)));  // Seed the random generator once

    InitFont();
   
    // Initialize our 3 current box ingredients
    for (int i = 0; i < 3; ++i)
    {
        g_currentBoxIngredients[i] = GetRandomIngredient();
    }

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
	chickenTex = AEGfxTextureLoad("Assets/chicken.png");
	beefTex = AEGfxTextureLoad("Assets/beef.png");
	cheeseTex = AEGfxTextureLoad("Assets/cheese.png");
	eggTex = AEGfxTextureLoad("Assets/egg.png");
	riceTex = AEGfxTextureLoad("Assets/rice.png");
	potatoTex = AEGfxTextureLoad("Assets/potato.png");
	


    AEGfxMeshStart();
    AEGfxTriAdd(
        -0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,  // Bottom-left
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,  // Bottom-right
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f   // Top-left
    );
    AEGfxTriAdd(
        0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,  // Bottom-right
        0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,  // Top-right
        -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f   // Top-left
    );
    IngredientMesh = AEGfxMeshEnd();

}

void CoreEngine::Update()
{

    while (gGameRunning) {

        AESysFrameStart();

        if (AEInputCheckTriggered(AEVK_ESCAPE) || !AESysDoesWindowExist())
            gGameRunning = false;


        players1.playerMove(6.0);
        players1.ClampToScreen();
        for (size_t i = 0; i < objectcollision.size(); i++) {
            const Rect& object = objectcollision[i];


            players1.playerCheckCollisonobject(object.x, object.y, object.width, object.height);


        }

        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        Renderbackground(pMesh, bTex);
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        RenderDustbin(pMesh, dTex);
       
        players1.playerUpdate(Wok,recipeSystem);

        Wok.update(recipeSystem);

        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        RenderIngredientbox(pMesh);
        RenderActiveRecipes(pMesh, recipeSystem);        
        RenderStove(pMesh, Wok,players1);
        players1.playerdraw(pMesh, IngredientMesh);

        for (size_t i = 0; i < collisionBoxes.size(); i++) {
            const Rect& collBox = collisionBoxes[i];
            const Rect& visualBox = highingredientBoxes[i];

            if (players1.playerCheckCollison(collBox.x, collBox.y, collBox.width, collBox.height)) {
                // Optionally, render a highlight for the box.
                RenderhighlightIngredientBox(pMesh, visualBox);
                // Handle pickup/drop for the current box.
                players1.playerPickUp(g_currentBoxIngredients[i]);
            }
            if (players1.playerCheckCollison(Wok.getX(), Wok.getY(), Wok.getW(), Wok.getH()) ||
                players1.playerCheckCollison(objectcollision[0].x, objectcollision[0].y, objectcollision[0].width, objectcollision[0].height))
            {

                players1.playerDrop(Wok);
            }
        }

        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
       
         RenderIngredientsOnBoxes(
            pMesh,
            chickenTex,  
            beefTex,
            cheeseTex,
            eggTex,
            riceTex,
            potatoTex
        );



        AESysFrameEnd();
    }

}

void CoreEngine::Exit(){
    if (pMesh) AEGfxMeshFree(pMesh);
    if (IngredientMesh)AEGfxMeshFree(IngredientMesh);
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


