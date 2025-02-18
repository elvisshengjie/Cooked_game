#pragma once
#include <vector>
#include <string>

class MainMenu {
public:
    MainMenu();
    ~MainMenu();

    // Initializes menu resources (e.g., load fonts, textures, etc.)
    void Init();

    // Handles input for menu navigation
    void Update();

    // Renders the menu options on the screen
    void Render();

    // Returns true if the user has chosen to start the game
    bool IsStartGameSelected() const;

    // Returns true if the user has chosen to quit the game
    bool IsQuitSelected() const;

    // Clean up any allocated resources
    void Cleanup();

private:
    std::vector<std::string> menuOptions;
    int selectedOption;
};