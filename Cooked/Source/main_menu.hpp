#pragma once
#include <vector>
#include <string>
#include "AEEngine.h"
#include <AEGraphics.h>
#include "render.hpp"

// Simple Button structure for menu items
struct Button {
    std::string label;
    float x, y;      // Center position of the button
    float width, height;
};

class MainMenu {
public:
    MainMenu();
    ~MainMenu();

    // Initializes menu resources (fonts, background texture, buttons)
    void Init();

    // Handles input for menu navigation (keyboard and mouse)
    void Update();

    // Renders the menu background and buttons
    void Render(AEGfxVertexList* mesh);

    // Returns true if the user has selected "Start Game"
    bool IsStartGameSelected() const;

    // Returns true if the user has selected "Quit Game"
    bool IsQuitSelected() const;

    // Clean up any allocated resources
    void Cleanup();

private:
    std::vector<Button> buttons;          // List of buttons
    int selectedOption;                   // Currently highlighted option
    int FontID_main_menu = -1;
    AEGfxTexture* background = nullptr;

    // Flag set when the mouse click activates the "Start Game" button
    bool m_StartGameActivated = false;

    // Helper: Check if a point is inside a button (using center coordinates)
    bool IsPointInsideButton(float px, float py, const Button& btn) const;
};
