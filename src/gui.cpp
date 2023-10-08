#include "../includes/gui.h"

Gui::Gui()
{
}

Gui::~Gui()
{
}

void Gui::drawMenu(Menu* item){
    for(int i = 0; i < item->items.size(); i++ ){
        if( &item->items[i] == item->active_item ){
            cout << "->" << item->items[i] << endl;
        }else {
            cout << item->items[i] << endl;
        }
    }
};

void Gui::start_Drawing(){
    initscr(); 
    keypad(stdscr, TRUE); 
    // noecho(); 
    curs_set(FALSE); 
    printw("Press arrow keys (q to quit):\n");
    int key;
    while (true) {
        key = getch();
        clear();
        if (key == KEY_UP) {
            printw("Up arrow key pressed\n");
        } else if (key == KEY_DOWN) {
            printw("Down arrow key pressed\n");
        } else if (key == KEY_RIGHT) {
            printw("Right arrow key pressed\n");
        } else if (key == KEY_LEFT) {
            printw("Left arrow key pressed\n");
        } else if (key == 'q') {
            break;
        } else {
            printw("we can controll with arrow.");
        }
    }  
    endwin();
}