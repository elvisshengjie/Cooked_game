#include "Main_Menu.hpp"


bool IsPointInsideButton(float px, float py, const Button& btn) {
    float left = btn.x - btn.width / 2.0f;
    float right = btn.x + btn.width / 2.0f;
    float top = btn.y + btn.height / 2.0f;
    float bottom = btn.y - btn.height / 2.0f;
    return (px >= left && px <= right && py <= top && py >= bottom);
}

// Destructor
MainMenu::~MainMenu() {}

void MainMenu::Init() {
    background = AEGfxTextureLoad("Assets/cafe.jpg");
    DigipenLogo = AEGfxTextureLoad("Assets/DigiPen_Singapore_WEB_RED.png");

    assert(background && "Failed to load background texture!");

    // Define button positions and sizes.
    float centerX{ 0.0f };      // Center horizontally
    float startY{ 0.5f };       // Starting y position for the top button
    float buttonWidth{ 1.0f };  // Width of each button
    float buttonHeight{ 0.15f };//Height of each button
    float spacing{ 0.2f };      // Vertical spacing between button centers

    buttons.clear();
    buttons.push_back({ "Start Game", centerX, startY, buttonWidth, buttonHeight });
    buttons.push_back({ "Credits",    centerX, startY - spacing, buttonWidth, buttonHeight });
    buttons.push_back({ "Options",    centerX, startY - 2 * spacing, buttonWidth, buttonHeight });
    buttons.push_back({ "Extras",     centerX, startY - 3 * spacing, buttonWidth, buttonHeight });
    buttons.push_back({ "Quit Game",  centerX, startY - 4 * spacing, buttonWidth, buttonHeight });
}

void MainMenu::Update() {
    time += AEFrameRateControllerGetFrameTime();
    if (time > 5 || AEInputCheckTriggered(AEVK_LBUTTON) || AEInputCheckTriggered(AEVK_RBUTTON) || AEInputCheckTriggered(AEVK_SPACE) || AEInputCheckTriggered(AEVK_RETURN) || AEInputCheckTriggered(AEVK_ESCAPE)) {
        // Reset the activation flag each frame.
        flag = true;
    }
    if (flag) {
        m_StartGameActivated = false;
        m_StartGameActivated4 = false;
        
        

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
            float mouseX{ (rawX - 800) / 800.0f };
            float mouseY{ (450 - rawY) / 450.0f };

            // Check each button to see if the mouse is over it.
            for (size_t i = 0; i < buttons.size(); i++) {
                if (IsPointInsideButton(mouseX, mouseY, buttons[i])) {
                    selectedOption = static_cast<int>(i);
                    std::cout << "yes";
                    // If "Start Game" (button 0) is clicked, set activation flag.
                    if (i == 0) {
                        m_StartGameActivated = true;
                    }
                    else if (i == 4) {
                        m_StartGameActivated4 = true;
                    }

                }
            }
 
        }
    }
}

void MainMenu::Render(AEGfxVertexList* mesh) {
    
    if (flag){
        RenderMain_menu_background(mesh, background);
        
        // Render each button. We assume AEGfxPrint centers the text.
        for (size_t i = 0; i < buttons.size(); i++) {
            const Button& btn = buttons[i];
            AEGfxPrint(FontID, btn.label.c_str(), btn.x, btn.y, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

        }
        
    }
    else {
        AEGfxSetBackgroundColor(0, 0, 0);
        RenderMain_digipenLogo(mesh, DigipenLogo);
        
    }
}


bool MainMenu::IsStartGameSelected() const {
    return ((m_StartGameActivated ) );
}


bool MainMenu::IsQuitSelected() const {
    return ((m_StartGameActivated4));
}


void MainMenu::Cleanup() {
    AEGfxTextureUnload(background);
    AEGfxTextureUnload(DigipenLogo);
    AEGfxDestroyFont(FontID);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
// Destructor
WinScreen::~WinScreen() {}

void WinScreen::Init()
{
    // Define button positions and sizes.
    float centerX{ 0.0f };      // Center horizontally
    float startY{-0.2f};       // Starting y position for the top button
    float buttonWidth{ 1.0f };  // Width of each button
    float buttonHeight{ 0.15f };//Height of each button
    float spacing{ 0.2f };      // Vertical spacing between button centers

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
                        //m_StartGameActivated = true;
                        return 1;
                        break;
                    case 1: //main menu
                        return 2;
                        break;
                    case 2:
                        return 3;
                        break;
                    default:
                        
                        break;
                }
                
            }
        }
    }
    return 0;
}
void WinScreen::Render(AEGfxVertexList* mesh, AEGfxTexture* tex, AEGfxTexture* tex2, const char* condition)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

    Rect background{ 1600.0f,900.0f,0.0f,0.0f };
    DrawRect(background, tex, mesh);

    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_NONE);
    AEGfxSetTransparency(1.0f);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);

    Rect box{ 900.0f, 1000.0f, 100.0f, -60.0f };
    DrawRect(box, tex2, mesh);


    // Render each button. We assume AEGfxPrint centers the text.
    for (size_t i = 0; i < buttons.size(); i++) {
        const Button& btn = buttons[i];
        unsigned int color = (i == static_cast<size_t>(selected)) ? 0xFFFFFF00 : 0xFFFFFFFF;
        AEGfxPrint(FontID, btn.label.c_str(), btn.x-0.1f, btn.y, 1.5f, 0.0f, 0.0f, 0.0f, 1.0f);
    }

    AEGfxPrint(FontID, condition, -0.23f, 0.2f, 4.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

bool WinScreen::IsRestartGameSelected()
{
    return true;
}
bool WinScreen::IsMenuSelected()
{
    return true;
}
bool WinScreen::IsQuitSelected()
{
    return true;
}
