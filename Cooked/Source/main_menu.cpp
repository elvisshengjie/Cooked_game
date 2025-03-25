#include "Main_Menu.hpp"

void Digipen::Init(){

    time.start(5);
    DigipenLogo = AEGfxTextureLoad("Assets/DigiPen_Singapore_WEB_RED.png");
}

void Digipen::Update() {
   
    if (time.completed() || AEInputCheckTriggered(AEVK_LBUTTON) || AEInputCheckTriggered(AEVK_RBUTTON) || AEInputCheckTriggered(AEVK_SPACE) || AEInputCheckTriggered(AEVK_RETURN) || AEInputCheckTriggered(AEVK_ESCAPE)) {
        // Reset the activation flag each frame.
        flag = true;
    }
    
}

void Digipen::Render(AEGfxVertexList* mesh) {

    
    
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        AEGfxSetBackgroundColor(0, 0, 0);
        RenderMain_digipenLogo(mesh, DigipenLogo);

        assert(DigipenLogo && "DigiPen logo texture failed to load!");
    
}

void Digipen::Cleanup() {
    AEGfxTextureUnload(DigipenLogo);
}
bool IsPointInsideButton(float px, float py, const Button& btn) {
    float left = btn.box.x+800.0f - btn.box.width / 2.0f;
    float right = btn.box.x+800.0f + btn.box.width / 2.0f;
    float top = 450.0f -btn.box.y + btn.box.height / 2.0f;
    float bottom = 450.0f -btn.box.y - btn.box.height / 2.0f;


    return (px >= left && px <= right && py <= top && py >= bottom);
}

// Destructor
MainMenu::~MainMenu() {}

void MainMenu::Init() {
    background = AEGfxTextureLoad("Assets/cafe.jpg");
  
    button = AEGfxTextureLoad("Assets/paperUIButton.png");
    htpTexture = AEGfxTextureLoad("Assets/howtoplay.png");
    htpButtonTexture = AEGfxTextureLoad("Assets/X.png");
    titleTexture = AEGfxTextureLoad("Assets/title.png");

    

    assert(background && "Failed to load background texture!");

    // Define button positions and sizes.
    float centerX{ 0.0f };      // Center horizontally
    float startY{ 0.25f };       // Starting y position for the top button
    float buttonWidth{ 300.0f };  // Width of each button
    float buttonHeight{ 50.0f };//Height of each button
    float spacing{ 0.2f };      // Vertical spacing between button centers


    buttons.clear();
    buttons.push_back({ "Start Game", { buttonWidth, buttonHeight, (centerX * 800.0f) , (startY * 450.0f) } });
    buttons.push_back({ "Credits",    { buttonWidth, buttonHeight, (centerX * 800.0f) , (startY * 450.0f) - (spacing * 450.0f)}});
    buttons.push_back({ "Options",    { buttonWidth, buttonHeight, (centerX * 800.0f) , (startY * 450.0f) - (spacing * 2 * 450.0f)}});
    buttons.push_back({ "Extras",     { buttonWidth, buttonHeight, (centerX * 800.0f) , (startY * 450.0f)- (spacing * 3 * 450.0f)}});
    buttons.push_back({ "How To Play",{ buttonWidth, buttonHeight, (centerX * 800.0f) , (startY * 450.0f)  - (spacing * 4 * 450.0f)}});
    buttons.push_back({ "Quit Game",  { buttonWidth, buttonHeight, (centerX * 800.0f) , (startY * 450.0f) - (spacing * 5 * 450.0f)}});
}

void MainMenu::Update() {
    
        m_StartGameActivated = false;
        m_CreditsActivated = false;
        m_StartGameActivated4 = false;
        m_OptionsActivated = false;
        

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
            //// Convert from screen-space (assuming 1600x900) to centered coordinates:
            //float mouseX{ (rawX - 800) / 800.0f };
            //float mouseY{ (450 - rawY) / 450.0f };

            // Check each button to see if the mouse is over it.
            for (size_t i = 0; i < buttons.size(); i++) {
                if (IsPointInsideButton(static_cast<float>(rawX), static_cast<float>(rawY), buttons[i])) {
                    selectedOption = static_cast<int>(i);
                   // std::cout << "yes";
                    // If "Start Game" (button 0) is clicked, set activation flag.
                    if (i == 0) {
                        m_StartGameActivated = true;
                    }
                    else if (i == 1) {
                        m_CreditsActivated = true;
                    }
                    else if (i == 2) 
                    {
                        m_OptionsActivated = true;
                    }
                    else if (i == 4) {
                        m_howToPlayActivated = true;
                    }
                    else if (i == 5) {
                        m_StartGameActivated4 = true;
                    }
                }
            }
            if (m_howToPlayActivated) {
                if (IsPointInsideButton(static_cast<float>(rawX), static_cast<float>(rawY), HTPbutton_button)) {
                    m_howToPlayActivated = false;
                }
            }
 
        }
    
}

void MainMenu::Render(AEGfxVertexList* mesh) {

    
        RenderMain_menu_background(mesh, background);
        
        DrawRect(titleRect, titleTexture, mesh);

        // Render each button. We assume AEGfxPrint centers the text.
        for (size_t i = 0; i < buttons.size(); i++) {
            const Button& btn = buttons[i];

            DrawRect(btn.box, button, mesh);
            AEGfxPrint(FontID, btn.label.c_str(), btn.box.x-0.1f , btn.box.y/450.0f -0.02f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);


    
            //DrawRect(btn.box, 0xFFFF00FF, mesh);

        }
        if (m_howToPlayActivated) {
            DrawRect(HTP_rect, htpTexture, mesh);
            DrawRect(HTPbutton_button.box, htpButtonTexture, mesh);
        }
        
    

}


bool MainMenu::IsStartGameSelected() const {
    return ((m_StartGameActivated ) );
}

bool MainMenu::isCreditsSelected() const
{
    return((m_CreditsActivated));
}


bool MainMenu::IsQuitSelected() const {
    return ((m_StartGameActivated4));
}

bool MainMenu::IsOptionsSelected() const
{
    return ((m_OptionsActivated));
}

void MainMenu::Cleanup() {
    AEGfxTextureUnload(background);
    
    AEGfxTextureUnload(button);
    AEGfxTextureUnload(htpTexture);
    AEGfxTextureUnload(htpButtonTexture);
    AEGfxTextureUnload(titleTexture);
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
    float buttonWidth{ 300.0f };  // Width of each button
    float buttonHeight{ 60.0f };//Height of each button
    float spacing{ 0.2f };      // Vertical spacing between button centers

    buttons.clear();
    buttons.push_back({ "Restart",    { buttonWidth, buttonHeight, centerX * 800.0f , (startY * 450.0f) } } );
    buttons.push_back({ "Main Menu",  { buttonWidth, buttonHeight, (centerX * 800.0f) , (startY * 450.0f) - (spacing * 450.0f)} });
    buttons.push_back({ "Quit Game",  { buttonWidth, buttonHeight, (centerX * 800.0f) , (startY * 450.0f) - (spacing * 2 * 450.0f)} });
}
int WinScreen::Update()
{
    m_StartGameActivated = false;
    // Mouse input: Process on left-click.
    if (AEInputCheckTriggered(AEVK_LBUTTON)) {

        int rawX, rawY;
        AEInputGetCursorPosition(&rawX, &rawY);
        // Convert from screen-space (assuming 1600x900) to centered coordinates:
     /*   float mouseX = (rawX - 800) / 800.0f;
        float mouseY = (450 - rawY) / 450.0f;*/

        // Check each button to see if the mouse is over it.
        for (size_t i = 0; i < buttons.size(); i++)
        {
            if (IsPointInsideButton(static_cast<float>(rawX), static_cast<float>(rawY), buttons[i]))
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
void WinScreen::Render(AEGfxVertexList* mesh, AEGfxTexture* tex, AEGfxTexture* tex2, AEGfxTexture* button, const char* condition)
{
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);

    Rect background{ 1600.0f,900.0f,0.0f,0.0f };
    DrawRect(background, tex, mesh);

    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);
    AEGfxSetColorToAdd(0.0, 0.0f, 0.0f, 0.0f);
    AEGfxSetBlendMode(AE_GFX_BM_NONE);
    AEGfxSetTransparency(1.0f);

    Rect box{ 900.0f, 1000.0f, 100.0f, -60.0f };
    DrawRect(box, tex2, mesh);


    // Render each button. We assume AEGfxPrint centers the text.
    for (size_t i = 0; i < buttons.size(); i++) {
        const Button& btn = buttons[i];
        
        DrawRect(btn.box, button, mesh);
        //unsigned int color = (i == static_cast<size_t>(selected)) ? 0xFFFFFF00 : 0xFFFFFFFF;
        AEGfxPrint(FontID, btn.label.c_str(), btn.box.x-0.1f, btn.box.y/450.f-0.01f, 1.5f, 0.0f, 0.0f, 0.0f, 1.0f);

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

PauseMenu::~PauseMenu() {}

void PauseMenu::Init() {
    // Use the same style as MainMenu for background and button layout.
    float centerX{ 0.0f };
    float startY{ 0.5f };
    float buttonWidth{ 300.0f };
    float buttonHeight{ 60.0f };
    float spacing{ 0.2f };

    buttons.clear();
    buttons.push_back({ "Resume Game", { buttonWidth, buttonHeight, centerX * 800.0f, startY * 450.0f } });
    buttons.push_back({ "How To Play", { buttonWidth, buttonHeight, centerX * 800.0f, (startY * 450.0f) - spacing * 450.0f } });
    buttons.push_back({ "Quit Game", { buttonWidth, buttonHeight, centerX * 800.0f, (startY * 450.0f) - (spacing * 2 * 450.0f )} });
}

int PauseMenu::Update() {
    time += AEFrameRateControllerGetFrameTime();

    // Allow keyboard navigation (optional)
    if (AEInputCheckTriggered(AEVK_DOWN)) {
        selectedOption = (selectedOption + 1) % buttons.size();
    }
    if (AEInputCheckTriggered(AEVK_UP)) {
        selectedOption = (selectedOption - 1 + buttons.size()) % buttons.size();
    }

    // Process mouse click
    if (AEInputCheckTriggered(AEVK_LBUTTON))
    {
        int rawX, rawY;
        AEInputGetCursorPosition(&rawX, &rawY);
        for (size_t i = 0; i < buttons.size(); i++)
        {
            if (IsPointInsideButton((float)rawX, (float)rawY, buttons[i]))
            {
                selectedOption = i;
                // Immediately return if you want the click itself to ��activate�� the button:
                if (i == 0) // Resume
                    return 1;
                if (i == 1) {
                    m_howToPlayActivated = true;
                    return 2;
                }
                if (i == 2)
                    return 3;
            }
        }
        if (m_howToPlayActivated) {
            if (IsPointInsideButton((float)rawX, (float)rawY, HTPbutton_button)) {
                m_howToPlayActivated = false;
            }
        }
    }


    // Check selection based on the current option:
    // Option 0: Resume Game, Option 1: Quit Game.
    if (selectedOption == 0 && AEInputCheckTriggered(AEVK_RETURN)) {
        return 1; // Resume game
    }
    if (selectedOption == 2 && AEInputCheckTriggered(AEVK_RETURN)) {
        return 3; // Quit game
    }

    return 0;
}

void PauseMenu::Render(AEGfxVertexList* mesh, AEGfxTexture* background, AEGfxTexture* button, AEGfxTexture* htp , AEGfxTexture* htpbutton) {
    // Render background and logo similar to MainMenu
    RenderMain_menu_background(mesh, background);
   /* RenderMain_digipenLogo(mesh, logo);*/

    // Render each button
    for (size_t i = 0; i < buttons.size(); i++) {
        const Button& btn = buttons[i];
        // Draw button rectangle
        DrawRect(btn.box, button, mesh);
        // Print button label
        AEGfxPrint(FontID, btn.label.c_str(), btn.box.x-0.1f, btn.box.y/450.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f); // black text

    }



    if (m_howToPlayActivated) {
        DrawRect(HTP_rect, htp, mesh);
        DrawRect(HTPbutton_button.box, htpbutton, mesh);
    }
}

Credits::Credits() {
    // Get the window height in pixels (for example, 900) and use half of it (450)
    // if your main menu converts y by dividing by 450.
    screenHeight = static_cast<float>(AEGfxGetWindowHeight());
    scrollPosition = -200.0f; // start at top (in pixel space)
}

void Credits::Init() {
    lines.clear();
    // Populate the credits list.
    lines.push_back({ "Cooked!", 1.8f, 60.0f });
    lines.push_back({ "created at DigiPen Institute of Technology Singapore", 1.0f, 80.0f });
    lines.push_back({ "PRESIDENT", 1.5f, 40.0f });
    lines.push_back({ "CLAUDE COMAIR", 1.2f, 60.0f });
    lines.push_back({ "PROGRAMMERS INCLUDE", 1.5f, 40.0f });
    lines.push_back({ "ELVIS", 1.2f, 30.0f });
    lines.push_back({ "KERRIN", 1.2f, 30.0f });
    lines.push_back({ "NORMAN", 1.2f, 30.0f });
    lines.push_back({ "JUSTIN", 1.2f, 60.0f });
    lines.push_back({ "DIGIPEN INSTRUCTORS & ADVISORS", 1.5f, 40.0f });
    lines.push_back({ "DING XIANG", 1.2f, 30.0f });
    lines.push_back({ "SOROOR", 1.2f, 30.0f });
    lines.push_back({ "GERALD WONG", 1.2f, 60.0f });
    lines.push_back({ "All Content Copyright 2025 DigiPen Institute of Technology Singapore. All Rights Reserved", 0.8f, 80.0f });

    lines.push_back({ "PRESS Q TO GO BACK MAIN MENU", 1.5f, 80.0f });

}

void Credits::Update() {
    s32 delta = 0;
    AEInputMouseWheelDelta(&delta);  // Get how much the wheel moved
    float sensitivity = 20.0f;  // Adjust sensitivity as needed.
    // Update the scroll position in pixel space
    scrollPosition += static_cast<float>(delta) * sensitivity;
    // Clamp to prevent scrolling above the start 
    if (scrollPosition > -300.0f) {
        scrollPosition = -300.0f;
    }
    if (scrollPosition < -400.0f) {
        scrollPosition = -400.0f;
    }
    // Add automatic scrolling for a better credits experience
    scrollPosition += 0.5f; // Adjust speed as needed
}

void Credits::Render(AEGfxVertexList* mesh) {
  /*   Set texture to NULL to ensure no previous textures are used*/
    DrawRect(HTPbutton_buttonX.box, texture, mesh);
    AEGfxTextureSet(NULL, 0.0f, 0.0f);
    AEGfxSetRenderMode(AE_GFX_RM_COLOR);
    AEGfxSetBackgroundColor(0.87f, 0.72f, 0.53f);
   

    // IMPORTANT: Set blend mode for text rendering
    AEGfxSetBlendMode(AE_GFX_BM_BLEND);
    float textX = -0.5f; 
    // Convert scrollPosition (in pixels) to normalized space
    float normY = -scrollPosition / 450.0f;

    for (std::vector<CreditLine>::const_iterator it = lines.begin(); it != lines.end(); ++it) {
        // Only draw if in the visible normalized range (-1.0 to 1.0)
        if (normY > -1.0f && normY < 1.0f) {
      
            AEGfxPrint(FontID, it->text.c_str(), textX, normY, it->scale, 1, 1, 1, 1.0f);
        }
        normY -= it->spacing / 450.0f;
    }

    // Check if the left mouse button is pressed on the HTP button:
    if (AEInputCheckTriggered(AEVK_LBUTTON)) {
        int mouseX, mouseY;
        AEInputGetCursorPosition(&mouseX, &mouseY);
        if (IsPointInsideButton(static_cast<float>(mouseX), static_cast<float>(mouseY), HTPbutton_buttonX)) {
            exitToMain = true;  // Set the flag if the button is clicked
        }
    }
}


OptionsMenu::~OptionsMenu() {}

void OptionsMenu::Init()
{
   

    // Create buttons for volume control + back
    // Adjust positions/sizes to fit your layout
    float centerX = 0.0f;
    float startY = 0.3f;
    float buttonW = 300.0f;
    float buttonH = 60.0f;
    float spacing = 0.2f;

    buttons.clear();
    buttons.push_back({ "Volume Up",   { buttonW, buttonH, centerX * 800.0f,  startY * 450.0f } });
    buttons.push_back({ "Volume Down", { buttonW, buttonH, centerX * 800.0f,  (startY * 450.0f) - (spacing * 450.0f) } });
    buttons.push_back({ "Back",        { buttonW, buttonH, centerX * 800.0f,  (startY * 450.0f) - (spacing * 2 * 450.0f) } });
}

int OptionsMenu::Update(float& bgmVolume, AEAudioGroup bgm)
{
    // Mouse input
    if (AEInputCheckTriggered(AEVK_LBUTTON))
    {
        int mouseX, mouseY;
        AEInputGetCursorPosition(&mouseX, &mouseY);

        // Check each button
        for (size_t i = 0; i < buttons.size(); i++)
        {
            if (IsPointInsideButton(static_cast<float>(mouseX), static_cast<float>(mouseY), buttons[i]))
            {
                selectedOption = static_cast<int>(i);
                switch (selectedOption)
                {
                case 0: // Volume Up
                    bgmVolume += 0.5f;
                    if (bgmVolume > 1.0f) bgmVolume = 1.0f;
                    AEAudioSetGroupVolume(bgm, bgmVolume);
                    break;
                case 1: // Volume Down
                    bgmVolume -= 0.5f;
                    if (bgmVolume < 0.0f) bgmVolume = 0.0f;
                    AEAudioSetGroupVolume(bgm, bgmVolume);
                    break;
                case 2: // Back
                    return 1; // We'll return 1 to indicate "back to main menu"
                default:
                    break;
                }
            }
        }
    }

    return 0; // 0 means no special action
}

//void OptionsMenu::Render(AEGfxVertexList* mesh, AEGfxTexture* background, AEGfxTexture* buttonTex)
//{
//    // Render background
//
//        RenderMain_menu_background(mesh, background);
//
//    // Render buttons
//    for (size_t i = 0; i < buttons.size(); i++)
//    {
//        DrawRect(buttons[i].box, buttonTex, mesh);
//        // Print button label (adjust position as needed)
//        AEGfxPrint(FontID, buttons[i].label.c_str(),
//            buttons[i].box.x - 0.1f,
//            buttons[i].box.y / 450.0f,
//            1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
//    }
//}

void OptionsMenu::Render(AEGfxVertexList* mesh, AEGfxTexture* background, AEGfxTexture* buttonTex)
{
    // Set render mode and reset color state before drawing the background.
    AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

    // Render the background (ensure RenderMain_menu_background correctly handles coordinates)
    RenderMain_menu_background(mesh, background);

    // Loop through each button to render its background and label
    for (size_t i = 0; i < buttons.size(); i++)
    {
        // Draw the button background using texture mode.
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
        DrawRect(buttons[i].box, buttonTex, mesh);

        // Switch to color mode for text rendering and reset color state.
        AEGfxSetRenderMode(AE_GFX_RM_COLOR);
        AEGfxSetColorToMultiply(1.0f, 1.0f, 1.0f, 1.0f);

        // Draw the button label.
        // (You may need to adjust the position values depending on your coordinate system.)
        AEGfxPrint(FontID, buttons[i].label.c_str(),
            buttons[i].box.x - 0.1f,
            buttons[i].box.y / 450.0f,
            1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

        // Optionally, switch back to texture mode in preparation for the next button.
        AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);
    }
}
