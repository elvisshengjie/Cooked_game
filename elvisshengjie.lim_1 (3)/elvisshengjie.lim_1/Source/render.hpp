#pragma once
// render.hpp
#ifndef RENDER_HPP
#define RENDER_HPP

#include <crtdbg.h> // To check for memory leaks
#include <math.h> 
#include <AEEngine.h> // Replace with the actual header for your graphics framework

void Renderbackground(AEGfxVertexList* mesh, AEGfxTexture* tex);
// Renders the dustbin with texture
void RenderDustbin(AEGfxVertexList * mesh, AEGfxTexture* tex);

// Renders three circles with white boundaries
void RenderIngredientbox(AEGfxVertexList* mesh);

// Renders the stove with a red color
void RenderStove(AEGfxVertexList* mesh);

#endif // RENDER_HPP
