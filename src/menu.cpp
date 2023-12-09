#include "../includes/menu.h"

Menu::Menu(vector<string> options){
    this->startMenuItems = options;
    this->startMenuActiveItem = &this->startMenuItems[0];
}

Menu::~Menu(){

}

class GameState {
public:
    virtual void drawMenu() = 0;
    virtual ~GameState() = default;
};

// Concrete Menu State class
class MenuState : public GameState {
public:
    void drawMenu() override {
        // Draw menu specific to MenuState
        // For example:
        // Draw main menu options
        // Draw settings menu options
    }
};

// Concrete Playing State class
class PlayingState : public GameState {
public:
    void drawMenu() override {
        // Draw menu specific to PlayingState
        // For example:
        // Draw in-game options
        // Draw pause menu
    }
};

// Concrete Settings State class
class SettingsState : public GameState {
public:
    void drawMenu() override {
        // Draw menu specific to SettingsState
        // For example:
        // Draw settings options
        // Draw back button
    }
};