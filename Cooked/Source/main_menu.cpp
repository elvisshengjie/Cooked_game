#include "Main_Menu.hpp"
#include "AEEngine.h"
#include "AEInput.h"
#include "render.hpp"
#include <AEGraphics.h>
#include <cassert>

MainMenu::MainMenu() : selectedOption(0) {
    menuOptions.push_back("Start Game");
    menuOptions.push_back("Options");
    menuOptions.push_back("Credits");
    menuOptions.push_back("Quit");
}

MainMenu::~MainMenu() {}

void MainMenu::Init() {
    FontID_main_menu = AEGfxCreateFont("./Assets/Cute Dino.otf", 24);
    background = AEGfxTextureLoad("Assets/cafe.jpg");
    assert(FontID_main_menu >= 0 && "Failed to load font!");
    assert(background && "Failed to load background texture!");
}

void MainMenu::Update() {
    // Keyboard navigation: Use up/down arrow keys to change selection
    if (AEInputCheckTriggered(AEVK_DOWN)) {
        selectedOption = (selectedOption + 1) % menuOptions.size();
    }
    if (AEInputCheckTriggered(AEVK_UP)) {
        selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
    }
    // (Optional) You could add mouse handling here as well.
}

void MainMenu::Render(AEGfxVertexList* mesh) {
    // Render the menu background
    RenderMain_menu_background(mesh, background);

    
}

bool MainMenu::IsStartGameSelected() const {
    // Confirm selection with space key; check index 0 ("Start Game")
    return (selectedOption == 0 && AEInputCheckTriggered(AEVK_SPACE));
}

bool MainMenu::IsQuitSelected() const {
    // "Quit" is at index 3
    return (selectedOption == 3 && AEInputCheckTriggered(AEVK_SPACE));
}

void MainMenu::Cleanup() {
    // Free any resources if needed.
    AEGfxTextureUnload(background);
}
