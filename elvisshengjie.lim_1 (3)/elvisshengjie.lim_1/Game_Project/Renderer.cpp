#include "Renderer.h"
#include <crtdbg.h> // To check for memory leaks
#include "AEEngine.h"
#include <math.h> 
Renderer::Renderer(AEGfxVertexList* mesh, AEGfxTexture* texture)
    : mMesh(mesh), mTexture(texture) {}

Renderer::~Renderer() {
    // Cleanup if necessary
}

void Renderer::DrawCircle(const Circle& circle) {
    AEGfxTextureSet(circle.texture, 0, 0);
    AEMtx33 transform;
    AEMtx33Scale(&transform, circle.radius * 2, circle.radius * 2);
    AEMtx33TransApply(&transform, &transform, circle.x, circle.y);
    AEGfxSetTransform(transform.m);
    AEGfxSetColorToMultiply(circle.multiplyColor.r, circle.multiplyColor.g, circle.multiplyColor.b, circle.multiplyColor.a);
    AEGfxSetColorToAdd(circle.addColor.r, circle.addColor.g, circle.addColor.b, circle.addColor.a);
    AEGfxSetBlendMode(circle.blendMode);
    AEGfxSetBlendColor(circle.blendColor.r, circle.blendColor.g, circle.blendColor.b, circle.blendColor.a);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(mMesh, AE_GFX_MDM_TRIANGLES);
}

void Renderer::DrawPlayer(float x, float y, float scaleX, float scaleY, AEGfxColor color) {
    AEGfxSetColorToMultiply(color.r, color.g, color.b, color.a);
    AEMtx33 transform;
    AEMtx33Scale(&transform, scaleX, scaleY);
    AEMtx33TransApply(&transform, &transform, x, y);
    AEGfxSetTransform(transform.m);
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    AEGfxSetBlendColor(color.r, color.g, color.b, color.a);
    AEGfxSetTransparency(1.0f);
    AEGfxMeshDraw(mMesh, AE_GFX_MDM_TRIANGLES);
}
