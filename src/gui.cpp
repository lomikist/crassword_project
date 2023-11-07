#include "../includes/gui.h"
#include <menu.h>
#include "gui.h"
#include "board.h"
#include <ncurses.h>
#include <map>
#include <functional>

using namespace std;

Gui::Gui(){
    int width = 60;
    int height = 30; 

    vector<string> menuOptions = {"start", "obout_us","exit","blya","mlya"};
    // map<string, function< void() > > menuFunctionOptions;
    //TODO: each option should have their own logic after entering a key.
    // menuFunctionOptions["start"] = [this]() { this->startDrawBoadr(); };
    // menuFunctionOptions["exit"] = [this]() { this->startDrawBoadr(); };
    // menuFunctionOptions["obout_us"] = [this]() { this->startDrawBoadr(); };

    this->startMenu = new Menu(menuOptions);
    // (width, height) 
    this->gameBoard = new Board(height, width);
}

Gui::~Gui(){

}

//
int Gui::windowHeight;
int Gui::windowWidth;

// setting a board size after some events. 
void Gui::adjustScreenSize(){
    getmaxyx(stdscr, Gui::windowHeight, Gui::windowWidth);
}

void Gui::drawStartMenu(int height, int width){
    int y = (Gui::windowHeight - height) / 2;
    int x = (Gui::windowWidth - width) / 2;

    auto *mainWindow = this->startMenu->mainWindow;
    
    mainWindow = newwin(height, width, y, x);
    box(mainWindow, '#', '#');

    for (int i = 0; i < this->startMenu->startMenuItems.size(); ++i) {
        if ( &this->startMenu->startMenuItems[i] == this->startMenu->startMenuActiveItem ) {
            mvwprintw(mainWindow, (i + 0.5) * height / this->startMenu->startMenuItems.size(), 2, "----->");
            mvwprintw(mainWindow, (i + 0.5) * height / this->startMenu->startMenuItems.size(), 9, "%s", this->startMenu->startMenuActiveItem->c_str() );
        } else {
            mvwprintw(mainWindow, (i + 0.5) * height / this->startMenu->startMenuItems.size(), 2, "%s", this->startMenu->startMenuItems[i].c_str());
        }
    }
    wrefresh(mainWindow);
}

// responsible for changing a menu active item. 
void Gui::changeItem(int key){
    // for down
    if ( key == 1 && this->startMenu->startMenuActiveItem != &this->startMenu->startMenuItems[this->startMenu->startMenuItems.size() - 1] ) {
        this->startMenu->startMenuActiveItem = this->startMenu->startMenuActiveItem + 1;
    } else if (key == 0 && this->startMenu->startMenuActiveItem != &this->startMenu->startMenuItems[0]) {
        // for up
        this->startMenu->startMenuActiveItem = this->startMenu->startMenuActiveItem - 1;
    }
}

void Gui::startDrawBoadr( vector < vector < char > > & table){
    int y = (Gui::windowHeight - gameBoard->sizes.first) / 2;
    int x = (Gui::windowWidth - gameBoard->sizes.second) / 2;

    auto *mainWindow = this->gameBoard->mainWindow;
    auto *inputWindow = this->gameBoard->inputWindow;

    // initialaze game board
    mainWindow = newwin(gameBoard->sizes.first, gameBoard->sizes.second, y, x);
    //  initialzae input board      ! ( y + game...  becaues we should draw it below the board )
    inputWindow = newwin(gameBoard->sizes.first / 5, gameBoard->sizes.second, y + gameBoard->sizes.first + 7, x);

    box(mainWindow, 0, 0);
    for (size_t i = 1; i < table.size(); ++i) {
        for (size_t j = 1; j < table[i].size(); ++j) {
            mvwaddch(mainWindow, j, i, table[i][j]);
        }
    }
    wrefresh(mainWindow);
    wrefresh(inputWindow);
}