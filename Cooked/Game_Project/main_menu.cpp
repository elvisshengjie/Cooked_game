#include "Main_Menu.hpp"
#include "AEEngine.h"
#include "AEInput.h"
#include "Renderer.h"
#include <AEGraphics.h>

MainMenu::MainMenu() : selectedOption(0) {
	menuOptions.push_back("Start Game");
	menuOptions.push_back("Options");
	menuOptions.push_back("Credits");
	menuOptions.push_back("Quit");

}
MainMenu::~MainMenu() {}

void MainMenu::Init()
{
}

void MainMenu::Update() {

}

void MainMenu::Render() {

}

bool MainMenu::IsStartGameSelected() const {
	return (selectedOption == 0 && AEInputCheckTriggered(AEVK_SPACE));
}

bool MainMenu::IsQuitSelected() const {
	return (selectedOption == 1 && AEInputCheckTriggered(AEVK_SPACE));
}

void MainMenu::Cleanup() {

}


