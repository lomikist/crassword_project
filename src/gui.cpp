#include "../includes/gui.h"
#include "../includes/board.h"
#include <menu.h>
#include <ncurses.h>
#include <map>
#include <functional>

using namespace std;

//
int Gui::windowHeight;
int Gui::windowWidth;

Gui::Gui(int verCount, int horCount){
    std::vector<string> menuOptions = {"start", "how control","choose control type","your previous results","exit"};

    this->startMenu = new Menu(menuOptions);
    // (width, height) 
    this->gameBoard = new Board(verCount, horCount);
}

Gui::~Gui(){

}

/**
 * setting a board size after some events. 
*/
void Gui::adjustScreenSize(){
    getmaxyx(stdscr, Gui::windowHeight, Gui::windowWidth);
}

void Gui::drawStartMenu(int height, int width){
    int y = (Gui::windowHeight - height) / 2;
    int x = (Gui::windowWidth - width) / 2;

    this->startMenu->mainWindow = newwin(height, width, y, x);
    box(this->startMenu->mainWindow, 0, 0);

    for (int i = 0; i < this->startMenu->startMenuItems.size(); ++i) {
        if ( &this->startMenu->startMenuItems[i] == this->startMenu->startMenuActiveItem ) {
            mvwprintw(this->startMenu->mainWindow, (i + 0.5) * height / this->startMenu->startMenuItems.size(), 2, "----->");
            mvwprintw(this->startMenu->mainWindow, (i + 0.5) * height / this->startMenu->startMenuItems.size(), 9, "%s", this->startMenu->startMenuActiveItem->c_str() );
        } else {
            mvwprintw(this->startMenu->mainWindow, (i + 0.5) * height / this->startMenu->startMenuItems.size(), 2, "%s", this->startMenu->startMenuItems[i].c_str());
        }
    }
    wrefresh(this->startMenu->mainWindow);
}

void Gui::changeItem(int key){
    // for down
    if ( key == 1 && this->startMenu->startMenuActiveItem != &this->startMenu->startMenuItems[this->startMenu->startMenuItems.size() - 1] ) {
        this->startMenu->startMenuActiveItem = this->startMenu->startMenuActiveItem + 1;
    } else if (key == 0 && this->startMenu->startMenuActiveItem != &this->startMenu->startMenuItems[0]) {
        // for up
        this->startMenu->startMenuActiveItem = this->startMenu->startMenuActiveItem - 1;
    }
}

void Gui::startDrawBoadr( std::vector < std::vector < char > > & table){
    int y = 1;
    int x = (Gui::windowWidth - this->gameBoard->sizes.second) / 2;

    // initialaze game board
    this->gameBoard->mainWindow = newwin(gameBoard->sizes.first, gameBoard->sizes.second, y, x);
    int counter = 1;
    for (int i = 0; i < table.size(); ++i) {
        for (int j = 0; j < table[i].size(); ++j) {
            // // print a field number ( 1 + becauese number in left upper part of the field ).
            // mvwprintw(this->gameBoard->mainWindow, 1 + j * 4, 1 + i * 4, "%d", counter);
            // print a char from the board ( 2 + becaues each field is 3 spaces and 1 spase is line)
            mvwaddch(this->gameBoard->mainWindow, 1 + i * 2, 2 + j * 4, table[i][j]);
            counter++;
        }
    }   
    box(this->gameBoard->mainWindow, 0, 0);

    this->drawHorizontalLines();
    this->drawVerticalLines();

    wrefresh(this->gameBoard->mainWindow);
    // wrefresh(inputWindow);
}

void Gui::drawVerticalLines(){
    for(int i = 1; i < this->gameBoard->sizes.second / 4; ++i){
        // from +1 to -1 because this function for inner lines.
        mvwvline(this->gameBoard->mainWindow, 1, i * 4, 0, this->gameBoard->sizes.first - 2);
    }
}

void Gui::drawHorizontalLines(){
    for(int i = 1; i < this->gameBoard->sizes.first / 2; ++i){
        // last argument .second because for horizontal line we should print vertical coutn time. 
        mvwhline(this->gameBoard->mainWindow, i * 2, 1, 0, this->gameBoard->sizes.second - 2);
    }
}

int Gui::detectConrtolKeys(){    
    // adjusting a window sizes.
    int key = getch();
    // if pressed button is not enter
    if ( key == KEY_UP 
        || key == KEY_DOWN 
        || key == KEY_LEFT 
        || key == KEY_RIGHT
        || key == 10
        || key == 'q'
        ) {
        return key;
    }
    return 0;
}

int Gui::getDecimalNumber(){
    int input, number = 0;
    do {
        input = getch();
        // take a input from user and convert it to number , if assci code between 9 and 1.
        if (input <= '9' && input >= '1') {
            number = number * 10 + input - '0';
        }
    } while (input != 10);
    return number;
}

void Gui::clearScreen(){
    clear();
}