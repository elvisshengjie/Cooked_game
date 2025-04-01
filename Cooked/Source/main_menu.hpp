/*!
@ All content 2025 DigiPen (SINGAPORE) Corporation, all rights reserved
@file main_menu.hpp
@author1 Elvis lim sheng jie(elvisshengjie.lim)
@author2 Justin Kong (yimo.kong)
@author3 Kerrin Lemin Khoo (kerrinlemin.k)
@course csd1451s25 Software Engineering Project 2
@section a
*//*______________________________________________________________________*/
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
    Rect box;
};

class ConfirmScreen {
public:

    // Initializes menu resources (fonts, background texture, buttons)
    void Init();

    // Handles input for menu navigation (keyboard and mouse)
    void Update();

    // Renders the menu background and buttons
    void Render(AEGfxVertexList* mesh, AEGfxTexture* background, AEGfxTexture* button);
    
    

    bool GetFlag() {
        return flag;
    }
    
    bool GetflagToUpdate() {
        return flagToUpdate;
    }

    void ModflagToUpdate(bool A) {
        flagToUpdate = A;
    }
   

private:
    std::vector<Button> buttons;
    size_t selectedOption = 0;

    bool flag{ false };
    bool flagToUpdate{ false };
    
};
class Digipen {
public:

    // Initializes menu resources (fonts, background texture, buttons)
    void Init();

    // Handles input for menu navigation (keyboard and mouse)
    void Update();

    // Renders the menu background and buttons
    void Render(AEGfxVertexList* mesh);
    void Cleanup();
    AEGfxTexture* GetLogoTexture() const { return DigipenLogo; }
 
    double GetFlag() {
        return flag;
    }
    Timer time;
private:
    bool flag{ false };
    AEGfxTexture* DigipenLogo = nullptr;
    
};

class Credits {
private:
    struct CreditLine {
        std::string text;
        float scale;
        float spacing;
    };
    AEGfxTexture* texture = nullptr;
    std::vector<CreditLine> lines;
    float screenHeight;
    float scrollPosition;  // <-- Add this line
   
    Button HTPbutton_buttonX{ "X",{50.0f , 50.0f , 625.0f, 300.0f} };
    bool exitToMain = false;
public:
    Credits();
    void Init();
    void Update();
    void Render(AEGfxVertexList* mesh);
    void setTexture(AEGfxTexture * tex) {
        texture = tex;
    }
    bool shouldExitToMain() const { return exitToMain; }
    void ResetExitFlag() { exitToMain = false; }
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

    bool isCreditsSelected() const;

   
    bool IsQuitSelected() const;

    bool IsOptionsSelected() const;
    

   // bool IsHowToPlaySelected() const;

    
    void Cleanup();
 
    AEGfxTexture* GetHtpButtonTexture() const {
        return htpButtonTexture;
    }

    

    Rect titleRect{ 600.0f , 200.0f , 0.0f , 300.0f };
    Rect HTP_rect{ 1400.0f, 700.0f ,0.0f, 0.0f };
    Button HTPbutton_button { "X",{50.0f , 50.0f , 625.0f, 300.0f} };

private:
   
    std::vector<Button> buttons;         
    size_t selectedOption{};
    s8 FontID_main_menu = -1;
    AEGfxTexture* background = nullptr;

    AEGfxTexture* button = nullptr;
    AEGfxTexture* htpTexture = nullptr;
    AEGfxTexture* htpButtonTexture = nullptr;
    AEGfxTexture* titleTexture = nullptr;
  
  

    // Flag set when the mouse click activates the "Start Game" button
    bool m_StartGameActivated{ false };
    bool m_CreditsActivated{ false };
 
    bool m_StartGameActivated4{ false };
    bool m_howToPlayActivated{ false };
	bool m_OptionsActivated{ false };
};


class WinScreen
{
private:
    std::vector<Button> buttons;
    int selected{};
    bool m_StartGameActivated{ false };

   
public:

	bool hasPlayedSound = false;
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
    void Render(AEGfxVertexList* mesh, AEGfxTexture* background, AEGfxTexture* button, AEGfxTexture* htp, AEGfxTexture* htpbutton);


    Rect HTP_rect{ 1400.0f, 700.0f ,0.0f, 0.0f };
    Button HTPbutton_button{ "X",{50.0f , 50.0f , 625.0f, 300.0f} };

private:
    std::vector<Button> buttons;
    size_t selectedOption = 0;
    bool resumeActivated = false;
    bool quitActivated = false;
    bool m_howToPlayActivated = false;
    double time = 0;
};

class OptionsMenu
{
public:
    OptionsMenu()=default;
    ~OptionsMenu();

    // Initializes the menu (loads textures, sets up buttons, etc.)
    void Init();

    // Updates the menu each frame. 
    // `bgmVolume` is passed by reference so we can modify it here.
    // Returns an int indicating what the user did: 
    // e.g., 0 = nothing, 1 = back to main menu, etc.
    int Update(float& bgmVolume, AEAudioGroup bgm);

    // Renders the menu
    void Render(AEGfxVertexList* mesh, AEGfxTexture* background, AEGfxTexture* buttonTex);

private:
    std::vector<Button> buttons;
    size_t selectedOption = 0;

    

    // If you want a flag to indicate when to return to main menu
    bool backToMain = false;
};