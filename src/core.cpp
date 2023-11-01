#include "../includes/core.h"
#include "../includes/gui.h"

Core::Core()
{
    this->user_interface = new Gui();
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
    curs_set(FALSE);

    int key;

    printw("You can control with up and down arrows.");

    do {
        key = getch();
        clear();
        // if pressed button is not enter
        if (key != 10 ) {
            if (key == KEY_UP) {
                // For changing a pointer selection to one level up
                user_interface->changeItem(0);
            } else if (key == KEY_DOWN) {
                // For changing a pointer selection to one level down
                user_interface->changeItem(1);
            }
            user_interface->drawMenu();
        } else if (key == 10 ){
            // if pressed a enter
            user_interface->drawBoard();
        }

        refresh();
    } while (key != 'q');
    endwin();
}