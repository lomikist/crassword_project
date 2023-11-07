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
            row.push_back( i );
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
    do
    {
        // printw("you whould enter y x coordinates and after that you should enter a string.");
        user_interface->startDrawBoadr( this->table );
        key = getch();
        std::cin >> y >> x;
        this->table[y][y] = 'j';
    } while ( key != 'q');
    clear();
}