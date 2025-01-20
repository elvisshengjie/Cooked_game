// ---------------------------------------------------------------------------
// includes

#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include "main.h"




void playermovement(float &x,float &y) 
{
	if (AEInputCheckCurr(AEVK_W))
	{
		y+= 4;
	}
	if (AEInputCheckCurr(AEVK_S))
	{
		y -= 4;
	}
	if (AEInputCheckCurr(AEVK_D))
	{
		x += 4;
	}
	if (AEInputCheckCurr(AEVK_A))
	{
		x -= 4;
	}
}

void clampScreen(float& x, float& y, float& width, float& height, float screenWidth,float screenHeight) 
{
	const float right = x + width;
	if (x < -screenWidth/2 + width/2) {
		x = -screenWidth/2 + width/2;
	}
	else if (right >= screenWidth/2 + width/2)
	{
		x = (screenWidth/2) - width/2;
	}
	const float bottom = y - height;
	if (y > screenHeight/2 - height/2)
	{
		y = screenHeight/2 - height/2 ;
	}
	else if (bottom <= -(screenHeight/2)-height/2)
	{
		y = (-screenHeight / 2 ) + height/2;
	}

}
bool collisionCircle(float x0, float y0, float width0, float height0, float x1, float y1, float width1, float height1)
{


	float circle_radius = width0 / 2 + width1 / 2;
	float square_radius = circle_radius * circle_radius;
	float distanceX = x0 - x1;
	float distanceY = y0 - y1;
	float squaredistance = distanceX * distanceX + distanceY * distanceY;
	if (squaredistance < square_radius) {
		return true;
	}
	else {
		return false;
	}

}

bool healhbarexist(float healthwidth, float x, float healthwidth2)
{
	float const health = 1083;
	if (x >= 0) 
	{
		float tempx1 = x + health / 2 - healthwidth2;

		if (healthwidth < tempx1) {
			return false;
		}
		else 
		{
			return true;
		}
	}

	if (x < 0) 
	{
		float tempx2 = health / 2 + x - healthwidth2/2;

		if (healthwidth < tempx2)
		{
			return false;

		}
		else 
		{
			return true;
		}
	}

	return false;
}


// ---------------------------------------------------------------------------
// main

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	int gGameRunning = 1;

	// Initialization of your own variables go here

	// Using custom window procedure
	AESysInit(hInstance, nCmdShow, 1600, 900, 1, 60, false, NULL);

	// Changing the window title
	AESysSetWindowTitle("My New Demo!");
	AEGfxTexture* pTex = AEGfxTextureLoad("Assets/PlanetTexture.png");
	// reset the system modules
	AESysReset();

	AEGfxMeshStart();


	AEGfxTriAdd(
		-0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

	AEGfxTriAdd(
		0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
		0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
		-0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);



	// Saving the mesh (list of triangles) in pMesh
	AEGfxVertexList* pMesh = AEGfxMeshEnd();

	// Transformation matrix
	AEMtx33 transformationMat{ 0 }, modelMat{ 0 }, scaleMat{ 0 }, rotateMat{ 0 };
	rectleft.x = -400.0f;
	rectleft.y = 0.0f;
	rectleft.width = 400;
	rectleft.height = 400;

	rectright.x = 400.0f;
	rectright.y = 0.0f;
	rectright.width = 400;
	rectright.height = 400;

	rectplayer.x = 0.0f;
	rectplayer.y = 0.0f;
	rectplayer.width = 50.0f;
	rectplayer.height = 50.0f;

	recthealth.x = 0.0f;
	recthealth.y = 370.0f;
	recthealth.width = 1083.0f;
	recthealth.height = 60.0f;

	recthealth2.x = 0.0f;
	recthealth2.y = 370.0f;
	recthealth2.width = 1083.0f;
	recthealth2.height = 60.0f;

	recthealth3.x = 513.0f;
	recthealth3.y = 275.0f;
	recthealth3.width = 57.0f;
	recthealth3.height = 60.0f;


	recthealth4.x = 399.0f;
	recthealth4.y = 275.0f;
	recthealth4.width = 57.0f;
	recthealth4.height = 60.0f;

	recthealth5.x = 285.0f;
	recthealth5.y = 275.0f;
	recthealth5.width = 57.0f;
	recthealth5.height = 60.0f;

	recthealth6.x = 171.0f;
	recthealth6.y = 275.0f;
	recthealth6.width = 57.0f;
	recthealth6.height = 60.0f;

	recthealth7.x = 57.0f;
	recthealth7.y = 275.0f;
	recthealth7.width = 57.0f;
	recthealth7.height = 60.0f;

	recthealth8.x = -57.0f;
	recthealth8.y = 275.0f;
	recthealth8.width = 57.0f;
	recthealth8.height = 60.0f;

	recthealth9.x = -171.0f;
	recthealth9.y = 275.0f;
	recthealth9.width = 57.0f;
	recthealth9.height = 60.0f;

	recthealth10.x = -285.0f;
	recthealth10.y = 275.0f;
	recthealth10.width = 57.0f;
	recthealth10.height = 60.0f;

	recthealth11.x = -399.0f;
	recthealth11.y = 275.0f;
	recthealth11.width = 57.0f;
	recthealth11.height = 60.0f;

	recthealth12.x = -512.0f;
	recthealth12.y = 275.0f;
	recthealth12.width = 57.0f;
	recthealth12.height = 60.0f;







	

	// Game Loop
	while (gGameRunning)
	{
		// Informing the system about the loop's start
		AESysFrameStart();

		// Basic way to trigger exiting the application
		// when ESCAPE is hit or when the window is closed
		if (AEInputCheckTriggered(AEVK_ESCAPE) || 0 == AESysDoesWindowExist())
			gGameRunning = 0;

		// Your own update logic goes here
		AEGfxSetRenderMode(AE_GFX_RM_COLOR);

		// Your own rendering logic goes here
		AEGfxSetBackgroundColor(0.5f, 0.5f, 0.5f);

	
		AEGfxSetTransparency(1.0f);
		playermovement(rectplayer.x, rectplayer.y);

		clampScreen(rectplayer.x, rectplayer.y, rectplayer.width, rectplayer.height, screenWidth, screenHeight);
		if (collisionCircle(rectplayer.x, rectplayer.y, rectplayer.width, rectplayer.height, rectleft.x, rectleft.y, rectleft.width, rectleft.height) )
		{
			recthealth2.width += 6;
			recthealth2.x += 3;

		}
		if (recthealth2.width > 1083)
		{
			recthealth2.width = 1083;
			recthealth2.x -= 3;
		}

		if (collisionCircle(rectplayer.x, rectplayer.y, rectplayer.width, rectplayer.height, rectright.x, rectright.y, rectright.width, rectright.height)) 
		{
			recthealth2.width -= 6;
			recthealth2.x -= 3;
		}
		if (recthealth2.width < 0) 
		{
			recthealth2.width = 0;
			recthealth2.x += 3;
		}
		
		
		//LEFT RECT
		AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
		AEMtx33Trans(&modelMat, rectleft.x, rectleft.y);
		AEMtx33Scale(&scaleMat, rectleft.width, rectleft.height);
		AEMtx33Rot(&rotateMat, 0);
		AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
		AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
		AEGfxSetTransform(transformationMat.m);
		AEGfxSetColorToMultiply(0.0f, 1.0f, 0.0f, 1.0f);
		AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetBlendColor(0.0, 1.0f, 0.0, 1.0);
		AEGfxSetTransparency(1.0f);
		AEGfxTextureSet(pTex, 0, 0);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		AEGfxSetBlendMode(AE_GFX_BM_NONE); // Disable blend mode
		AEGfxSetTransparency(0.0f);        // Set transparency to 0.0f




		//RIGHT RECT
		AEMtx33Trans(&modelMat, rectright.x, rectright.y);
		AEMtx33Scale(&scaleMat, rectright.width, rectright.height);
		AEMtx33Rot(&rotateMat, 0);
		AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
		AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
		AEGfxSetTransform(transformationMat.m);
		AEGfxSetColorToMultiply(1.0f, 0.6f, 0.6f, 1.0f);
		AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetBlendColor(1.0, 0.6f, 0.6f, 1.0f);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		AEGfxSetBlendMode(AE_GFX_BM_NONE); // Disable blend mode
		AEGfxSetTransparency(0.0f);        // Set transparency to 0.0f
	
		//PLAYER
		AEMtx33Trans(&modelMat, rectplayer.x, rectplayer.y);
		AEMtx33Scale(&scaleMat, rectplayer.width, rectplayer.height);
		AEMtx33Rot(&rotateMat, 0);
		AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
		AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
		AEGfxSetTransform(transformationMat.m);
		AEGfxSetColorToMultiply(0.0f, 0.0f, 1.0f, 1.0f);
		AEGfxSetColorToAdd(0.0f, 0.0f, 0.0f, 0.0f);
		AEGfxSetBlendMode(AE_GFX_BM_BLEND);
		AEGfxSetBlendColor(0.0, 0.0f, 1.0f, 1.0f);
		AEGfxSetTransparency(1.0f);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);
		AEGfxSetBlendMode(AE_GFX_BM_NONE); // Disable blend mode
		AEGfxSetTransparency(0.0f);        // Set transparency to 0.0f


		AEGfxSetRenderMode(AE_GFX_RM_COLOR);
		//HEALTH BORDER

		AEMtx33Trans(&modelMat, recthealth.x, recthealth.y);
		AEMtx33Scale(&scaleMat, recthealth.width, recthealth.height);
		AEMtx33Rot(&rotateMat, 0);
		AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
		AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
		AEGfxSetTransform(transformationMat.m);
		AEGfxSetColorToMultiply(0.5f, 0.0f, 0.0f, 1.0f);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		//HEALTH bar
		AEMtx33Trans(&modelMat, recthealth2.x, recthealth2.y);
		AEMtx33Scale(&scaleMat, recthealth2.width, recthealth2.height);
		AEMtx33Rot(&rotateMat, 0);
		AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
		AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
		AEGfxSetTransform(transformationMat.m);
		AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 0.0f);
		AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		if (healhbarexist(recthealth2.width, recthealth3.x, recthealth3.width))
		{
			//health bars 2
			AEMtx33Trans(&modelMat, recthealth3.x, recthealth3.y);
			AEMtx33Scale(&scaleMat, recthealth3.width, recthealth3.height);
			AEMtx33Rot(&rotateMat, 0);
			AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
			AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
			AEGfxSetTransform(transformationMat.m);
			AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 0.0f);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		}

		if (healhbarexist(recthealth2.width, recthealth4.x, recthealth4.width))
		{
			//health bars 2
			AEMtx33Trans(&modelMat, recthealth4.x, recthealth4.y);
			AEMtx33Scale(&scaleMat, recthealth4.width, recthealth4.height);
			AEMtx33Rot(&rotateMat, 0);
			AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
			AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
			AEGfxSetTransform(transformationMat.m);
			AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 0.0f);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		}
		if (healhbarexist(recthealth2.width, recthealth5.x, recthealth5.width))
		{
			//health bars 2
			AEMtx33Trans(&modelMat, recthealth5.x, recthealth5.y);
			AEMtx33Scale(&scaleMat, recthealth5.width, recthealth5.height);
			AEMtx33Rot(&rotateMat, 0);
			AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
			AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
			AEGfxSetTransform(transformationMat.m);
			AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 0.0f);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		}
		if (healhbarexist(recthealth2.width, recthealth6.x, recthealth6.width))
		{
			//health bars 2
			AEMtx33Trans(&modelMat, recthealth6.x, recthealth6.y);
			AEMtx33Scale(&scaleMat, recthealth6.width, recthealth6.height);
			AEMtx33Rot(&rotateMat, 0);
			AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
			AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
			AEGfxSetTransform(transformationMat.m);
			AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 0.0f);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		}
		if (healhbarexist(recthealth2.width, recthealth7.x, recthealth7.width))
		{
			//health bars 2
			AEMtx33Trans(&modelMat, recthealth7.x, recthealth7.y);
			AEMtx33Scale(&scaleMat, recthealth7.width, recthealth7.height);
			AEMtx33Rot(&rotateMat, 0);
			AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
			AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
			AEGfxSetTransform(transformationMat.m);
			AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 0.0f);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		}
		if (healhbarexist(recthealth2.width, recthealth8.x, recthealth8.width))
		{
			//health bars 2
			AEMtx33Trans(&modelMat, recthealth8.x, recthealth8.y);
			AEMtx33Scale(&scaleMat, recthealth8.width, recthealth8.height);
			AEMtx33Rot(&rotateMat, 0);
			AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
			AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
			AEGfxSetTransform(transformationMat.m);
			AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 0.0f);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		}
		if (healhbarexist(recthealth2.width, recthealth9.x, recthealth9.width))
		{
			//health bars 2
			AEMtx33Trans(&modelMat, recthealth9.x, recthealth9.y);
			AEMtx33Scale(&scaleMat, recthealth9.width, recthealth9.height);
			AEMtx33Rot(&rotateMat, 0);
			AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
			AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
			AEGfxSetTransform(transformationMat.m);
			AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 0.0f);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		}

		if (healhbarexist(recthealth2.width, recthealth10.x, recthealth10.width))
		{
			//health bars 2
			AEMtx33Trans(&modelMat, recthealth10.x, recthealth10.y);
			AEMtx33Scale(&scaleMat, recthealth10.width, recthealth10.height);
			AEMtx33Rot(&rotateMat, 0);
			AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
			AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
			AEGfxSetTransform(transformationMat.m);
			AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 0.0f);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		}

		if (healhbarexist(recthealth2.width, recthealth11.x, recthealth11.width))
		{
			//health bars 2
			AEMtx33Trans(&modelMat, recthealth11.x, recthealth11.y);
			AEMtx33Scale(&scaleMat, recthealth11.width, recthealth11.height);
			AEMtx33Rot(&rotateMat, 0);
			AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
			AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
			AEGfxSetTransform(transformationMat.m);
			AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 0.0f);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		}
		if (healhbarexist(recthealth2.width, recthealth12.x, recthealth12.width))
		{
			//health bars 2
			AEMtx33Trans(&modelMat, recthealth12.x, recthealth12.y);
			AEMtx33Scale(&scaleMat, recthealth12.width, recthealth12.height);
			AEMtx33Rot(&rotateMat, 0);
			AEMtx33Concat(&transformationMat, &rotateMat, &scaleMat);
			AEMtx33Concat(&transformationMat, &modelMat, &transformationMat);
			AEGfxSetTransform(transformationMat.m);
			AEGfxSetColorToMultiply(1.0f, 0.0f, 0.0f, 0.0f);
			AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);

		}
		// Informing the system about the loop's end
		AESysFrameEnd();

	}
	AEGfxTextureUnload(pTex);
	AEGfxMeshFree(pMesh);
	// free the system
	AESysExit();
}