#include "../includes/core.h"
#include "../includes/gui.h"

Core::Core()
{
    this->menu = new Menu("start menue");
    this->user_interface = new Gui();
    this->board = new Board();
}
Core::~Core()
{
}

/**
 * Function for selecting which key is pressed depending on it draw board or menu.
 */
void Core::detecting_key()
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    int key;

    printw("You can control with up and down arrows.");

    while (true)
    {
        key = getch();
        clear();
        // if pressed button is not enter
        if (key != 10 ) {
            if (key == KEY_UP) {
                // For changing a pointer selection to one level up
                this->menu->change_item(0);
            } else if (key == KEY_DOWN) {
                // For changing a pointer selection to one level down
                this->menu->change_item(1);
            } else if (key == 'q'){
                break;
            }
            user_interface->drawMenu(this->menu);
        } else if (key == 10 ){
            // if pressed a enter
            user_interface->drawBoard(this->board);
        }

        refresh();
    }
    endwin();
}