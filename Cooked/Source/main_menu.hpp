#pragma once
#include <vector>
#include <string>
#include "AEEngine.h"
#include <AEGraphics.h>
#include "render.hpp"
#include "AEInput.h"
#include <cassert>
#include <iostream>

// Simple Button structure for menu items
struct Button {
    std::string label;
    float x, y;
    float width, height;
    Rect box;
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
    AEGfxTexture* GetLogoTexture() const { return DigipenLogo; }

    double GetTime() {
        return time;
    }
    

private:
    double time = 0;
    std::vector<Button> buttons;          
    size_t selectedOption{};
    s8 FontID_main_menu = -1;
    AEGfxTexture* background = nullptr;
    AEGfxTexture* DigipenLogo = nullptr;
    AEGfxTexture* button = nullptr;
    bool flag = false;
  
    // Flag set when the mouse click activates the "Start Game" button
    bool m_StartGameActivated{ false };
    bool m_StartGameActivated4 {false};
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
    void Render(AEGfxVertexList*, AEGfxTexture*, AEGfxTexture*, AEGfxTexture*, const char* condition);

    bool IsRestartGameSelected();
    bool IsMenuSelected();
    bool IsQuitSelected();
};

class PauseMenu {
public:
    PauseMenu() = default;
    ~PauseMenu();

    // Initializes the pause menu resources and button layout.
    void Init();
    // Update the pause menu input.
    // Returns 1 if "Resume Game" is selected,
    //         2 if "Quit Game" is selected,
    //         0 otherwise.
    int Update();
    // Renders the pause menu background and buttons.
    void Render(AEGfxVertexList* mesh, AEGfxTexture* background, AEGfxTexture* logo, AEGfxTexture* button);

private:
    std::vector<Button> buttons;
    size_t selectedOption = 0;
    bool resumeActivated = false;
    bool quitActivated = false;
    double time = 0;
};