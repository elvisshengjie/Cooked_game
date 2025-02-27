#include "Main_Menu.hpp"
#include "AEEngine.h"
#include "AEInput.h"
#include "render.hpp"
#include <AEGraphics.h>
#include <cassert>

bool IsPointInsideButton(float px, float py, const Button& btn) {
    float left = btn.x - btn.width / 2.0f;
    float right = btn.x + btn.width / 2.0f;
    float top = btn.y + btn.height / 2.0f;
    float bottom = btn.y - btn.height / 2.0f;
    return (px >= left && px <= right && py <= top && py >= bottom);
}

// Constructor
MainMenu::MainMenu() : selectedOption(0), m_StartGameActivated(false) {
    
}

// Destructor
MainMenu::~MainMenu() {}


void MainMenu::Init() {
    FontID_main_menu = AEGfxCreateFont("./Assets/Cute Dino.otf", 24);
    background = AEGfxTextureLoad("Assets/cafe.jpg");
    assert(FontID_main_menu >= 0 && "Failed to load font!");
    assert(background && "Failed to load background texture!");

    // Define button positions and sizes.
    float centerX = 0.0f;      // Center horizontally
    float startY = 0.5f;       // Starting y position for the top button
    float buttonWidth = 1.0f;  // Width of each button
    float buttonHeight = 0.15f;
    float spacing = 0.2f;      // Vertical spacing between button centers

    buttons.clear();
    buttons.push_back({ "Start Game", centerX, startY, buttonWidth, buttonHeight });
    buttons.push_back({ "Credits",    centerX, startY - spacing, buttonWidth, buttonHeight });
    buttons.push_back({ "Options",    centerX, startY - 2 * spacing, buttonWidth, buttonHeight });
    buttons.push_back({ "Extras",     centerX, startY - 3 * spacing, buttonWidth, buttonHeight });
    buttons.push_back({ "Quit Game",  centerX, startY - 4 * spacing, buttonWidth, buttonHeight });
}

void MainMenu::Update() {
    // Reset the activation flag each frame.
    m_StartGameActivated = false;

  
    if (AEInputCheckTriggered(AEVK_DOWN)) {
        selectedOption = (selectedOption + 1) % buttons.size();
    }
    if (AEInputCheckTriggered(AEVK_UP)) {
        selectedOption = (selectedOption - 1 + buttons.size()) % buttons.size();
    }

    // Mouse input: Process on left-click.
    if (AEInputCheckTriggered(AEVK_LBUTTON)) {
        
        int rawX, rawY;
        AEInputGetCursorPosition(&rawX, &rawY);
        // Convert from screen-space (assuming 1600x900) to centered coordinates:
        float mouseX = (rawX - 800) / 800.0f;   
        float mouseY = (450 - rawY) / 450.0f;     

        // Check each button to see if the mouse is over it.
        for (size_t i = 0; i < buttons.size(); i++) {
            if (IsPointInsideButton(mouseX, mouseY, buttons[i])) {
                selectedOption = static_cast<int>(i);
                // If "Start Game" (button 0) is clicked, set activation flag.
                if (i == 0) {
                    m_StartGameActivated = true;
                }
              
            }
        }
    }
}

void MainMenu::Render(AEGfxVertexList* mesh) {
    
    RenderMain_menu_background(mesh, background);

    // Render each button. We assume AEGfxPrint centers the text.
    for (size_t i = 0; i < buttons.size(); i++) {
        const Button& btn = buttons[i];
        unsigned int color = (i == static_cast<size_t>(selectedOption)) ? 0xFFFFFF00 : 0xFFFFFFFF;
        AEGfxPrint(FontID_main_menu, btn.label.c_str(), btn.x, btn.y, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
        
    }
}


bool MainMenu::IsStartGameSelected() const {
    return (selectedOption == 0 && (AEInputCheckTriggered(AEVK_SPACE) || m_StartGameActivated));
}


bool MainMenu::IsQuitSelected() const {
    return (selectedOption == 4 && AEInputCheckTriggered(AEVK_SPACE));
}


void MainMenu::Cleanup() {
    AEGfxTextureUnload(background);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
// Destructor
WinScreen::~WinScreen() 
{
    AEGfxTextureUnload(background);
}

void WinScreen::Init()
{
    void InitFont();
    background = AEGfxTextureLoad("Assets/cafe.jpg");

    // Define button positions and sizes.
    float centerX = 0.0f;      // Center horizontally
    float startY = 0.5f;       // Starting y position for the top button
    float buttonWidth = 1.0f;  // Width of each button
    float buttonHeight = 0.15f;
    float spacing = 0.2f;      // Vertical spacing between button centers

    buttons.clear();
    buttons.push_back({ "Restart", centerX, startY, buttonWidth, buttonHeight });
    buttons.push_back({ "Main Menu",    centerX, startY - spacing, buttonWidth, buttonHeight });
    buttons.push_back({ "Quit Game",    centerX, startY - 2 * spacing, buttonWidth, buttonHeight });
}
int WinScreen::Update()
{
    m_StartGameActivated = false;
    // Mouse input: Process on left-click.
    if (AEInputCheckTriggered(AEVK_LBUTTON)) {

        int rawX, rawY;
        AEInputGetCursorPosition(&rawX, &rawY);
        // Convert from screen-space (assuming 1600x900) to centered coordinates:
        float mouseX = (rawX - 800) / 800.0f;
        float mouseY = (450 - rawY) / 450.0f;

        // Check each button to see if the mouse is over it.
        for (size_t i = 0; i < buttons.size(); i++)
        {
            if (IsPointInsideButton(mouseX, mouseY, buttons[i]))
            {
                selected = static_cast<int>(i);
                // If "restart Game" (button 0) is clicked, set activation flag.
                switch (i)
                {
                    case 0: //restart game
                        m_StartGameActivated = true;
                        break;
                    case 1: //main menu
                        menuSelected();


                default:
                    break;
                }
                
            }
        }
    }
}
void WinScreen::Render();

bool WinScreen::restartSelected();
bool WinScreen::menuSelected();
bool WinScreen::quitSelected();
#endif