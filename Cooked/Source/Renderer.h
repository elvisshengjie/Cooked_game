#ifndef RENDERER_H
#define RENDERER_H

#include "AEEngine.h"

// Structure to hold circle data
struct Circle {
    float x;
    float y;
    float radius;
    AEGfxTexture* texture;
   
};

// Renderer class to handle all rendering
class Renderer {
public:
    Renderer(AEGfxVertexList* mesh, AEGfxTexture* texture);
    ~Renderer();

    void DrawCircle(const Circle& circle);
    void DrawPlayer(float x, float y, float scaleX, float scaleY);

private:
    AEGfxVertexList* mMesh;
    AEGfxTexture* mTexture;
};

#endif // RENDERER_H
