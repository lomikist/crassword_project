#include "../includes/core.h"
#include "../includes/gui.h"
#include <map>
#include <functional>

Core::Core(int verCount, int horCount)
{
    // board initialization 
    for (size_t i = 0; i < verCount; ++i) {
        vector<char> row;       
        for (size_t j = 0; j < horCount; ++j) {
            row.push_back(' ');
        }
        this->table.push_back(row);
    }
    
    this->user_interface = new Gui();
    this->detecting_key();
}
Core::~Core()
{
}

/**
 * Function for selecting which key is pressed depending on it draw board or menu.
 */
void Core::detecting_key() {
    initscr();
    keypad(stdscr, TRUE);

    int key;

    printw("You can control with up and down arrows.");
    Gui::adjustScreenSize();
    // adjusting a window sizes.
    do {
        key = getch();
        // if pressed button is not enter
        if (key != 10 ) {
            if (key == KEY_UP) {
                // For changing a pointer selection to one level up
                this->user_interface->changeItem(0);
            } else if (key == KEY_DOWN) {
                // For changing a pointer selection to one level down
                this->user_interface->changeItem(1);
            }
            this->user_interface->drawStartMenu(15,30);
        } else {
            // check if the selected menu item is "start" 
            Gui::adjustScreenSize();
            if ( *this->user_interface->startMenu->startMenuActiveItem == "start") {
                this->startGame();
            }
        }
        
    } while (key != 'q');
    endwin();
}

void Core::startGame(){
    //pressed key
    int key, x = 0, y = 0;
    bool done = false;
    clear();
    do {
        x = 0;
        y = 0;

        // printw("you whould enter y x coordinates and after that you should enter a string.");
        printw("Enter a x");
        this->getDecimal(x);

        printw("Enter a y");
        this->getDecimal(y);
        
        printw("Enter a key");
        key = getch();

        this->table[x][y] = key;
        user_interface->startDrawBoadr( this->table );
    } while ( key != 'q');
    clear();
}

void Core::getDecimal( int& number ){
    int input;
    do {
        input = getch();
        // take a input from user and convert it to number , if assci code between 9 and 1.
        if (input <= '9' && input >= '1') {
            number = number * 10 + input - '0';
        }
    } while (input != 10);
}