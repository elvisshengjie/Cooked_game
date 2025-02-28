#pragma once
#include <vector>
#include <string>
#include "AEEngine.h"
#include <AEGraphics.h>
#include "render.hpp"
#include "AEInput.h"
#include <cassert>

// Simple Button structure for menu items
struct Button {
    std::string label;
    float x, y;
    float width, height;
};

// Helper: Check if a point is inside a button (using center coordinates)
bool IsPointInsideButton(float px, float py, const Button& btn);

class MainMenu {
public:
    MainMenu() = default;
    ~MainMenu();

    // Initializes menu resources (fonts, background texture, buttons)
    void Init();

    // Handles input for menu navigation (keyboard and mouse)
    void Update();

    // Renders the menu background and buttons
    void Render(AEGfxVertexList* mesh);

   
    bool IsStartGameSelected() const;

   
    bool IsQuitSelected() const;

    
    void Cleanup();

private:
    std::vector<Button> buttons;          
    size_t selectedOption;                   
    s8 FontID_main_menu = -1;
    AEGfxTexture* background = nullptr;

    // Flag set when the mouse click activates the "Start Game" button
    bool m_StartGameActivated{ false };
};


class WinScreen
{
private:
    std::vector<Button> buttons;
    int selected{};
    bool m_StartGameActivated{ false };

public:
    WinScreen() = default;
    ~WinScreen();
    void Init();
    int Update();
    void Render(AEGfxVertexList*, AEGfxTexture*);

    bool IsRestartGameSelected();
    bool IsMenuSelected();
    bool IsQuitSelected();
};
